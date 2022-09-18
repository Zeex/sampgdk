/* Copyright (C) 2012-2016 Zeex
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
#include <string.h>
#include <time.h>

#include <sampgdk/platform.h>

#if SAMPGDK_WINDOWS
  #include <windows.h>
#endif

#include "array.h"
#include "init.h"
#include "log.h"
#include "plugin.h"
#include "timer.h"
#include "types.h"

struct _sampgdk_timer_info {
  bool    is_set;
  void   *plugin;
  int64_t started;
  int     interval;
  void   *callback;
  void   *param;
  bool    repeat;
};

static struct sampgdk_array _sampgdk_timers;

#if SAMPGDK_WINDOWS

static int64_t _sampgdk_timer_now(void) {
  LARGE_INTEGER freq;
  LARGE_INTEGER counter;

  if (QueryPerformanceFrequency(&freq) == 0) {
    sampgdk_log_error("QueryPerformanceFrequency: error %d", GetLastError());
    return 0;
  }
  if (QueryPerformanceCounter(&counter) == 0) {
    sampgdk_log_error("QueryPerformanceCounter: error %d", GetLastError());
    return 0;
  }

  return (int64_t)(1000.0L / freq.QuadPart * counter.QuadPart);
}

#else /* SAMPGDK_WINDOWS */

static int64_t _sampgdk_timer_now(void) {
  struct timespec ts;
  int64_t msec;
  int64_t msec_fract;

  if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0) {
    sampgdk_log_error("clock_gettime: %s", strerror(errno));
    return 0;
  }

  msec = (int64_t)ts.tv_sec * 1000;
  msec_fract = (int64_t)ts.tv_nsec / 1000000L;

  return msec + msec_fract;
}

#endif /* !SAMPGDK_WINDOWS */

static int _sampgdk_timer_find_slot(void) {
  int i;

  for (i = 0; i < _sampgdk_timers.count; i++) {
    struct _sampgdk_timer_info *timer;

    timer = (struct _sampgdk_timer_info *)sampgdk_array_get(&_sampgdk_timers, i);
    if (!timer->is_set) {
      return i;
    }
  }

  return -1;
}

static void _sampgdk_timer_fire(int timerid, int64_t elapsed) {
  struct _sampgdk_timer_info *timer;
  int64_t now = _sampgdk_timer_now();
  int64_t started;

  assert(timerid > 0 && timerid <= _sampgdk_timers.count);
  timer = (struct _sampgdk_timer_info *)sampgdk_array_get(&_sampgdk_timers, timerid - 1);

  assert(timer->is_set);
  started = timer->started;

  sampgdk_log_debug("Firing timer %d, now = %" PRId64 ", elapsed = %" PRId64,
      timerid, now, elapsed);
  ((sampgdk_timer_callback)timer->callback)(timerid, timer->param);

  /* We don't want to kill the same timer twice, so make sure it's not
   * been killed inside the timer callback.
   */
  if (timer->is_set && timer->started == started) {
    if (timer->repeat) {
      timer->started = now - (elapsed - timer->interval);
    } else {
      sampgdk_timer_kill(timerid);
    }
  }
}

SAMPGDK_MODULE_INIT(timer) {
  int error;

  error = sampgdk_array_new(&_sampgdk_timers,
                            8,
                            sizeof(struct _sampgdk_timer_info));
  if (error < 0) {
    return error;
  }

  sampgdk_array_zero(&_sampgdk_timers);

  return 0;
}

SAMPGDK_MODULE_CLEANUP(timer) {
  sampgdk_array_free(&_sampgdk_timers);
}

int sampgdk_timer_set(int interval,
                      bool repeat,
                      sampgdk_timer_callback callback,
                      void *param) {
  struct _sampgdk_timer_info timer;
  int slot;
  int error;
  int timerid;

  assert(callback != NULL);

  timer.is_set   = true;
  timer.interval = interval;
  timer.repeat   = repeat;
  timer.callback = (void *)callback;
  timer.param    = param;
  timer.started  = _sampgdk_timer_now();
  timer.plugin   = sampgdk_plugin_get_handle((void *)callback);

  if (timer.started == 0) {
    return 0; /* error already logged */
  }

  slot = _sampgdk_timer_find_slot();
  if (slot >= 0) {
    sampgdk_array_set(&_sampgdk_timers, slot, &timer);
  } else {
    error = sampgdk_array_append(&_sampgdk_timers, &timer);
    if (error < 0) {
      sampgdk_log_error("Error setting timer: %s", strerror(-error));
      return 0;
    }
    slot = _sampgdk_timers.count - 1;
  }

  /* Timer IDs returned by the SA:MP's SetTimer() API begin
   * with 1, and so do they here.
   */
  timerid = slot + 1;

  sampgdk_log_debug("Created timer: ID = %d, interval = %d, repeat = %s",
      timerid, interval, repeat ? "true" : "false");

  return timerid;
}

int sampgdk_timer_kill(int timerid) {
  struct _sampgdk_timer_info *timer;

  if (timerid <= 0 || timerid > _sampgdk_timers.count) {
    return -EINVAL;
  }

  timer = (struct _sampgdk_timer_info *)sampgdk_array_get(&_sampgdk_timers, timerid - 1);
  if (!timer->is_set) {
    return -EINVAL;
  }

  timer->is_set = false;

  sampgdk_log_debug("Killed timer %d", timerid);

  return 0;
}

void sampgdk_timer_process_timers(void *plugin) {
  int64_t now;
  int64_t elapsed;
  int i;
  struct _sampgdk_timer_info *timer;

  assert(plugin != NULL);

  now = _sampgdk_timer_now();

  for (i = 0; i < _sampgdk_timers.count; i++) {
    timer = (struct _sampgdk_timer_info *)sampgdk_array_get(&_sampgdk_timers, i);

    if (!timer->is_set
        || (plugin != NULL && timer->plugin != plugin)) {
      continue;
    }

    elapsed = now - timer->started;

    if (elapsed >= timer->interval) {
      _sampgdk_timer_fire(i + 1, elapsed);
    }
  }
}
