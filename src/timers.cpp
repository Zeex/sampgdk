// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#include <algorithm>
#include <functional>
#include <set>

#ifdef SAMPGDK_WINDOWS
	#include <Windows.h>
#else
	#include <time.h>
#endif

#include "timers.h"

std::set<Timer*> Timer::timers_;

Timer::Timer(int interval, bool repeat, TimerHandler hander, void *param) 
	: interval_(interval)
	, repeating_(repeat)
	, handler_(hander)
	, param_(param)
	, startTime_(GetTime())
{
}

Timer::~Timer() {
}

void Timer::Fire(int elapsedTime) {
	handler_(reinterpret_cast<int>(this), param_);
	if (repeating_) {
		startTime_ = GetTime() - (elapsedTime - interval_);
	}
}

#ifdef SAMPGDK_WINDOWS
	int Timer::GetTime() {
		return GetTickCount();
	}
#else 
	int Timer::GetTime() {
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		return static_cast<int>(ts.tv_nsec / 1000L);
	}
#endif

Timer *Timer::CreateTimer(int interval, bool repeat, TimerHandler handler, void *param) {
	Timer *timer = new Timer(interval, repeat, handler, param);
	timers_.insert(timer);
	return timer;
}

void Timer::DestroyTimer(Timer *timer) {
	timers_.erase(timer);
	delete timer;
}

void Timer::ProcessTimers() {
	int time = Timer::GetTime();
	for (std::set<Timer*>::iterator iterator = timers_.begin();
			iterator != timers_.end(); ++iterator) {
		Timer *timer = *iterator;
		int elapsedTime = time - timer->GetStartTime();
		if (elapsedTime >= timer->GetInterval()) {
			(*iterator)->Fire(elapsedTime);
			if (!timer->IsRepeating()) {
				timers_.erase(iterator);
			}
		}
	}
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers() {
	Timer::ProcessTimers();
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreateTimer(int interval, bool repeat, TimerHandler hander, void *param) {
	return reinterpret_cast<int>(Timer::CreateTimer(interval, repeat, hander, param));
}

SAMPGDK_EXPORT void SAMPGDK_CALL DestroyTimer(int timerid) {
	Timer::DestroyTimer(reinterpret_cast<Timer*>(timerid));
}
