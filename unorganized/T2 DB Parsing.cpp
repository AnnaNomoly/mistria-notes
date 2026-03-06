RValue GetNpcFromDatabase(int npc_id)
{
	RValue __npc_database = global_instance->GetMember("__npc_database");
	return g_ModuleInterface->CallBuiltin("array_get", { __npc_database, npc_id });
}

int GetNpcHeartPoints(RValue npc)
{
	return npc.GetMember("heart_points").ToInt64();
}

bool GetNpcGiftFlag(RValue npc)
{
	return npc.GetMember("gift_flag").ToBoolean();
}

RValue ReadValueFromT2Database(std::string t2_key, CInstance* Self, CInstance* Other)
{
	CScript* gml_script = nullptr;
	g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_read@T2r@T2r",
		(PVOID*)&gml_script
	);

	RValue result;
	RValue input = RValue(t2_key);
	RValue* input_ptr = &input;
	gml_script->m_Functions->m_ScriptFunction(
		Self,
		Other,
		result,
		1,
		{ &input_ptr }
	);

	return result;
}


// ========================================================================================

static const char* const GML_SCRIPT_T2_READ = "gml_Script_read@T2r@T2r";
static const char* const GML_SCRIPT_T2_WRITE = "gml_Script_write@T2r@T2r";

RValue T2Read(std::string key, CInstance* Self, CInstance* Other)
{
	CScript* gml_script_get_localizer = nullptr;
	g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_T2_READ,
		(PVOID*)&gml_script_get_localizer
	);

	RValue result;
	RValue input = RValue(key);
	RValue* input_ptr = &input;
	gml_script_get_localizer->m_Functions->m_ScriptFunction(
		Self,
		Other,
		result,
		1,
		{ &input_ptr }
	);

	return result;
}

void T2WriteString(std::string key, std::string value, CInstance* Self, CInstance* Other)
{
	CScript* script = nullptr;
	g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_T2_WRITE,
		(PVOID*)&script
	);

	RValue _key = RValue(key);
	RValue _value = RValue(value);
	RValue* key_ptr = &_key;
	RValue* value_ptr = &_value;
	RValue* rvalue_array[2] = { key_ptr, value_ptr };
	RValue retval;
	script->m_Functions->m_ScriptFunction(
		Self,
		Other,
		retval,
		2,
		rvalue_array
	);
}

void T2WriteDouble(std::string key, double value, CInstance* Self, CInstance* Other)
{
	CScript* script = nullptr;
	g_ModuleInterface->GetNamedRoutinePointer(
		GML_SCRIPT_T2_WRITE,
		(PVOID*)&script
	);

	RValue _key = RValue(key);
	RValue _value = RValue(value);
	RValue* key_ptr = &_key;
	RValue* value_ptr = &_value;
	RValue* rvalue_array[2] = { key_ptr, value_ptr };
	RValue retval;
	script->m_Functions->m_ScriptFunction(
		Self,
		Other,
		retval,
		2,
		rvalue_array
	);
}

// ========================================================================================

RValue& GmlScriptT2ReadCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	if (!script_name_to_reference_map.contains(GML_SCRIPT_T2_READ))
		script_name_to_reference_map[GML_SCRIPT_T2_READ] = { Self, Other };

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_T2_READ));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	if (Arguments[0]->m_Kind == VALUE_STRING && Arguments[0]->ToString() == "eiland_status" && Result.m_Kind == VALUE_UNDEFINED)
	{
		T2WriteString("eiland_status", "romantic", Self, Other);
		Result = RValue("romantic");
	}

	std::string search = Arguments[0]->ToString();
	if (Arguments[0]->m_Kind == VALUE_STRING && search.contains("heart") && Result.m_Kind != VALUE_UNDEFINED)
	{
		int x = 1;
		int y = 2;
	}

	if (Arguments[0]->m_Kind == VALUE_STRING && Arguments[0]->ToString() == "water_seal" && Result.m_Kind != VALUE_UNDEFINED)
	{
		int x = 1;
		int y = 2;
	}
		// 

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
	if (Arguments[0]->m_Real < 0)
		Arguments[0]->m_Real = 0;

	if (script_name_to_reference_map.contains(GML_SCRIPT_T2_READ))
	{
		RValue valen_heart_event = T2Read("valen_heart_event", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		RValue juniper_heart_event = T2Read("juniper_heart_event", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		RValue water_seal = T2Read("water_seal", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		RValue fire_seal = T2Read("fire_seal", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		RValue cutscene_seen_valen_four_hearts = T2Read("cutscene_seen_valen_four_hearts", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);

		RValue cutscene_seen_eiland_six_hearts = T2Read("cutscene_seen_eiland_six_hearts", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		if (cutscene_seen_eiland_six_hearts.m_Kind == VALUE_REAL && cutscene_seen_eiland_six_hearts.ToDouble() == 0)
			T2WriteDouble("cutscene_seen_eiland_six_hearts", 1.0, script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);

		RValue cutscene_seen_eiland_eight_hearts = T2Read("cutscene_seen_eiland_eight_hearts", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		if (cutscene_seen_eiland_eight_hearts.m_Kind == VALUE_REAL && cutscene_seen_eiland_eight_hearts.ToDouble() == 0)
			T2WriteDouble("cutscene_seen_eiland_eight_hearts", 1.0, script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);

		RValue eiland_post_8h_romantic_grouping = T2Read("eiland_post_8h_romantic_grouping", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);
		if (eiland_post_8h_romantic_grouping.m_Kind == VALUE_REAL && eiland_post_8h_romantic_grouping.ToDouble() == 0)
			T2WriteDouble("eiland_post_8h_romantic_grouping", 2.0, script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);

		RValue cutscene_seen_juniper_eight_hearts = T2Read("cutscene_seen_juniper_eight_hearts", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]);

		RValue juniper_post_8h_romantic_grouping  = T2Read("juniper_post_8h_romantic_grouping", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]); // 2.0
		RValue juniper_post_8h_best_friend_gate = T2Read("juniper_post_8h_best_friend_gate", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]); // 0.0
		RValue juniper_post_8h_romantic_progression = T2Read("juniper_post_8h_romantic_progression", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]); // 0.0
		RValue juniper_post_8h_romantic_gate = T2Read("juniper_post_8h_romantic_gate", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]); // 0.0
		RValue juniper_post_8h_best_friend_grouping = T2Read("juniper_post_8h_best_friend_grouping", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]); // 0.0
		RValue juniper_8h_lead_up = T2Read("Cutscenes/Heart Events/Juniper/juniper_eight_hearts/juniper_eight_hearts_lead_up_juniper", script_name_to_reference_map[GML_SCRIPT_T2_READ][0], script_name_to_reference_map[GML_SCRIPT_T2_READ][1]); // 1.0

		// cutscene_seen_eiland_six_hearts
		// cutscene_seen_eiland_eight_hearts
		int temp = 5;
	}
	

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, GML_SCRIPT_MODIFY_HEALTH));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	return Result;
}