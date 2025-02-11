#include <YYToolkit/Shared.hpp>
using namespace Aurie;
using namespace YYTK;

static const char* const VERSION = "1.0.0";
static YYTKInterface* g_ModuleInterface = nullptr;

RValue& GmlScriptTraceCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	return Result;
}

RValue& GmlScriptInfoCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	return Result;
}

RValue& GmlScriptWarnCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	return Result;
}

RValue& GmlScriptErrorCallback(
	IN CInstance* Self,
	IN CInstance* Other,
	OUT RValue& Result,
	IN int ArgumentCount,
	IN RValue** Arguments
)
{
	return Result;
}

void CreateHookGmlScriptTrace(AurieStatus& status)
{
	CScript* gml_script_trace = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_trace",
		(PVOID*)&gml_script_trace
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to get script (gml_Script_trace)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_trace",
		gml_script_trace->m_Functions->m_ScriptFunction,
		GmlScriptTraceCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to hook script (gml_Script_trace)!", VERSION);
	}
}

void CreateHookGmlScriptInfo(AurieStatus& status)
{
	CScript* gml_script_info = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_info",
		(PVOID*)&gml_script_info
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to get script (gml_Script_info)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_info",
		gml_script_info->m_Functions->m_ScriptFunction,
		GmlScriptInfoCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to hook script (gml_Script_info)!", VERSION);
	}
}

void CreateHookGmlScriptWarn(AurieStatus& status)
{
	CScript* gml_script_warn = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_warn",
		(PVOID*)&gml_script_warn
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to get script (gml_Script_warn)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_warn",
		gml_script_warn->m_Functions->m_ScriptFunction,
		GmlScriptWarnCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to hook script (gml_Script_warn)!", VERSION);
	}
}

void CreateHookGmlScriptError(AurieStatus& status)
{
	CScript* gml_script_error = nullptr;
	status = g_ModuleInterface->GetNamedRoutinePointer(
		"gml_Script_error",
		(PVOID*)&gml_script_error
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to get script (gml_Script_error)!", VERSION);
	}

	status = MmCreateHook(
		g_ArSelfModule,
		"gml_Script_error",
		gml_script_error->m_Functions->m_ScriptFunction,
		GmlScriptErrorCallback,
		nullptr
	);

	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Failed to hook script (gml_Script_error)!", VERSION);
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

	g_ModuleInterface->Print(CM_LIGHTAQUA, "[CleanLog %s] - Plugin starting...", VERSION);

	CreateHookEventObject(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptSetupMainScreen(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}
	
	CreateHookGmlScriptAddHeartPointsAnimal(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptOnNewDay(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptTrace(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptInfo(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptWarn(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	CreateHookGmlScriptError(status);
	if (!AurieSuccess(status))
	{
		g_ModuleInterface->Print(CM_LIGHTRED, "[CleanLog %s] - Exiting due to failure on start!", VERSION);
		return status;
	}

	g_ModuleInterface->Print(CM_LIGHTGREEN, "[CleanLog %s] - Plugin started!", VERSION);
	return AURIE_SUCCESS;
}