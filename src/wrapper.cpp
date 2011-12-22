// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/wrapper.h>

#include <plugin.h>

#include "callbacks.h"
#include "jump-x86.h"

#include <cstdio>
#include <cstring>
#include <string>

extern void *pAMXFunctions;

// Gamemode's AMX
static AMX *gamemode = 0;

// Curently Exec()'ing public 
static std::string currentPublic;

// AMX hooks
static JumpX86 amx_FindPublicHook;
static JumpX86 amx_ExecHook;
static JumpX86 amx_RegisterHook;
static JumpX86 amx_CallbackHook;

static cell AMX_NATIVE_CALL fixed_funcidx(AMX *amx, cell *params) {
	char *funcname;
	amx_StrParam(amx, params[1], funcname);
	int index;
	int error = amx_FindPublic(amx, funcname, &index);
	if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE && index == AMX_EXEC_GDK)) {
		return -1;
	}
	return index;
}

static int AMXAPI amx_RegisterHookProc(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	amx_RegisterHook.Remove();

	int error = amx_Register(amx, nativelist, number);

	for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
		Wrapper::GetInstance().SetNative(nativelist[i].name, nativelist[i].func);
		// Fix for funcidx() issue
		if (strcmp(nativelist[i].name, "funcidx") == 0) {
			new JumpX86((void*)nativelist[i].func, (void*)fixed_funcidx);
		}
	}

	amx_RegisterHook.Install();
	return error;
}

static int AMXAPI amx_FindPublicHookProc(AMX *amx, const char *name, int *index) {
	amx_FindPublicHook.Remove();

	int error = amx_FindPublic(amx, name, index);

	if (amx == gamemode) {
		if (error != AMX_ERR_NONE) {
			*index = AMX_EXEC_GDK;
			error = AMX_ERR_NONE;
		}
		currentPublic = name;
	}

	amx_FindPublicHook.Install();
	return error;
}

static int AMXAPI amx_ExecHookProc(AMX *amx, cell *retval, int index) {
	amx_ExecHook.Remove();
	amx_CallbackHook.Install();
	
	bool canDoExec = true;
	if (index == AMX_EXEC_MAIN) {
		gamemode = amx;
		Wrapper::GetInstance().CallPublicHook(amx, retval, "OnGameModeInit");
	} else {
		if (amx == gamemode && index != AMX_EXEC_CONT) {
			canDoExec = Wrapper::GetInstance().CallPublicHook(amx, retval, currentPublic.c_str());
		}
	}

	int error = AMX_ERR_NONE;
	if (canDoExec && index != AMX_EXEC_GDK) {
		error = amx_Exec(amx, retval, index);
	} else {
		// Pop parameters from stack 
		amx->stk += amx->paramcount * sizeof(cell);			
	}

	// Reset parameter count 
	// <weird>
	// Sometimes it is not auto-reset by amx_Exec though it normally should. 
	// </weird>
	amx->paramcount = 0;	

	amx_CallbackHook.Remove();
	amx_ExecHook.Install();

	return error;
}

static int AMXAPI amx_CallbackHookProc(AMX *amx, cell index, cell *result, cell *params) {
	amx_CallbackHook.Remove();
	amx_ExecHook.Install();

	// Forbid SYSREQ.D
	amx->sysreq_d = 0;
	
	int error = amx_Callback(amx, index, result, params);
	
	amx_ExecHook.Remove();
	amx_CallbackHook.Install();

	return error;
}

Wrapper::Wrapper() {}

Wrapper &Wrapper::GetInstance() {
	static Wrapper wrapper;
	return wrapper;
}

void Wrapper::Initialize(void **ppPluginData) {
	pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];
	void **amxExports = static_cast<void**>(pAMXFunctions);

	amx_RegisterHook.Install(
		amxExports[PLUGIN_AMX_EXPORT_Register],   
		(void*)amx_RegisterHookProc);

	amx_FindPublicHook.Install(
		amxExports[PLUGIN_AMX_EXPORT_FindPublic], 
		(void*)amx_FindPublicHookProc);

	amx_ExecHook.Install(
		amxExports[PLUGIN_AMX_EXPORT_Exec],       
		(void*)amx_ExecHookProc);

	amx_CallbackHook.Install(
		amxExports[PLUGIN_AMX_EXPORT_Callback],
		(void*)amx_CallbackHookProc);

	SetupSampCallbackHooks();
}

void Wrapper::SetNative(const char *name, AMX_NATIVE native) {
	natives_[std::string(name)] = native;
}

AMX_NATIVE Wrapper::GetNative(const char *name) const {
	std::map<std::string, AMX_NATIVE>::const_iterator it = natives_.find(name);
	if (it != natives_.end()) {
		return it->second;
	}
	return 0;
}

void Wrapper::SetPublicHook(const char *name, PublicHook hook) {
	publicHooks_.insert(std::make_pair(std::string(name), hook));
}

bool Wrapper::CallPublicHook(AMX *amx, cell *retval, const char *name) const {
	std::map<std::string, PublicHook>::const_iterator it = publicHooks_.find(name);
	if (it != publicHooks_.end()) {
		return it->second.Call(amx, retval);
	}
	return true;
}
