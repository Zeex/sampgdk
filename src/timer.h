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

#ifndef SAMPGDK_TIMER_H_
#define SAMPGDK_TIMER_H_

#include <sampgdk/bool.h>
#include <sampgdk/export.h>

#include <time.h>

typedef void (SAMPGDK_CALL *timer_callback)(int timerid, void *param);

struct timer_info {
	time_t          interval;
	bool            repeat;
	timer_callback  callback;
	void           *param;
	time_t          started;
	void           *plugin;
};

/* Initializes internal global data. Returns 0 on success or a negative
 * value otherwise.
 */
int timer_init();

/* Frees internal data.
 */
void timer_cleanup();

/* Sets a new timer that is fired after interval milliseconds. If repeat is
 * true the timer is called repeatedly until it gets killed by timer_kill().
 * The callback parameter specifies the function to be called once the timer
 * expires. The function is passed the ID of the newly created timer and a
 * pointer to user data (the param argument).
 */
int timer_set(time_t interval, bool repeat, timer_callback calback,
              void *param /* = NULL */);

/* Kills the specified timer. Returns 0 on success and a negative value if
 * the timer is already killed or the timer ID is not within the valid range
 * of timer IDs.
 */
int timer_kill(int timerid);

/* Fires all timers that have expired since their creation or since the last
 * call to this function. If the plugin argument is not NULL only those timers
 * that belong to the specified plugin are processed by the function. */
void timer_process_timers(void *plugin);

/* Returns the number of milliseconds since some fixed point of time. */
time_t timer_clock();

#endif /* !SAMPGDK_TIMER_H_ */
