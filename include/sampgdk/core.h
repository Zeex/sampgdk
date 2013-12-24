/* Copyright (C) 2011-2013 Zeex
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

#include <stdarg.h>

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/sdk.h>

typedef void (SAMPGDK_CALL *sampgdk_logprintf_t)(const char *format, ...);
typedef void (SAMPGDK_CALL *sampgdk_vlogprintf_t)(const char *format, va_list args);

SAMPGDK_EXPORT sampgdk_logprintf_t sampgdk_logprintf;
SAMPGDK_EXPORT sampgdk_vlogprintf_t sampgdk_vlogprintf;

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_init(void **plugin_data);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_init_plugin(void *plugin, void **plugin_data);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_cleanup(void);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_cleanup_plugin(void *plugin);

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_register_plugin(void *plugin);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin);

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol);
SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_symbol(void *plugin, const char *name);

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers(void);
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin);

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives(void);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_get_num_natives(void);

SAMPGDK_EXPORT AMX_NATIVE SAMPGDK_CALL sampgdk_find_native(const char *name);
SAMPGDK_EXPORT cell SAMPGDK_CALL sampgdk_call_native(AMX_NATIVE native, cell *params);
SAMPGDK_EXPORT cell SAMPGDK_CALL sampgdk_invoke_native(AMX_NATIVE native, const char *format, ...);

typedef bool (SAMPGDK_CALL *sampgdk_public_hook)(AMX *amx, const char *name, cell *params);

SAMPGDK_EXPORT sampgdk_public_hook SAMPGDK_CALL sampgdk_get_public_hook(void);
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_set_public_hook(sampgdk_public_hook hook);

#ifdef __cplusplus

#include <cstdarg>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable:4355) // 'this' : used in base member initializer list
#endif

namespace sampgdk {

class Plugin {
 public:
  Plugin(void *handle): handle_(handle) {}

  void *GetHandle() { return handle_; }
  void SetHandle(void *handle) { handle_ = handle; }

  int Load(void **ppData) { return sampgdk_init_plugin(handle_, ppData); }
  int Unload() { return sampgdk_cleanup_plugin(handle_); }

  int Register() { return sampgdk_register_plugin(handle_); }
  int Unregister() { return sampgdk_unregister_plugin(handle_); }

  void *GetSymbol(const char *name) {
    return sampgdk_get_plugin_symbol(handle_, name);
  }

  void ProcessTimers() { sampgdk_process_plugin_timers(handle_); }

 private:
  void *handle_;
};

class ThisPlugin: public Plugin {
 public:
  ThisPlugin(): Plugin(sampgdk_get_plugin_handle(this)) {}
};

class ServerLog {
 public:
  static void Printf(const char *format, ...) {
    std::va_list args;
    va_start(args, format);
    VPrintf(format, args);
    va_end(args);
  }
  static void VPrintf(const char *format, std::va_list args) {
    sampgdk_vlogprintf(format, args);
  }
};

} // namespace sampgdk

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#endif /* __cplusplus */

#endif /* !SAMPGDK_CORE_H */
