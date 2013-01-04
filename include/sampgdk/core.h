/* Copyright (C) 2011-2012 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_CORE_H
#define SAMPGDK_CORE_H

#include <assert.h>
#include <stdarg.h>

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>
#include <sampgdk/export.h>

/* These should be called only once, e.g. in Load() and Unload() respectively. */
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppData);
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize();

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_register_plugin(void *plugin);
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin);

SAMPGDK_EXPORT void **SAMPGDK_CALL sampgdk_get_plugin_data();
SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol);
SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_symbol(void *plugin, const char *name);

#define sampgdk_initialize_plugin sampgdk_initialize

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers();
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin);

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives();
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_num_natives();

typedef void (*sampgdk_logprintf_t)(const char *format, ...);
SAMPGDK_EXPORT sampgdk_logprintf_t sampgdk_logprintf;

typedef void (*sampgdk_vlogprintf_t)(const char *format, va_list args);
SAMPGDK_EXPORT sampgdk_vlogprintf_t sampgdk_vlogprintf;

#ifdef __cplusplus

class ThisPlugin {
public:
	ThisPlugin() : handle_(::sampgdk_get_plugin_handle(this)) {}

	void *GetHandle() { return handle_; }

	void Load(void **ppData) { ::sampgdk_initialize(ppData); }
	void Unload() { ::sampgdk_finalize(); }

	void Register() { ::sampgdk_register_plugin(handle_); }
	void Unregister() { ::sampgdk_unregister_plugin(handle_); }

	void *GetSymbol(const char *name) {
		return ::sampgdk_get_plugin_symbol(handle_, name);
	}

	void ProcessTimers() { ::sampgdk_process_plugin_timers(handle_); }

private:
	void *handle_;
};

class Log {
public:
	static void Printf(const char *format, ...) {
		va_list args;
		va_start(args, format);
		VPrintf(format, args);
		va_end(args);
	}

	static void VPrintf(const char *format, va_list args) {
		assert(::sampgdk_vlogprintf != 0 && "sampgdk has not been initialized");
		::sampgdk_vlogprintf(format, args);
	}
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_CORE_H */
