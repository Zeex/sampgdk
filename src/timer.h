/* Copyright (C) 2012-2014 Zeex
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

#ifndef SAMPGDK_TIMER_H_
#define SAMPGDK_TIMER_H_

#include <sampgdk/bool.h>
#include <sampgdk/export.h>

typedef void (SAMPGDK_TIMER_CALL *sampgdk_timer_callback)(int id, void *param);

int sampgdk_timer_set(long interval, bool repeat,
                      sampgdk_timer_callback calback, void *param);
int sampgdk_timer_kill(int timerid);
void sampgdk_timer_process_timers(void *plugin);
long sampgdk_timer_now(void);

#endif /* !SAMPGDK_TIMER_H_ */
