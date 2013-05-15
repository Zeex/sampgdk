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

#ifndef SAMPGDK_PRIVATE_CALLBACK_H_
#define SAMPGDK_PRIVATE_CALLBACK_H_

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>

typedef bool (*sampgdk_callback_handler)(
  AMX  *amx,
  void *callback,
  cell *retval);

struct sampgdk_callback {
  char                     *name;
  sampgdk_callback_handler  handler;
};

/* 
 * Finds a calback by name. Returns NULL if there is no callback with
 * such a name.
 */
struct sampgdk_callback *sampgdk_callback_lookup(const char *name);

/*
 * Adds a new callback handler. Returns 0 on success and a negative
 * value on error.
 */
int sampgdk_callback_register(const char *name,
                              sampgdk_callback_handler handler);

/* Same as sampgdk_callback_register() but can register *multiple*
 * callbacks  at once.
 */
int sampgdk_callback_register_table(const struct sampgdk_callback *table);

/* Unregisters a callback previously registered with
 * sampgdk_callback_register().
 */
void sampgdk_callback_unregister(const char *name);

/* Same as sampgdk_callback_unregister() but can unregister *multiple*
 * callbacks at once.
 */
void sampgdk_callback_unregister_table(const struct sampgdk_callback *table);

/*
 * Invokes a callback by name and stores return value in retval
 * if retval is not NULL. Returns false if there is no callback
 * with such a name.
 */
bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval);

#endif /* !SAMPGDK_PRIVATE_CALLBACK_H_ */
