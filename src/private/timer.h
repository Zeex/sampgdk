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

#ifndef SAMPGDK_PRIVATE_TIMER_H_
#define SAMPGDK_PRIVATE_TIMER_H_

#include <sampgdk/bool.h>
#include <sampgdk/export.h>

#include <time.h>

typedef void (SAMPGDK_CALL *sampgdk_timer_callback)(int timerid, void *param);

struct sampgdk_timer {
  bool                    is_set;
  long                    interval;
  bool                    repeat;
  sampgdk_timer_callback  callback;
  void                   *param;
  long                    started;
  void                   *plugin;
};

/* Sets a new timer that is fired after interval milliseconds. If repeat is
 * true the timer is called repeatedly until it gets killed by
 * sampgdk_timer_kill(). The callback parameter specifies the function to be
 * called once the timer expires. The function is passed the ID of the newly
 * created timer and a pointer to user data (the param argument).
 */
int sampgdk_timer_set(
  long                    interval,
  bool                    repeat,
  sampgdk_timer_callback  calback,
  void                   *param /* = NULL */);

/* Kills the specified timer. Returns 0 on success and a negative value if
 * the timer is already killed or the timer ID is not within the valid range
 * of timer IDs.
 */
int sampgdk_timer_kill(int timerid);

/* Fires all timers that have expired since their creation or since the last
 * call to this function. If the plugin argument is not NULL only those timers
 * that belong to the specified plugin are processed by the function. */
void sampgdk_timer_process_timers(void *plugin);

/* Returns the number of milliseconds since some fixed point of time. */
long sampgdk_timer_clock(void);

#endif /* !SAMPGDK_PRIVATE_TIMER_H_ */
