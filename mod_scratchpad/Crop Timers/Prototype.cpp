#include <map>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <YYToolkit/YYTK_Shared.hpp> // YYTK v4
using namespace Aurie;
using namespace YYTK;
using json = nlohmann::json;

static const char* const MOD_NAME = "BetterChargedTools";
static const char* const VERSION = "1.0.0";
static const char* const GML_SCRIPT_NODE_OBJECT_SET_SPRITE = "gml_Script_set_sprite@gml_Object_obj_node_renderer_Create_0"; // Unneeded
static const char* const GML_SCRIPT_USE_ITEM = "gml_Script_draw_sprite_ext_pixel_perfect";
static const char* const GML_SCRIPT_ARI_FSM_HOE = "gml_Script_hoe@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_ARI_FSM_AXE = "gml_Script_axe@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_ARI_FSM_PICK_AXE = "gml_Script_pick_axe@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_ARI_FSM_SHOVEL = "gml_Script_shovel@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_ARI_FSM_NET = "gml_Script_net@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_ARI_FSM_WATERING_CAN = "gml_Script_watering_can@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_ARI_FSM_SOW = "gml_Script_sow@anon@84872@AriFsm@AriFsm";
static const char* const GML_SCRIPT_MODIFY_STAMINA = "gml_Script_modify_stamina@Ari@Ari";
static const char* const GML_SCRIPT_SETUP_MAIN_SCREEN = "gml_Script_setup_main_screen@TitleMenu@TitleMenu";

static YYTKInterface* g_ModuleInterface = nullptr;
static CInstance* global_instance = nullptr;
static bool load_on_start = true;
static bool stamina_consumed = false;
static std::map<std::string, int> script_name_to_stamina_consumed_map = {};
static std::map<std::string, std::vector<CInstance*>> script_name_to_reference_map = {};

bool EnumFunction(
	IN const char* MemberName,
	IN OUT RValue* Value
)
{
	g_ModuleInterface->Print(CM_LIGHTYELLOW, "Member Name: %s", MemberName);
	return false;
}


int RValueAsInt(RValue value)
{
	if (value.m_Kind == VALUE_REAL)
		return static_cast<int>(value.m_Real);
	if (value.m_Kind == VALUE_INT64)
		return static_cast<int>(value.m_i64);
	if (value.m_Kind == VALUE_INT32)
		return static_cast<int>(value.m_i32);
}

bool RValueAsBool(RValue value)
{
	if (value.m_Kind == VALUE_REAL && value.m_Real == 1)
		return true;
	if (value.m_Kind == VALUE_BOOL && value.m_Real == 1)
		return true;
	return false;
}

bool IsNumeric(RValue value)
{
	return value.m_Kind == VALUE_INT32 || value.m_Kind == VALUE_INT64 || value.m_Kind == VALUE_REAL;
}

bool IsObject(RValue value)
{
	return value.m_Kind == VALUE_OBJECT;
}

bool StructVariableExists(RValue the_struct, std::string variable_name)
{
	RValue struct_exists = g_ModuleInterface->CallBuiltin(
		"struct_exists",
		{ the_struct, RValue(variable_name) }
	);

	return RValueAsBool(struct_exists);
}

RValue StructVariableGet(RValue the_struct, std::string variable_name)
{
	return g_ModuleInterface->CallBuiltin(
		"struct_get",
		{ the_struct, RValue(variable_name) }
	);
}

void ModifyStamina(CInstance* Self, CInstance* Other, int value)
{
	CScript* gml_script_modify_stamina = nullptr;
	g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_MODIFY_STAMINA,
		(PVOID*)&gml_script_modify_stamina
	);

	RValue result;
	RValue stamina_modifier = value;
	RValue* stamina_modifier_ptr = &stamina_modifier;

	gml_script_modify_stamina->m_Functions->m_ScriptFunction(
		Self,
		Other,
		result,
		1,
		{ &stamina_modifier_ptr }
	);
}

void ObjectCallback(
	IN FWCodeEvent& CodeEvent
)
{
	auto& [self, other, code, argc, argv] = CodeEvent.Arguments();

	if (!self)
		return;

	if (!self->m_Object)
		return;

	if (strstr(self->m_Object->m_Name, "obj_ari"))
	{
		if (!script_name_to_reference_map.contains("obj_ari"))
			script_name_to_reference_map["obj_ari"] = { global_instance->GetRefMember("__ari")->ToInstance(), self };
	}

	// This works to remove the shop object, not the actual wagon sprite though
	//if (strstr(self->m_Object->m_Name, "obj_balors_wagon"))
	//{
	//	RValue instance_exists = g_ModuleInterface->CallBuiltin("instance_exists", { self });
	//	if (instance_exists.ToBoolean())
	//		g_ModuleInterface->CallBuiltin("instance_destroy", { self });
	//}
}

RValue& GmlScriptNodeObjectSetSpriteCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{


	// Self is the node renderer


	if (ArgumentCount > 0 && Arguments[0]->m_Kind == VALUE_REF)
	{
		RValue type = g_ModuleInterface->CallBuiltin("asset_get_type", { *Arguments[0] });
		if (type.ToInt64() == 1) // asset_sprite
		{
			RValue sprite_name = g_ModuleInterface->CallBuiltin("sprite_get_name", { *Arguments[0] });
			std::string sprite_name_str = sprite_name.ToString();

			if (sprite_name_str.contains("stage") && (sprite_name_str.contains("crop") || sprite_name_str.contains("forage")))
			{
				// Self->Node
				RValue node = Self->GetMember("node");

				//g_ModuleInterface->Print(CM_WHITE, "ENTER: %s", GML_SCRIPT_NODE_OBJECT_SET_SPRITE);
				//g_ModuleInterface->Print(CM_WHITE, "=============== %s ===============", "Self");
				//g_ModuleInterface->EnumInstanceMembers(Self, EnumFunction);
				//g_ModuleInterface->Print(CM_WHITE, "=============== %s ===============", "Other");
				//g_ModuleInterface->EnumInstanceMembers(Other, EnumFunction);

				/*
					=============== Self.node ===============
					Member Name: regrow_cycle
					Member Name: prototype
					Member Name: day_count
					Member Name: write_size_x
					Member Name: write_size_y
					Member Name: renderer
					Member Name: object_id
					Member Name: top_left_x
					Member Name: stage
					Member Name: ctx
					Member Name: top_left_y
					Member Name: last_update
				*/

				if (StructVariableExists(node, "prototype"))
				{
					RValue prototype = node.GetMember("prototype");
					if (StructVariableExists(prototype, "category_id") && IsNumeric(prototype.GetMember("category_id")))
					{
						int category_id = prototype.GetMember("category_id").ToInt64();
						if (category_id == 3) // don't hardcode this
						{
							int day_count = node.GetMember("day_count").ToInt64();
							bool stage_zero_is_seed = prototype.GetMember("stage_zero_is_seed").ToBoolean();
							bool regrow_cycle = node.GetMember("regrow_cycle").ToBoolean();

							RValue day_to_stage = prototype.GetMember("day_to_stage");
							RValue buffer = day_to_stage.GetMember("__buffer");

							int growth_days = g_ModuleInterface->CallBuiltin("array_length", { buffer }).ToInt64() - 1;
							growth_days = stage_zero_is_seed ? growth_days : growth_days - 1; // Adjust if stage 0 isn't a seed

							if (!regrow_cycle) // day_count <= growth_days
							{
								int days_remaining = growth_days - day_count;

								std::string replacement_sprite_name = sprite_name_str + "_timer_" + std::to_string(days_remaining);
								RValue replacement_sprite = g_ModuleInterface->CallBuiltin("asset_get_index", { replacement_sprite_name.c_str() });
								if (replacement_sprite.m_Kind == VALUE_REF)
									*Arguments[0] = replacement_sprite;

								//if (days_remaining == 0)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_zero" });
								//if (days_remaining == 1)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_one" });
								//if (days_remaining == 2)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_two" });
								//if (days_remaining == 3)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_three" });
								//if (days_remaining == 4)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_four" });
								//if (days_remaining == 5)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_five" });
								//if (days_remaining == 6)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_six" });

								int temp = 5;
							}
							else
							{
								RValue post_harvest_day_to_stage = prototype.GetMember("post_harvest_day_to_stage");
								RValue post_harvest_day_to_stage_buffer = post_harvest_day_to_stage.GetMember("__buffer");

								int regrowth_days = g_ModuleInterface->CallBuiltin("array_length", { post_harvest_day_to_stage_buffer }).ToInt64() - 1;
								int days_remaining = regrowth_days - day_count;

								//int days_since_first_harvest = day_count - growth_days;
								//int days_remaining = days_since_first_harvest % regrowth_days;

								std::string replacement_sprite_name = sprite_name_str + "_timer_" + std::to_string(days_remaining);
								RValue replacement_sprite = g_ModuleInterface->CallBuiltin("asset_get_index", { replacement_sprite_name.c_str() });
								if (replacement_sprite.m_Kind == VALUE_REF)
									*Arguments[0] = replacement_sprite;

								//if (days_remaining == 0)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_zero" });
								//if (days_remaining == 1)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_one" });
								//if (days_remaining == 2)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_two" });
								//if (days_remaining == 3)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_three" });
								//if (days_remaining == 4)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_four" });
								//if (days_remaining == 5)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_five" });
								//if (days_remaining == 6)
								//	*Arguments[0] = g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_bark_icon_six" });

								int temp = 5;
							}
						}
					}
				}
			}
				int temp = 5;
		}
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_NODE_OBJECT_SET_SPRITE));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	return Result;
}

RValue& GmlScriptUseItemCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	script_name_to_stamina_consumed_map.clear();

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_USE_ITEM));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	/*
	CRoom* current_room = nullptr;
	if (AurieSuccess(g_ModuleInterface->GetCurrentRoomData(current_room)))
	{
		for (CInstance* inst = current_room->GetMembers().m_ActiveInstances.m_First; inst != nullptr; inst = inst->GetMembers().m_Flink)
		{
			auto map = inst->ToRValue().ToRefMap();
			if (!map.contains("node")) continue;

			RValue* nodeValue = map["node"];
			if (!nodeValue || nodeValue->GetKindName() != "struct") continue;

			auto nodeRefMap = nodeValue->ToRefMap();
			if (!nodeRefMap.contains("prototype")) continue;

			RValue* protoVal = nodeRefMap["prototype"];
			if (!protoVal || protoVal->GetKindName() != "struct") continue;

			auto protoMap = protoVal->ToRefMap();
			if (!protoMap.contains("category_id")) continue;

			int category_id = protoMap["category_id"]->ToInt64();
			if (category_id != 3) continue; // TODO: Don't hardcode this

			//int stage = nodeRefMap["stage"]->ToInt64();
			int day_count = nodeRefMap["day_count"]->ToInt64();
			bool stage_zero_is_seed = protoMap["stage_zero_is_seed"]->ToBoolean();
			//bool regrow_cycle = nodeRefMap["regrow_cycle"]->ToBoolean();

			RValue* day_to_stage = protoMap["day_to_stage"];
			RValue buffer = day_to_stage->GetMember("__buffer");

			int growth_days = g_ModuleInterface->CallBuiltin("array_length", { buffer }).ToInt64() - 1;
			growth_days = stage_zero_is_seed ? growth_days : growth_days - 1; // Adjust if stage 0 isn't a seed

			if (day_count <= growth_days)
			{
				int days_remaining = growth_days - day_count;
				int temp = 5;
			}
			else
			{
				RValue* post_harvest_day_to_stage = protoMap["post_harvest_day_to_stage"];
				auto post_harvest_day_to_stage_map = post_harvest_day_to_stage->ToRefMap();

				int regrowth_days = g_ModuleInterface->CallBuiltin("array_length", { *post_harvest_day_to_stage }).ToInt64() - 1;
				int days_since_first_harvest = day_count - growth_days;
				int days_remaining = days_since_first_harvest % regrowth_days;


				int temp = 5;
			}

			int blah = 5;

			// --------------------------------------------------------------
			// TESTING DRAW STEP
			int x = nodeRefMap["top_left_x"]->ToInt64();
			int y = nodeRefMap["top_left_y"]->ToInt64();

			RValue sprite_index = g_ModuleInterface->CallBuiltin(
				"asset_get_index", {
					"spr_void_seal_stars_bg"
				}
			);

			// Draw sprite on top (centered)
			g_ModuleInterface->CallBuiltin(
				"draw_sprite",
				{
					RValue(sprite_index),
					RValue(-1),
					RValue(x * 8),
					RValue(y * 8)
				}
			);
			// --------------------------------------------------------------

			//if (!protoMap.contains("object_id")) continue;
			//int object_id = protoMap["object_id"]->ToInt64();



			//if (object_id == object_name_to_id_map[SUMMONING_CIRCLE_ITEM_NAME])
			//{
			//	int x = nodeRefMap["top_left_x"]->ToInt64();
			//	int y = nodeRefMap["top_left_y"]->ToInt64();
			//	existing_positions.emplace_back(x, y);
			//}
		}
	}
	*/

	return Result;
}

RValue& GmlScriptAriFsmHoeCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	stamina_consumed = false;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_HOE));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (stamina_consumed)
	{
		script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_HOE] += 1;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_HOE] % 3 == 0)
			ModifyStamina(script_name_to_reference_map["obj_ari"][0], script_name_to_reference_map["obj_ari"][1], 1);
	}
	stamina_consumed = false;

	return Result;
}

RValue& GmlScriptAriFsmAxeCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	stamina_consumed = false;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_AXE));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (stamina_consumed)
	{
		script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_AXE] += 1;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_AXE] % 3 == 0)
			ModifyStamina(script_name_to_reference_map["obj_ari"][0], script_name_to_reference_map["obj_ari"][1], 1);
	}
	stamina_consumed = false;

	return Result;
}

RValue& GmlScriptAriFsmPickAxeCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	stamina_consumed = false;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_PICK_AXE));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (stamina_consumed)
	{
		script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_PICK_AXE] += 1;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_PICK_AXE] % 3 == 0)
			ModifyStamina(script_name_to_reference_map["obj_ari"][0], script_name_to_reference_map["obj_ari"][1], 1);
	}
	stamina_consumed = false;

	return Result;
}

RValue& GmlScriptAriFsmShovelCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	stamina_consumed = false;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_SHOVEL));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (stamina_consumed)
	{
		script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_SHOVEL] += 1;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_SHOVEL] % 3 == 0)
			ModifyStamina(script_name_to_reference_map["obj_ari"][0], script_name_to_reference_map["obj_ari"][1], 1);
	}
	stamina_consumed = false;

	return Result;
}

RValue& GmlScriptAriFsmNetCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	stamina_consumed = false;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_NET));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (stamina_consumed)
	{
		script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_NET] += 1;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_NET] % 3 == 0)
			ModifyStamina(script_name_to_reference_map["obj_ari"][0], script_name_to_reference_map["obj_ari"][1], 1);
	}
	stamina_consumed = false;

	return Result;
}

RValue& GmlScriptAriFsmWateringCanCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_WATERING_CAN] += 1;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_WATERING_CAN));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	return Result;
}

RValue& GmlScriptAriFsmSowCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	stamina_consumed = false;

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_ARI_FSM_SOW));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (stamina_consumed)
	{
		script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_SOW] += 1;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_SOW] % 3 == 0)
			ModifyStamina(script_name_to_reference_map["obj_ari"][0], script_name_to_reference_map["obj_ari"][1], 1);
	}
	stamina_consumed = false;

	return Result;
}

RValue& GmlScriptModifyStaminaCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	if (Arguments[0]->ToInt64() < 0)
	{
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_WATERING_CAN] % 3 == 0)
			*Arguments[0] = 0;
		if (script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_WATERING_CAN] > 0)
			script_name_to_stamina_consumed_map[GML_SCRIPT_ARI_FSM_WATERING_CAN] -= 1;
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_MODIFY_STAMINA));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (Arguments[0]->ToInt64() < 0)
		stamina_consumed = true;

	return Result;
}

RValue& GmlScriptSetupMainScreenCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	if (load_on_start)
	{
		load_on_start = false;
		g_ModuleInterface->GetGlobalInstance(&global_instance);
	}

	// Reset static fields
	stamina_consumed = false;
	script_name_to_stamina_consumed_map = {};
	script_name_to_reference_map = {};

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_SETUP_MAIN_SCREEN));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	return Result;
}

void CreateObjectCallback(AurieStatus& status)
{
	status = g_ModuleInterface->CreateCallback(
		g_ArSelfModule,
		EVENT_OBJECT_CALL,
		ObjectCallback,
		0
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook (EVENT_OBJECT_CALL)!", MOD_NAME, VERSION);
	}
}

void CreateHookGmlScriptNodeObjectSetSprite(AurieStatus& status)
{
	CScript* gml_script_node_object_set_sprite = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_NODE_OBJECT_SET_SPRITE,
		(PVOID*)&gml_script_node_object_set_sprite
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_NODE_OBJECT_SET_SPRITE);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_NODE_OBJECT_SET_SPRITE,
		gml_script_node_object_set_sprite->m_Functions->m_ScriptFunction,
		GmlScriptNodeObjectSetSpriteCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_NODE_OBJECT_SET_SPRITE);
	}
}

void CreateHookGmlScriptUseItem(AurieStatus& status)
{
	CScript* gml_script_use_item = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_USE_ITEM,
		(PVOID*)&gml_script_use_item
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_USE_ITEM);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_USE_ITEM,
		gml_script_use_item->m_Functions->m_ScriptFunction,
		GmlScriptUseItemCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_USE_ITEM);
	}
}

void CreateHookGmlScriptAriFsmHoe(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_hoe = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_HOE,
		(PVOID*)&gml_script_ari_fsm_hoe
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_HOE);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_HOE,
		gml_script_ari_fsm_hoe->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmHoeCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_HOE);
	}
}

void CreateHookGmlScriptAriFsmAxe(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_axe = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_AXE,
		(PVOID*)&gml_script_ari_fsm_axe
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_AXE);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_AXE,
		gml_script_ari_fsm_axe->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmAxeCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_AXE);
	}
}

void CreateHookGmlScriptAriFsmPickAxe(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_pick_axe = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_PICK_AXE,
		(PVOID*)&gml_script_ari_fsm_pick_axe
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_PICK_AXE);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_PICK_AXE,
		gml_script_ari_fsm_pick_axe->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmPickAxeCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_PICK_AXE);
	}
}

void CreateHookGmlScriptAriFsmShovel(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_shovel = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_SHOVEL,
		(PVOID*)&gml_script_ari_fsm_shovel
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_SHOVEL);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_SHOVEL,
		gml_script_ari_fsm_shovel->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmShovelCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_SHOVEL);
	}
}

void CreateHookGmlScriptAriFsmNet(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_net = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_NET,
		(PVOID*)&gml_script_ari_fsm_net
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_NET);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_NET,
		gml_script_ari_fsm_net->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmNetCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_NET);
	}
}

void CreateHookGmlScriptAriFsmWateringCan(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_watering_can = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_WATERING_CAN,
		(PVOID*)&gml_script_ari_fsm_watering_can
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_WATERING_CAN);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_WATERING_CAN,
		gml_script_ari_fsm_watering_can->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmWateringCanCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_WATERING_CAN);
	}
}

void CreateHookGmlScriptAriFsmSow(AurieStatus& status)
{
	CScript* gml_script_ari_fsm_sow = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_ARI_FSM_SOW,
		(PVOID*)&gml_script_ari_fsm_sow
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_SOW);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_ARI_FSM_SOW,
		gml_script_ari_fsm_sow->m_Functions->m_ScriptFunction,
		GmlScriptAriFsmSowCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_ARI_FSM_SOW);
	}
}

void CreateHookGmlScriptModifyStamina(AurieStatus& status)
{
	CScript* gml_script_modify_stamina = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_MODIFY_STAMINA,
		(PVOID*)&gml_script_modify_stamina
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_MODIFY_STAMINA);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_MODIFY_STAMINA,
		gml_script_modify_stamina->m_Functions->m_ScriptFunction,
		GmlScriptModifyStaminaCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_MODIFY_STAMINA);
	}
}

void CreateHookGmlScriptSetupMainScreen(AurieStatus& status)
{
	CScript* gml_script_setup_main_screen = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_SETUP_MAIN_SCREEN,
		(PVOID*)&gml_script_setup_main_screen
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to get script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_SETUP_MAIN_SCREEN);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		GML_SCRIPT_SETUP_MAIN_SCREEN,
		gml_script_setup_main_screen->m_Functions->m_ScriptFunction,
		GmlScriptSetupMainScreenCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Failed to hook script (%s)!", MOD_NAME, VERSION, GML_SCRIPT_SETUP_MAIN_SCREEN);
	}
}

EXPORTED AurieStatus ModuleInitialize(IN AurieModule* Module, IN const fs::path& ModulePath) {
	UNREFERENCED_PARAMETER(ModulePath);

	AurieStatus status = AURIE_SUCCESS;

	status = ObGetInterface(
		"YYTK_Main",
		(AurieInterfaceBase*&)(g_ModuleInterface)
	);

	if (!AurieSuccess(status))
		return AURIE_MODULE_DEPENDENCY_NOT_RESOLVED;

	g_ModuleInterface->Print(CM_LIGHTAQUA, "[%s %s] - Plugin starting...", MOD_NAME, VERSION);

	CreateObjectCallback(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
		return status;
	}

	CreateHookGmlScriptNodeObjectSetSprite(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
		return status;
	}

	//CreateHookGmlScriptUseItem(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmHoe(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmAxe(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmPickAxe(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmShovel(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmNet(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmWateringCan(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptAriFsmSow(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	//CreateHookGmlScriptModifyStamina(status);
	//if (!AurieSuccess(status))
	//{
	//	g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
	//	return status;
	//}

	CreateHookGmlScriptSetupMainScreen(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[%s %s] - Exiting due to failure on start!", MOD_NAME, VERSION);
		return status;
	}

	g_ModuleInterface->Print(CM_LIGHTGREEN, "[%s %s] - Plugin started!", MOD_NAME, VERSION);
	return AURIE_SUCCESS;
}