/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_PARAM_H
#define SAMPGDK_INTERNAL_PARAM_H

#include <sampgdk/bool.h>
#include <sampgdk/sdk.h>

void sampgdk_param_get_cell(AMX *amx, int index, cell *param);
void sampgdk_param_get_bool(AMX *amx, int index, bool *param);
void sampgdk_param_get_float(AMX *amx, int index, float *param);
void sampgdk_param_get_string(AMX *amx, int index, char **param);

/* Returns pointer to the start of the parameter list. */
cell *sampgdk_param_get_start(AMX *amx);

#endif /* !SAMPGDK_INTERNAL_PARAM_H */
