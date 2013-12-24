/* Copyright (C) 2012-2013 Zeex
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

#ifndef SAMPGDK_NATIVE_H_
#define SAMPGDK_NATIVE_H_

#include <stdarg.h>

#include <sampgdk/sdk.h>

int sampgdk_native_register(const char *name, AMX_NATIVE func);
AMX_NATIVE sampgdk_native_find(const char *name);
AMX_NATIVE sampgdk_native_find_warn(const char *name);
AMX_NATIVE sampgdk_native_find_stub(const char *name);
AMX_NATIVE sampgdk_native_find_warn_stub(const char *name);
const AMX_NATIVE_INFO *sampgdk_native_get_natives(void);
int sampgdk_native_get_num_natives(void);
cell sampgdk_native_call(AMX_NATIVE native, cell *params);
cell sampgdk_native_invoke(AMX_NATIVE native, const char *format, va_list args);

#endif /* !SAMPGDK_NATIVE_H_ */
