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

#include <sampgdk/config.h>
#include <sampgdk/core.h>

#include "timer.h"

#define MAX_TIMERS 128

struct timer_info {
	time_t          interval;
	bool            repeat;
	timer_callback  callback;
	void           *param;
	time_t          started;
	void           *plugin;
};

struct timer_slot {
	struct timer_info timer;
	bool              busy;
};

/* TODO: make this dynamic */
static struct timer_slot timers[MAX_TIMERS];

static int find_free_slot() {
	int i;

	for (i = 0; i < MAX_TIMERS; i++) {
		if (!timers[i].busy) {
			return i;
		}
	}

	return -1;
}

static int find_timer_id(struct timer_info *timer) {
	int i;

	for (i = 0; i < MAX_TIMERS; i++) {
		if (&timers[i].timer == timer) {
			return i;
		}
	}

	return -1;
}

static void fire_timer(int timerid, time_t elapsed) {
	struct timer_info *timer;

	timer = &timers[timerid].timer;
	(timer->callback)(timerid, timer->param);

	if (timer->repeat) {
		timer->started = timer_clock() - (elapsed - timer->interval);
	}
}

int timer_set(time_t interval, bool repeat, timer_callback callback, void *param) {
	int timerid;
	struct timer_info *timer;

	timerid = find_free_slot();
	if (timerid >= 0) {
		timer = &timers[timerid].timer;
		timer->interval = interval;
		timer->repeat   = repeat;
		timer->callback = callback;
		timer->param    = param;
		timer->started  = timer_clock();
		timer->plugin   = sampgdk_get_plugin_handle(callback);
		timers[timerid].busy = true;
	}

	return timerid;
}

bool timer_kill(int timerid) {
	if (timerid < 0 || timerid >= MAX_TIMERS) {
		return false;
	}

	if (timers[timerid].busy) {
		timers[timerid].busy = false;
		return true;
	}

	return false;
}

void timer_process_timers(void *plugin) {
	time_t now;
	time_t elapsed;
	int i;
	struct timer_info *timer;

	now = timer_clock();

	for (i = 0; i < MAX_TIMERS; i++) {
		if (!timers[i].busy) 
			continue;

		timer = &timers[i].timer;

		if (plugin != NULL && timer->plugin != plugin)
			continue;

		elapsed = now - timer->started;
		if (elapsed >= timer->interval) {
			fire_timer(i, elapsed);
			if (!timer->repeat) {
				timer_kill(i);
			}
		}
	}
}
