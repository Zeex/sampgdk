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

#include <stdlib.h>
#include <time.h>

#include "array.h"
#include "timer.h"

struct timer_info {
	time_t          interval;
	bool            repeat;
	timer_callback  callback;
	void           *param;
	time_t          started;
	void           *plugin;
};

static struct array timers;

static struct timer_info *get_timer_ptr(int timerid) {
	return ((void**)timers.data)[timerid];
}

static int find_free_slot() {
	int i;

	for (i = 0; i < timers.count; i++) {
		if (get_timer_ptr(i) == NULL) {
			return i;
		}
	}

	return -1;
}

static int find_timer_id(struct timer_info *timer) {
	int i;

	for (i = 0; i < timers.count; i++) {
		if (get_timer_ptr(i) == timer) {
			return i;
		}
	}

	return -1;
}

static void fire_timer(int timerid, time_t elapsed) {
	struct timer_info *timer;

	timer = get_timer_ptr(timerid);
	if (timer == NULL)
		return;

	(timer->callback)(timerid, timer->param);

	if (timer->repeat) {
		timer->started = timer_clock() - (elapsed - timer->interval);
	}
}

bool timer_init() {
	if (!array_new(&timers, 10, sizeof(void *)))
		return false;

	array_zero(&timers);
	return true;
}

void timer_cleanup() {
	array_free(&timers);
}

int timer_set(time_t interval, bool repeat, timer_callback callback, void *param) {
	int timerid;
	struct timer_info *timer;

	timer = malloc(sizeof(*timer));
	if (timer == NULL)
		return -1;

	timer->interval = interval;
	timer->repeat   = repeat;
	timer->callback = callback;
	timer->param    = param;
	timer->started  = timer_clock();
	timer->plugin   = sampgdk_get_plugin_handle(callback);

	timerid = find_free_slot();
	if (timerid >= 0) {
		array_set(&timers, timerid, &timer);
	} else {
		array_append(&timers, &timer);
		timerid = timers.count - 1;
	}

	return timerid;
}

bool timer_kill(int timerid) {
	struct timer_info *timer;

	if (timerid < 0 || timerid >= timers.count) {
		return false;
	}

	if ((timer = get_timer_ptr(timerid)) !=  NULL) {
		free(timer);
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

	for (i = 0; i < timers.count; i++) {
		timer = get_timer_ptr(i);

		if (timer == NULL) 
			continue;

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
