/* Copyright (C) 2012 Zeex
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

#include <sampgdk/amx.h>

/* Initialization and cleanup routines. Each of these must be called only
 * once.
 */
int native_init();
void native_cleanup();

/* Registers a new native function that can be further retrieved with
 * one of the native_lookup*() functions family.
 */
int native_register(const char *name, AMX_NATIVE func);

/* Looks up a native function with the specified name and returns it.
 * Can return NULL if the function was not found. 
 */
AMX_NATIVE native_lookup(const char *name);

/* Same as native_lookup() but prints a warning if the name was not found.
 */
AMX_NATIVE native_lookup_warn(const char *name);

/* Same as native_lookup() but can return a stub native that prints an error
 * whenever it gets called if the specified name was not found.
 */
AMX_NATIVE native_lookup_stub(const char *name);

/* The stub native, see details above.
 */
cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params);

/* native_lookup_warn + native_lookup_stub
 */
AMX_NATIVE native_lookup_warn_stub(const char *name);

/* Returns a pointer to the internal array of currently registered natives. 
 */
const AMX_NATIVE_INFO *native_get_natives();

/* Returns the total number of natives that have been registered with
 * native_register().
 */
int native_get_num_natives();

#endif /* !SAMPGDK_NATIVE_H */
