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

#ifndef SAMPGDK_UTIL_H_
#define SAMPGDK_UTIL_H_

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

cell read_amx_stack_cell(AMX *amx, int index);
bool read_amx_stack_bool(AMX *amx, int index);
float read_amx_stack_float(AMX *amx, int index);
char *read_amx_stack_string(AMX *amx, int index);

void hook_native(AMX *amx, const char *name, AMX_NATIVE address);

#endif /* !SAMPGDK_UTIL_H_ */
