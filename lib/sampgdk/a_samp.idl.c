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

#include <sampgdk/export.h>
#include <sampgdk/types.h>
#include <sampgdk/a_samp.h>

#include "internal/timer.h"

SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback,
                             void *param)) {
  return sampgdk_timer_set(interval, repeat, callback, param, NULL);
}

SAMPGDK_NATIVE(int, SetTimerEx(int interval, bool repeat, TimerCallback callback,
                             void *param, void *owner)) {
	return sampgdk_timer_set(interval, repeat, callback, param, owner);
}

SAMPGDK_NATIVE(bool, KillTimer(int timerid)) {
  return sampgdk_timer_kill(timerid, NULL) >= 0;
}

SAMPGDK_NATIVE(bool, KillTimerEx(int timerid, void *owner)) {
	return sampgdk_timer_kill(timerid, owner) >= 0;
}
