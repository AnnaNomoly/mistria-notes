#include <YYToolkit/Shared.hpp>
using namespace Aurie;
using namespace YYTK;

static const char* const VERSION = "1.0.1";

static const int INVALID_ID = -1;
static int BLACKBERRY_JAM_ITEM_ID = INVALID_ID;
static int BLUEBERRY_JAM_ITEM_ID = INVALID_ID;
static int MARMALADE_ITEM_ID = INVALID_ID;
static int ROSEHIP_JAM_ITEM_ID = INVALID_ID;
static int MINES_LOCATION_ID = INVALID_ID;
static int BEACH_LOCATION_ID = INVALID_ID;
static int TOWN_LOCATION_ID = INVALID_ID;
static int FARM_LOCATION_ID = INVALID_ID;

static const std::tuple<int, int> MINES_TELEPORT_POINT = std::make_tuple(216, 198);
static const std::tuple<int, int> BEACH_TELEPORT_POINT = std::make_tuple(1722, 505);
static const std::tuple<int, int> TOWN_TELEPORT_POINT = std::make_tuple(1097, 1323);
static const std::tuple<int, int> FARM_TELEPORT_POINT = std::make_tuple(809, 306);

static YYTKInterface* g_ModuleInterface = nullptr;
static int held_item_id = INVALID_ID;
static int telepop_destination_id = INVALID_ID;
static bool teleport_ari = false;
static bool reposition_ari = false;
static bool room_loaded = false;
static bool load_on_start = true;
static std::vector<std::string> struct_field_names = {};

bool EnumFunction(
	IN const char* MemberName,
	IN OUT RValue* Value
)
{
	g_ModuleInterface->Print(CM_LIGHTYELLOW, "Member Name: %s", MemberName);
	return false;
}

bool GetStructFieldNames(
	IN const char* MemberName,
	IN OUT RValue* Value
)
{
	struct_field_names.push_back(MemberName);
	return false;
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

	if (!strstr(self->m_Object->m_Name, "obj_ari"))
		return;

	if (teleport_ari)
	{
		CScript* gml_script_goto_location_id = nullptr;
		g_ModuleInterface->GetNamedRoutinePointer(
			"gml_Script_goto_location_id",
			(PVOID*)&gml_script_goto_location_id
		);

		RValue retval;
		RValue* location_id = new RValue(telepop_destination_id);
		gml_script_goto_location_id->m_Functions->m_ScriptFunction(
			self,
			other,
			retval,
			1,
			{ &location_id }
		);
		delete location_id;

		teleport_ari = false;
		reposition_ari = true;

		if (telepop_destination_id == MINES_LOCATION_ID)
			g_ModuleInterface->Print(CM_LIGHTGREEN, "[Telepop %s] - Ari teleported to Mines!", VERSION);
		if (telepop_destination_id == BEACH_LOCATION_ID)
			g_ModuleInterface->Print(CM_LIGHTGREEN, "[Telepop %s] - Ari teleported to Beach!", VERSION);
		if (telepop_destination_id == TOWN_LOCATION_ID)
			g_ModuleInterface->Print(CM_LIGHTGREEN, "[Telepop %s] - Ari teleported to Town!", VERSION);
		if (telepop_destination_id == FARM_LOCATION_ID)
			g_ModuleInterface->Print(CM_LIGHTGREEN, "[Telepop %s] - Ari teleported to Farm!", VERSION);
	}
	else if (reposition_ari && room_loaded) {
		RValue x;
		RValue y;
		
		if (telepop_destination_id == MINES_LOCATION_ID) {
			x = std::get<0>(MINES_TELEPORT_POINT);
			y = std::get<1>(MINES_TELEPORT_POINT);
		}

		if (telepop_destination_id == BEACH_LOCATION_ID) {
			x = std::get<0>(BEACH_TELEPORT_POINT);
			y = std::get<1>(BEACH_TELEPORT_POINT);
		}

		if (telepop_destination_id == TOWN_LOCATION_ID) {
			x = std::get<0>(TOWN_TELEPORT_POINT);
			y = std::get<1>(TOWN_TELEPORT_POINT);
		}

		if (telepop_destination_id == FARM_LOCATION_ID) {
			x = std::get<0>(FARM_TELEPORT_POINT);
			y = std::get<1>(FARM_TELEPORT_POINT);
		}

		g_ModuleInterface->SetBuiltin("x", self, NULL_INDEX, x);
		g_ModuleInterface->SetBuiltin("y", self, NULL_INDEX, y);

		held_item_id = INVALID_ID;
		telepop_destination_id = INVALID_ID;

		reposition_ari = false;
		room_loaded = false;
	}
}

RValue& GmlScriptUseItemCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	g_ModuleInterface->Print(CM_WHITE, "ENTER: gml_Script_use_item. ArgCount: %d", ArgumentCount);
	// Arguments
	for (int i = 0; i < ArgumentCount; i++)
	{
		g_ModuleInterface->Print(CM_WHITE, "=============== Argument[%d] ===============", i);
		if (Arguments[i]->m_Kind == VALUE_OBJECT)
		{
			g_ModuleInterface->Print(CM_AQUA, "OBJECT:");
			struct_field_names = {};
			g_ModuleInterface->EnumInstanceMembers(Arguments[i]->m_Object, GetStructFieldNames);
			for (int j = 0; j < struct_field_names.size(); j++)
			{
				std::string field_name = struct_field_names[j];
				RValue field = Arguments[i]->m_Object->at(field_name);
				if (field.m_Kind == VALUE_OBJECT)
				{
					g_ModuleInterface->Print(CM_AQUA, "%s: OBJECT", field_name.c_str());
					g_ModuleInterface->EnumInstanceMembers(field, EnumFunction);
					g_ModuleInterface->Print(CM_WHITE, "------------------------------");
				}
				else if (field.m_Kind == VALUE_ARRAY)
				{
					RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { field });
					g_ModuleInterface->Print(CM_AQUA, "%s: ARRAY (length == %d)", field_name.c_str(), static_cast<int>(array_length.m_Real));
					for (int k = 0; k < array_length.m_Real; k++)
					{
						//INT64 == 956
						RValue array_element = g_ModuleInterface->CallBuiltin("array_get", { field, k });
						int temp = 5;
					}
				}
				else if (field.m_Kind == VALUE_INT32)
					g_ModuleInterface->Print(CM_AQUA, "%s: INT32 == %d", field_name.c_str(), field.m_i32);
				else if (field.m_Kind == VALUE_INT64)
					g_ModuleInterface->Print(CM_AQUA, "%s: INT64 == %d", field_name.c_str(), field.m_i64);
				else if (field.m_Kind == VALUE_REAL)
					g_ModuleInterface->Print(CM_AQUA, "%s: REAL == %f", field_name.c_str(), field.m_Real);
				else if (field.m_Kind == VALUE_BOOL)
					g_ModuleInterface->Print(CM_AQUA, "%s: BOOL == %s", field_name.c_str(), field.m_Real == 0 ? "false" : "true");
				else if (field.m_Kind == VALUE_STRING)
					g_ModuleInterface->Print(CM_AQUA, "%s: STRING == %s", field_name.c_str(), field.AsString().data());
				else
					g_ModuleInterface->Print(CM_AQUA, "%s: OTHER", field_name.c_str());
			}
		}
		else if (Arguments[i]->m_Kind == VALUE_ARRAY)
		{
			RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { Arguments[i] });
			g_ModuleInterface->Print(CM_AQUA, "ARRAY: (length == %d)", static_cast<int>(array_length.m_Real));
		}
		else if (Arguments[i]->m_Kind == VALUE_INT32)
			g_ModuleInterface->Print(CM_AQUA, "INT32: %d", Arguments[i]->m_i32);
		else if (Arguments[i]->m_Kind == VALUE_INT64)
			g_ModuleInterface->Print(CM_AQUA, "INT64: %d", Arguments[i]->m_i64);
		else if (Arguments[i]->m_Kind == VALUE_REAL)
			g_ModuleInterface->Print(CM_AQUA, "REAL: %f", Arguments[i]->m_Real);
		else if (Arguments[i]->m_Kind == VALUE_BOOL)
			g_ModuleInterface->Print(CM_AQUA, "BOOL: %s", Arguments[i]->m_Real == 0 ? "false" : "true");
		else if (Arguments[i]->m_Kind == VALUE_STRING)
			g_ModuleInterface->Print(CM_AQUA, "STRING: %s", Arguments[i]->AsString().data());
		else
			g_ModuleInterface->Print(CM_AQUA, "OTHER");
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_use_item"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	// Result
	g_ModuleInterface->Print(CM_WHITE, "=============== Result ===============");
	if (Result.m_Kind == VALUE_OBJECT)
	{
		g_ModuleInterface->Print(CM_AQUA, "OBJECT:");
		g_ModuleInterface->EnumInstanceMembers(Result, EnumFunction);
		g_ModuleInterface->Print(CM_WHITE, "------------------------------");
	}
	else if (Result.m_Kind == VALUE_ARRAY)
	{
		RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { Result });
		g_ModuleInterface->Print(CM_AQUA, "ARRAY: (length == %d)", static_cast<int>(array_length.m_Real));
	}
	else if (Result.m_Kind == VALUE_INT32)
		g_ModuleInterface->Print(CM_AQUA, "INT32: %d", Result.m_i32);
	else if (Result.m_Kind == VALUE_INT64)
		g_ModuleInterface->Print(CM_AQUA, "INT64: %d", Result.m_i64);
	else if (Result.m_Kind == VALUE_REAL)
		g_ModuleInterface->Print(CM_AQUA, "REAL: %f", Result.m_Real);
	else if (Result.m_Kind == VALUE_BOOL)
		g_ModuleInterface->Print(CM_AQUA, "BOOL: %s", Result.m_Real == 0 ? "false" : "true");
	else if (Result.m_Kind == VALUE_STRING)
		g_ModuleInterface->Print(CM_AQUA, "STRING: %s", Result.AsString().data());
	else
		g_ModuleInterface->Print(CM_AQUA, "OTHER");

	g_ModuleInterface->Print(CM_WHITE, "EXIT: gml_Script_use_item. ArgCount: %d", ArgumentCount);
	return Result;
}

RValue& GmlScriptInventoryPopCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	g_ModuleInterface->Print(CM_WHITE, "ENTER: gml_Script_pop@InventorySlot@Inventory. ArgCount: %d", ArgumentCount);
	// Arguments
	for (int i = 0; i < ArgumentCount; i++)
	{
		g_ModuleInterface->Print(CM_WHITE, "=============== Argument[%d] ===============", i);
		if (Arguments[i]->m_Kind == VALUE_OBJECT)
		{
			g_ModuleInterface->Print(CM_AQUA, "OBJECT:");
			struct_field_names = {};
			g_ModuleInterface->EnumInstanceMembers(Arguments[i]->m_Object, GetStructFieldNames);
			for (int j = 0; j < struct_field_names.size(); j++)
			{
				std::string field_name = struct_field_names[j];
				RValue field = Arguments[i]->m_Object->at(field_name);
				if (field.m_Kind == VALUE_OBJECT)
				{
					g_ModuleInterface->Print(CM_AQUA, "%s: OBJECT", field_name.c_str());
					g_ModuleInterface->EnumInstanceMembers(field, EnumFunction);
					g_ModuleInterface->Print(CM_WHITE, "------------------------------");
				}
				else if (field.m_Kind == VALUE_ARRAY)
				{
					RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { field });
					g_ModuleInterface->Print(CM_AQUA, "%s: ARRAY (length == %d)", field_name.c_str(), static_cast<int>(array_length.m_Real));
					for (int k = 0; k < array_length.m_Real; k++)
					{
						//INT64 == 956
						RValue array_element = g_ModuleInterface->CallBuiltin("array_get", { field, k });
						int temp = 5;
					}
				}
				else if (field.m_Kind == VALUE_INT32)
					g_ModuleInterface->Print(CM_AQUA, "%s: INT32 == %d", field_name.c_str(), field.m_i32);
				else if (field.m_Kind == VALUE_INT64)
					g_ModuleInterface->Print(CM_AQUA, "%s: INT64 == %d", field_name.c_str(), field.m_i64);
				else if (field.m_Kind == VALUE_REAL)
					g_ModuleInterface->Print(CM_AQUA, "%s: REAL == %f", field_name.c_str(), field.m_Real);
				else if (field.m_Kind == VALUE_BOOL)
					g_ModuleInterface->Print(CM_AQUA, "%s: BOOL == %s", field_name.c_str(), field.m_Real == 0 ? "false" : "true");
				else if (field.m_Kind == VALUE_STRING)
					g_ModuleInterface->Print(CM_AQUA, "%s: STRING == %s", field_name.c_str(), field.AsString().data());
				else
					g_ModuleInterface->Print(CM_AQUA, "%s: OTHER", field_name.c_str());
			}
		}
		else if (Arguments[i]->m_Kind == VALUE_ARRAY)
		{
			RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { Arguments[i] });
			g_ModuleInterface->Print(CM_AQUA, "ARRAY: (length == %d)", static_cast<int>(array_length.m_Real));
		}
		else if (Arguments[i]->m_Kind == VALUE_INT32)
			g_ModuleInterface->Print(CM_AQUA, "INT32: %d", Arguments[i]->m_i32);
		else if (Arguments[i]->m_Kind == VALUE_INT64)
			g_ModuleInterface->Print(CM_AQUA, "INT64: %d", Arguments[i]->m_i64);
		else if (Arguments[i]->m_Kind == VALUE_REAL)
			g_ModuleInterface->Print(CM_AQUA, "REAL: %f", Arguments[i]->m_Real);
		else if (Arguments[i]->m_Kind == VALUE_BOOL)
			g_ModuleInterface->Print(CM_AQUA, "BOOL: %s", Arguments[i]->m_Real == 0 ? "false" : "true");
		else if (Arguments[i]->m_Kind == VALUE_STRING)
			g_ModuleInterface->Print(CM_AQUA, "STRING: %s", Arguments[i]->AsString().data());
		else
			g_ModuleInterface->Print(CM_AQUA, "OTHER");
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_pop@InventorySlot@Inventory"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	// Result
	g_ModuleInterface->Print(CM_WHITE, "=============== Result ===============");
	if (Result.m_Kind == VALUE_OBJECT)
	{
		g_ModuleInterface->Print(CM_AQUA, "OBJECT:");
		g_ModuleInterface->EnumInstanceMembers(Result, EnumFunction);
		g_ModuleInterface->Print(CM_WHITE, "------------------------------");
	}
	else if (Result.m_Kind == VALUE_ARRAY)
	{
		RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { Result });
		g_ModuleInterface->Print(CM_AQUA, "ARRAY: (length == %d)", static_cast<int>(array_length.m_Real));
	}
	else if (Result.m_Kind == VALUE_INT32)
		g_ModuleInterface->Print(CM_AQUA, "INT32: %d", Result.m_i32);
	else if (Result.m_Kind == VALUE_INT64)
		g_ModuleInterface->Print(CM_AQUA, "INT64: %d", Result.m_i64);
	else if (Result.m_Kind == VALUE_REAL)
		g_ModuleInterface->Print(CM_AQUA, "REAL: %f", Result.m_Real);
	else if (Result.m_Kind == VALUE_BOOL)
		g_ModuleInterface->Print(CM_AQUA, "BOOL: %s", Result.m_Real == 0 ? "false" : "true");
	else if (Result.m_Kind == VALUE_STRING)
		g_ModuleInterface->Print(CM_AQUA, "STRING: %s", Result.AsString().data());
	else
		g_ModuleInterface->Print(CM_AQUA, "OTHER");

	g_ModuleInterface->Print(CM_WHITE, "EXIT: gml_Script_pop@InventorySlot@Inventory. ArgCount: %d", ArgumentCount);
	return Result;
}

RValue& GmlScriptHeldItemCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_held_item@Ari@Ari"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (Result.m_Kind != VALUE_UNDEFINED)
	{
		if (held_item_id != Result.at("item_id").m_i64 && !teleport_ari)
		{
			held_item_id = Result.at("item_id").m_i64;
		}
	}

	return Result;
}

RValue& GmlScriptModifyHealthCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	if (held_item_id == BLACKBERRY_JAM_ITEM_ID) {
		teleport_ari = true;
		telepop_destination_id = MINES_LOCATION_ID;
		held_item_id = INVALID_ID;
	}

	if (held_item_id == BLUEBERRY_JAM_ITEM_ID) {
		teleport_ari = true;
		telepop_destination_id = BEACH_LOCATION_ID;
		held_item_id = INVALID_ID;
	}

	if (held_item_id == MARMALADE_ITEM_ID) {
		teleport_ari = true;
		telepop_destination_id = TOWN_LOCATION_ID;
		held_item_id = INVALID_ID;
	}

	if (held_item_id == ROSEHIP_JAM_ITEM_ID) {
		teleport_ari = true;
		telepop_destination_id = FARM_LOCATION_ID;
		held_item_id = INVALID_ID;
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_modify_health@Ari@Ari"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	return Result;
}

RValue& GmlScriptShowRoomTitleCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	if (reposition_ari) {
		room_loaded = true;
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_show_room_title"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

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
	held_item_id = INVALID_ID;
	telepop_destination_id = INVALID_ID;
	teleport_ari = false;
	room_loaded = false;

	if (load_on_start)
	{
		// Load item IDs.
		CScript* gml_script_try_string_to_item_id = nullptr;
		g_ModuleInterface->GetNamedRoutinePointer(
			"gml_Script_try_string_to_item_id",
			(PVOID*)&gml_script_try_string_to_item_id
		);

		std::vector<const char*> item_names = {"blackberry_jam", "blueberry_jam", "marmalade", "rosehip_jam"};
		for (size_t i = 0; i < item_names.size(); i++)
		{
			RValue* item_name = new RValue(item_names[i]);
			RValue item_id;
			gml_script_try_string_to_item_id->m_Functions->m_ScriptFunction(
				Self,
				Other,
				item_id,
				1,
				{ &item_name }
			);
			delete item_name;

			if (strcmp(item_names[i], "blackberry_jam") == 0)
				BLACKBERRY_JAM_ITEM_ID = item_id.m_i64;
			if (strcmp(item_names[i], "blueberry_jam") == 0)
				BLUEBERRY_JAM_ITEM_ID = item_id.m_i64;
			if (strcmp(item_names[i], "marmalade") == 0)
				MARMALADE_ITEM_ID = item_id.m_i64;
			if (strcmp(item_names[i], "rosehip_jam") == 0)
				ROSEHIP_JAM_ITEM_ID = item_id.m_i64;
		}

		if (BLACKBERRY_JAM_ITEM_ID == INVALID_ID || BLUEBERRY_JAM_ITEM_ID == INVALID_ID || MARMALADE_ITEM_ID == INVALID_ID || ROSEHIP_JAM_ITEM_ID == INVALID_ID)
			g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to load item IDs!", VERSION);

		// Load location IDs.
		CScript* gml_script_try_string_to_location_id = nullptr;
		g_ModuleInterface->GetNamedRoutinePointer(
			"gml_Script_try_string_to_location_id",
			(PVOID*)&gml_script_try_string_to_location_id
		);

		std::vector<const char*> location_names = { "mines_entry", "beach", "town", "farm" };
		for (size_t i = 0; i < location_names.size(); i++)
		{
			RValue* location_name = new RValue(location_names[i]);
			RValue location_id;
			gml_script_try_string_to_location_id->m_Functions->m_ScriptFunction(
				Self,
				Other,
				location_id,
				1,
				{ &location_name }
			);
			delete location_name;

			if (strcmp(location_names[i], "mines_entry") == 0)
				MINES_LOCATION_ID = location_id.m_i64;
			if (strcmp(location_names[i], "beach") == 0)
				BEACH_LOCATION_ID = location_id.m_i64;
			if (strcmp(location_names[i], "town") == 0)
				TOWN_LOCATION_ID = location_id.m_i64;
			if (strcmp(location_names[i], "farm") == 0)
				FARM_LOCATION_ID = location_id.m_i64;
		}

		if (MINES_LOCATION_ID == INVALID_ID || BEACH_LOCATION_ID == INVALID_ID || TOWN_LOCATION_ID == INVALID_ID || FARM_LOCATION_ID == INVALID_ID)
			g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to location IDs!", VERSION);

		load_on_start = false;
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_setup_main_screen@TitleMenu@TitleMenu"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	return Result;
}

void CreateHookGmlScriptUseItem(AurieStatus& status)
{
	CScript* gml_script_use_item = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_use_item",
		(PVOID*)&gml_script_use_item
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to get script (gml_Script_use_item)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_use_item",
		gml_script_use_item->m_Functions->m_ScriptFunction,
		GmlScriptUseItemCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to hook script (gml_Script_use_item)!", VERSION);
	}
}

void CreateHookGmlScriptInventoryPop(AurieStatus& status)
{
	CScript* gml_script_inventory_pop = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_pop@InventorySlot@Inventory",
		(PVOID*)&gml_script_inventory_pop
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to get script (gml_Script_pop@InventorySlot@Inventory)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_pop@InventorySlot@Inventory",
		gml_script_inventory_pop->m_Functions->m_ScriptFunction,
		GmlScriptInventoryPopCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to hook script (gml_Script_pop@InventorySlot@Inventory)!", VERSION);
	}
}

void CreateHookGmlScriptHeldItem(AurieStatus& status)
{
	CScript* gml_script_held_item = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_held_item@Ari@Ari",
		(PVOID*)&gml_script_held_item
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to get script (gml_Script_held_item@Ari@Ari)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_held_item@Ari@Ari",
		gml_script_held_item->m_Functions->m_ScriptFunction,
		GmlScriptHeldItemCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to hook script (gml_Script_held_item@Ari@Ari)!", VERSION);
	}
}

void CreateHookGmlScriptModifyHealth(AurieStatus& status)
{
	CScript* gml_script_modify_stamina = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_modify_health@Ari@Ari",
		(PVOID*)&gml_script_modify_stamina
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to get script (gml_Script_modify_health@Ari@Ari)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_modify_health@Ari@Ari",
		gml_script_modify_stamina->m_Functions->m_ScriptFunction,
		GmlScriptModifyHealthCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to hook script (gml_Script_modify_health@Ari@Ari)!", VERSION);
	}
}

void CreateHookGmlScriptShowRoomTitle(AurieStatus& status)
{
	CScript* gml_script_show_room_title = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_show_room_title",
		(PVOID*)&gml_script_show_room_title
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to get script (gml_Script_show_room_title)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_show_room_title",
		gml_script_show_room_title->m_Functions->m_ScriptFunction,
		GmlScriptShowRoomTitleCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to hook script (gml_Script_show_room_title)!", VERSION);
	}
}

void CreateHookGmlScriptSetupMainScreen(AurieStatus& status)
{
	CScript* gml_script_setup_main_screen = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_setup_main_screen@TitleMenu@TitleMenu",
		(PVOID*)&gml_script_setup_main_screen
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to get script (gml_Script_setup_main_screen@TitleMenu@TitleMenu)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_setup_main_screen@TitleMenu@TitleMenu",
		gml_script_setup_main_screen->m_Functions->m_ScriptFunction,
		GmlScriptSetupMainScreenCallback,
		nullptr
	);


	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Failed to hook script (gml_Script_setup_main_screen@TitleMenu@TitleMenu)!", VERSION);
	}
}

EXPORTED AurieStatus ModuleInitialize(
	IN AurieModule* Module,
	IN const fs::path& ModulePath
)
{
	UNREFERENCED_PARAMETER(ModulePath);

	AurieStatus status = AURIE_SUCCESS;
	
	status = ObGetInterface(
		"YYTK_Main", 
		(AurieInterfaceBase*&)(g_ModuleInterface)
	);

	if (!AurieSuccess(status))
		return AURIE_MODULE_DEPENDENCY_NOT_RESOLVED;

	g_ModuleInterface->Print(CM_LIGHTAQUA, "[Telepop %s] - Plugin starting...", VERSION);
	
	g_ModuleInterface->CreateCallback(
		g_ArSelfModule,
		EVENT_OBJECT_CALL,
		ObjectCallback,
		0
	);

	CreateHookGmlScriptUseItem(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptInventoryPop(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptHeldItem(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptModifyHealth(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptShowRoomTitle(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptSetupMainScreen(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[Telepop %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	g_ModuleInterface->Print(CM_LIGHTGREEN, "[Telepop %s] - Plugin started!", VERSION);
	return AURIE_SUCCESS;
}