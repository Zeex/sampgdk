/* Copyright (C) 2012-2019 Zeex
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

#ifndef SAMPGDK_INTERNAL_NATIVE_H
#define SAMPGDK_INTERNAL_NATIVE_H

#include <stdarg.h>

#include <sampgdk/sdk.h>

/* Register a native function in the internal natives table. */
int sampgdk_native_register(const char *name, AMX_NATIVE func);

AMX_NATIVE sampgdk_native_find(const char *name);
AMX_NATIVE sampgdk_native_find_warn(const char *name);
AMX_NATIVE sampgdk_native_find_stub(const char *name);
AMX_NATIVE sampgdk_native_find_warn_stub(const char *name);
AMX_NATIVE sampgdk_native_find_flexible(const char *name, AMX_NATIVE current);

/* Returns all currently registered natives. */
const AMX_NATIVE_INFO *sampgdk_native_get_natives(int *number);

cell sampgdk_native_call(AMX_NATIVE native, cell *params);
cell sampgdk_native_invoke(AMX_NATIVE native, const char *format, va_list args);
cell sampgdk_native_invoke_array(
    AMX_NATIVE native, const char *format, void **args);

#endif /* !SAMPGDK_INTERNAL_NATIVE_H */
