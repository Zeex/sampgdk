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

#ifndef SAMPGDK_INTERNAL_TIMER_H
#define SAMPGDK_INTERNAL_TIMER_H

#include <sampgdk/bool.h>
#include <sampgdk/export.h>

/* Timer callback function.
 * There's also a public typedef TimerCallback in <sampgdk/types.h>.
 */
typedef void (SAMPGDK_CALL *sampgdk_timer_callback)(int id, void *param);

int sampgdk_timer_set(int interval, bool repeat,
    sampgdk_timer_callback calback, void *param);
int sampgdk_timer_kill(int timerid);

/* Processes timers created by the specified plugin. */
void sampgdk_timer_process_timers(void *plugin);

#endif /* !SAMPGDK_INTERNAL_TIMER_H */
