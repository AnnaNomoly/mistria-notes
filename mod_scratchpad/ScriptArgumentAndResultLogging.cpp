RValue& GmlScriptAriFsmWateringCanCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	g_ModuleInterface->Print(CM_WHITE, "ENTER: %s", GML_SCRIPT_DROP_ITEM);
	g_ModuleInterface->Print(CM_WHITE, "=============== %s ===============", "Self");
	g_ModuleInterface->EnumInstanceMembers(Self, EnumFunction);
	g_ModuleInterface->Print(CM_WHITE, "=============== %s ===============", "Other");
	g_ModuleInterface->EnumInstanceMembers(Other, EnumFunction);

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
				RValue field = *Arguments[i]->GetRefMember(field_name);
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
					g_ModuleInterface->Print(CM_AQUA, "%s: STRING == %s", field_name.c_str(), field.ToString().c_str());
				else if (field.m_Kind == VALUE_REF)
					g_ModuleInterface->Print(CM_AQUA, "%s: REFERENCE", field_name.c_str());
				else if (field.m_Kind == VALUE_NULL)
					g_ModuleInterface->Print(CM_AQUA, "%s: NULL", field_name.c_str());
				else if (field.m_Kind == VALUE_UNDEFINED)
					g_ModuleInterface->Print(CM_AQUA, "%s: UNDEFINED", field_name.c_str());
				else if (field.m_Kind == VALUE_UNSET)
					g_ModuleInterface->Print(CM_AQUA, "%s: UNSET", field_name.c_str());
				else
					g_ModuleInterface->Print(CM_AQUA, "%s: OTHER", field_name.c_str());
			}
		}
		else if (Arguments[i]->m_Kind == VALUE_ARRAY)
		{
			RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { *Arguments[i] });
			g_ModuleInterface->Print(CM_AQUA, "ARRAY (length == %d)", static_cast<int>(array_length.m_Real));
			for (int j = 0; j < array_length.m_Real; j++)
			{
				RValue array_element = g_ModuleInterface->CallBuiltin("array_get", { *Arguments[i], j });
				if (array_element.m_Kind == VALUE_OBJECT)
				{
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: OBJECT", j);
					g_ModuleInterface->EnumInstanceMembers(array_element, EnumFunction);
					g_ModuleInterface->Print(CM_WHITE, "------------------------------");

					// Test overriding the item.
					*array_element.GetRefMember("item_id") = item_name_to_id_map["sigil_of_alteration"];
					*array_element.GetRefMember("prototype") = item_id_to_prototype_map[item_name_to_id_map["sigil_of_alteration"]];
				}
				else if (array_element.m_Kind == VALUE_REAL)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: REAL: %f", j, array_element.m_Real);
				else if (array_element.m_Kind == VALUE_INT64)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: INT64: %d", j, array_element.m_i64);
				else if (array_element.m_Kind == VALUE_INT32)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: INT32: %d", j, array_element.m_i32);
				else if (array_element.m_Kind == VALUE_BOOL)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: BOOL: %s", j, array_element.m_Real == 0 ? "false" : "true");
				else if (array_element.m_Kind == VALUE_STRING)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: STRING: %s", j, array_element.ToString().c_str());
				else if (array_element.m_Kind == VALUE_REF)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: REFERENCE", j);
				else if (array_element.m_Kind == VALUE_NULL)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: NULL", j);
				else if (array_element.m_Kind == VALUE_UNDEFINED)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: UNDEFINED", j);
				else if (array_element.m_Kind == VALUE_UNSET)
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: UNSET", j);
				else
					g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: OTHER", j);
			}
		}
		else if (Arguments[i]->m_Kind == VALUE_REAL)
			g_ModuleInterface->Print(CM_AQUA, "REAL: %f", Arguments[i]->m_Real);
		else if (Arguments[i]->m_Kind == VALUE_INT64)
			g_ModuleInterface->Print(CM_AQUA, "INT64: %d", Arguments[i]->m_i64);
		else if (Arguments[i]->m_Kind == VALUE_INT32)
			g_ModuleInterface->Print(CM_AQUA, "INT32: %d", Arguments[i]->m_i32);
		else if (Arguments[i]->m_Kind == VALUE_BOOL)
			g_ModuleInterface->Print(CM_AQUA, "BOOL: %s", Arguments[i]->m_Real == 0 ? "false" : "true");
		else if (Arguments[i]->m_Kind == VALUE_STRING)
			g_ModuleInterface->Print(CM_AQUA, "STRING: %s", Arguments[i]->ToString().c_str());
		else if (Arguments[i]->m_Kind == VALUE_REF)
			g_ModuleInterface->Print(CM_AQUA, "REFERENCE");
		else if (Arguments[i]->m_Kind == VALUE_NULL)
			g_ModuleInterface->Print(CM_AQUA, "NULL");
		else if (Arguments[i]->m_Kind == VALUE_UNDEFINED)
			g_ModuleInterface->Print(CM_AQUA, "UNDEFINED");
		else if (Arguments[i]->m_Kind == VALUE_UNSET)
			g_ModuleInterface->Print(CM_AQUA, "UNSET");
		else
			g_ModuleInterface->Print(CM_AQUA, "OTHER");
	}

	const PFUNC_YYGMLScript original = reinterpret_cast<PFUNC_YYGMLScript>(MmGetHookTrampoline(g_ArSelfModule, "gml_Script_watering_can@anon@83944@AriFsm@AriFsm"));
	original(
		Self,
		Other,
		Result,
		ArgumentCount,
		Arguments
	);

	g_ModuleInterface->Print(CM_WHITE, "=============== Result ===============");
	if (Result.m_Kind == VALUE_OBJECT)
	{
		g_ModuleInterface->Print(CM_AQUA, "OBJECT");
		g_ModuleInterface->EnumInstanceMembers(Result, EnumFunction);
		g_ModuleInterface->Print(CM_WHITE, "------------------------------");
	}
	else if (Result.m_Kind == VALUE_ARRAY)
	{
		RValue array_length = g_ModuleInterface->CallBuiltin("array_length", { Result });
		g_ModuleInterface->Print(CM_AQUA, "ARRAY (length == %d)", static_cast<int>(array_length.m_Real));
		for (int i = 0; i < array_length.m_Real; i++)
		{
			RValue array_element = g_ModuleInterface->CallBuiltin("array_get", { Result[i], i });
			if (array_element.m_Kind == VALUE_OBJECT)
			{
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: OBJECT", i);
				g_ModuleInterface->EnumInstanceMembers(array_element, EnumFunction);
				g_ModuleInterface->Print(CM_WHITE, "------------------------------");

				// Test overriding the item.
				*array_element.GetRefMember("item_id") = item_name_to_id_map["sigil_of_alteration"];
				*array_element.GetRefMember("prototype") = item_id_to_prototype_map[item_name_to_id_map["sigil_of_alteration"]];
			}
			else if (array_element.m_Kind == VALUE_REAL)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: REAL: %f", i, array_element.m_Real);
			else if (array_element.m_Kind == VALUE_INT64)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: INT64: %d", i, array_element.m_i64);
			else if (array_element.m_Kind == VALUE_INT32)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: INT32: %d", i, array_element.m_i32);
			else if (array_element.m_Kind == VALUE_BOOL)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: BOOL: %s", i, array_element.m_Real == 0 ? "false" : "true");
			else if (array_element.m_Kind == VALUE_STRING)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: STRING: %s", i, array_element.ToString().c_str());
			else if (array_element.m_Kind == VALUE_REF)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: REFERENCE", i);
			else if (array_element.m_Kind == VALUE_NULL)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: NULL", i);
			else if (array_element.m_Kind == VALUE_UNDEFINED)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: UNDEFINED", i);
			else if (array_element.m_Kind == VALUE_UNSET)
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: UNSET", i);
			else
				g_ModuleInterface->Print(CM_AQUA, "ARRAY[%d]: OTHER", i);
		}
	}
	else if (Result.m_Kind == VALUE_INT32)
		g_ModuleInterface->Print(CM_AQUA, "INT32 == %d", Result.m_i32);
	else if (Result.m_Kind == VALUE_INT64)
		g_ModuleInterface->Print(CM_AQUA, "INT64 == %d", Result.m_i64);
	else if (Result.m_Kind == VALUE_REAL)
		g_ModuleInterface->Print(CM_AQUA, "REAL == %f", Result.m_Real);
	else if (Result.m_Kind == VALUE_BOOL)
		g_ModuleInterface->Print(CM_AQUA, "BOOL == %s", Result.m_Real == 0 ? "false" : "true");
	else if (Result.m_Kind == VALUE_STRING)
		g_ModuleInterface->Print(CM_AQUA, "STRING == %s", Result.ToString().c_str());
	else
		g_ModuleInterface->Print(CM_AQUA, "OTHER");

	g_ModuleInterface->Print(CM_WHITE, "EXIT: %s", GML_SCRIPT_DROP_ITEM);
	return Result;


static std::vector<std::string> struct_field_names = {};
bool GetStructFieldNames(
	IN const char* MemberName,
	IN OUT RValue* Value
)
{
	struct_field_names.push_back(MemberName);
	return false;
}
bool EnumFunction(
	IN const char* MemberName,
	IN OUT RValue* Value
)
{
	g_ModuleInterface->Print(CM_LIGHTYELLOW, "Member Name: %s", MemberName);
	return false;
}