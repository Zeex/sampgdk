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

#ifndef SAMPGDK_TIMER_H_
#define SAMPGDK_TIMER_H_

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#include <time.h>

typedef void (SAMPGDK_CALL *timer_callback)(int timerid, void *param);

bool timer_init();
void timer_cleanup();

int timer_set(time_t interval, bool repeat, timer_callback calback, void *param);
bool timer_kill(int timerid);

void timer_process_timers(void *plugin);

/* Returns number of milliseconds since some fixed point of time. */
time_t timer_clock();

#endif /* !SAMPGDK_TIMER_H_ */
