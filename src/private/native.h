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

#ifndef SAMPGDK_PRIVATE_NATIVE_H_
#define SAMPGDK_PRIVATE_NATIVE_H_

#include <sampgdk/amx.h>

/* Registers a new native function that can be further retrieved with
 * one of the sampgdk_native_lookup*() functions family.
 */
int sampgdk_native_register(const char *name, AMX_NATIVE func);

/* Looks up a native function with the specified name and returns it.
 * Can return NULL if the function was not found. 
 */
AMX_NATIVE sampgdk_native_lookup(const char *name);

/* Same as sampgdk_native_lookup() but prints a warning if the
*  name was not found.
 */
AMX_NATIVE sampgdk_native_lookup_warn(const char *name);

/* Same as sampgdk_native_lookup() but can return a stub native
 * that prints an error whenever it gets called if the specified
 * name was not found.
 */
AMX_NATIVE sampgdk_native_lookup_stub(const char *name);

/* The stub native, see details above.
 */
cell AMX_NATIVE_CALL sampgdk_native_stub(AMX *amx, cell *params);

/* sampgdk_native_lookup_warn + sampgdk_native_lookup_stub
 */
AMX_NATIVE sampgdk_native_lookup_warn_stub(const char *name);

/* Returns a pointer to the internal array of currently
 * registered natives.
 */
const AMX_NATIVE_INFO *sampgdk_native_get_natives(void);

/* Returns the total number of natives that have been registered
 * with sampgdk_native_register().
 */
int sampgdk_native_get_num_natives(void);

#endif /* !SAMPGDK_PRIVATE_NATIVE_H_ */
