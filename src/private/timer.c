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

static int find_slot() {
  int i;

  for (i = 0; i < timers.count; i++) {
    struct timer_info *timer;

    timer = array_get(&timers, i);
    if (!timer->is_set) {
      return i;
    }
  }

  return -1;
}

static void fire_timer(int timerid, long elapsed) {
  struct timer_info *timer;

  assert(timerid > 0 && timerid <= timers.count);

  timer = array_get(&timers, timerid - 1);
  if (!timer->is_set) {
    return;
  }

  (timer->callback)(timerid, timer->param);

  /* At this point the could be killed by the timer callback,
   * so the timer pointer may be no longer valid.
   */
  if (timer->is_set) {
    if (timer->repeat) {
      timer->started = timer_clock() - (elapsed - timer->interval);
    } else {
      timer_kill(timerid);
    }
  }
}

DEFINE_INIT_FUNC(timer_init) {
  int error;
  
  error = array_new(&timers, 10, sizeof(struct timer_info));
  if (error < 0) {
    return error;
  }
  
  array_zero(&timers);

  return 0;
}

DEFINE_CLEANUP_FUNC(timer_cleanup) {
  array_free(&timers);
}

int timer_set(long interval, bool repeat, timer_callback callback, void *param) {
  struct timer_info timer;
  int slot;
  int error;

  assert(callback != NULL);

  timer.is_set   = true;
  timer.interval = interval;
  timer.repeat   = repeat;
  timer.callback = callback;
  timer.param    = param;
  timer.started  = timer_clock();
  timer.plugin   = plugin_address_to_handle(callback);

  slot = find_slot();
  if (slot >= 0) {
    array_set(&timers, slot, &timer);
  } else {
    error = array_append(&timers, &timer);
    if (error < 0) {
      return -error;
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

  if (timerid <= 0 || timerid > timers.count) {
    return -EINVAL;
  }

  timer = array_get(&timers, timerid - 1);
  if (!timer->is_set) {
    return -EINVAL;
  }

  timer->is_set = false;
  return 0;
}

void timer_process_timers(void *plugin) {
  long now;
  long elapsed;
  int i;
  struct timer_info *timer;

  assert(plugin != NULL);

  now = timer_clock();

  for (i = 0; i < timers.count; i++) {
    timer = array_get(&timers, i);

    if (!timer->is_set) {
      continue;
    }

    if (plugin != NULL && timer->plugin != plugin) {
      continue;
    }

    elapsed = now - timer->started;

    if (elapsed >= timer->interval) {
      fire_timer(i + 1, elapsed);
    }
  }
}
