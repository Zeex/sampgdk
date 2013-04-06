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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"
#include "init.h"
#include "plugin.h"
#include "timer.h"

static struct array timers;

static struct timer_info *get_timer_ptr(int timerid) {
	assert(timerid > 0 && timerid <= timers.count);
	return ((void**)timers.data)[timerid - 1];
}

static void set_timer_ptr(int timerid, struct timer_info *ptr) {
	assert(timerid > 0 && timerid <= timers.count);
	((void**)timers.data)[timerid - 1] = ptr;
}

static int find_free_slot() {
	int i;

	for (i = 0; i < timers.count; i++) {
		if (get_timer_ptr(i) == NULL)
			return i;
	}

	return -1;
}

static void fire_timer(int timerid, time_t elapsed) {
	struct timer_info *timer;

	assert(timerid > 0 && timerid <= timers.count);

	timer = get_timer_ptr(timerid);
	if (timer == NULL)
		return;

	(timer->callback)(timerid, timer->param);

	/* At this point the could be killed by the timer callback,
	 * so the timer pointer may be no longer valid.
	 */
	timer = get_timer_ptr(timerid);
	if (timer != NULL)
		if (timer->repeat)
			timer->started = timer_clock() - (elapsed - timer->interval);
		else
			timer_kill(timerid);
}

DEFINE_INIT_FUNC(timer_init) {
	int error;
	
	error = array_new(&timers, 10, sizeof(void *));
	if (error < 0)
		return error;
	
	array_zero(&timers);

	return 0;
}

DEFINE_CLEANUP_FUNC(timer_cleanup) {
	array_free(&timers);
}

int timer_set(time_t interval, bool repeat, timer_callback callback, void *param) {
	struct timer_info *timer;
	int slot;

	assert(callback != NULL);

	timer = malloc(sizeof(*timer));
	if (timer == NULL)
		return -errno;

	timer->interval = interval;
	timer->repeat   = repeat;
	timer->callback = callback;
	timer->param    = param;
	timer->started  = timer_clock();
	timer->plugin   = plugin_address_to_handle(callback);

	slot = find_free_slot();
	if (slot >= 0) {
		array_set(&timers, slot, &timer);
	} else {
		if (array_append(&timers, &timer) < 0) {
			free(timer);
			return -errno;
		}
		slot = timers.count - 1;
	}

	/* Timer IDs returned by the SA:MP's SetTimer() API begin
	 * with 1, and so do they here.
	 */
	return slot + 1;
}

int timer_kill(int timerid) {
	struct timer_info *timer;

	if (timerid <= 0 || timerid > timers.count)
		return -EINVAL;

	timer = get_timer_ptr(timerid);
	if (timer ==  NULL)
		return -EINVAL;

	free(timer);
	set_timer_ptr(timerid, NULL);

	return 0;
}

void timer_process_timers(void *plugin) {
	time_t now;
	time_t elapsed;
	int i;
	struct timer_info *timer;

	assert(plugin != NULL);

	now = timer_clock();

	for (i = 1; i <= timers.count; i++) {
		timer = get_timer_ptr(i);

		if (timer == NULL) 
			continue;

		if (plugin != NULL && timer->plugin != plugin)
			continue;

		elapsed = now - timer->started;

		if (elapsed >= timer->interval)
			fire_timer(i, elapsed);
	}
}
