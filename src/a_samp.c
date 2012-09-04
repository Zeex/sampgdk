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

#include <sampgdk/a_samp.h>
#include <sampgdk/bool.h>
#include <sampgdk/export.h>

#include "support/amx-stack.h"
#include "support/callback.h"
#include "support/fakeamx.h"
#include "support/likely.h"
#include "support/native.h"
#include "support/timer.h"

#define register_callbacks register_callbacks__a_samp

#include "generated/a_samp.c"

SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback, void *param)) {
	int timerid;

	if (timer_set(&timerid, interval, repeat, (timer_callback)callback, param) >= 0) {
		return timerid + 1;
	}

	return 0;
}

SAMPGDK_NATIVE(bool, KillTimer(int timerid)) {
	return timer_kill(timerid - 1) >= 0;
}
