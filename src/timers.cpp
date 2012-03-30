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
#include <sampgdk/a_samp.h>

#include <set>
#include <vector>

#include "timers.h"

std::vector<Timer*> Timer::timers_;

Timer::Timer(int interval, bool repeat, TimerHandler hander, void *param)
	: interval_(interval)
	, repeating_(repeat)
	, handler_(hander)
	, param_(param)
	, startTime_(GetServerTickCount())
{
}

Timer::~Timer() {
}

void Timer::Fire(int elapsedTime) {
	size_t timerid = 0;
	while (timerid < timers_.size()) {
		if (timers_[timerid] == this) {
			break;
		}
		++timerid;
	}
	handler_(timerid, param_);
	if (repeating_) {
		startTime_ = GetServerTickCount() - (elapsedTime - interval_);
	}
}

int Timer::CreateTimer(int interval, bool repeat, TimerHandler handler, void *param) {
	Timer *timer = new Timer(interval, repeat, handler, param);
	size_t timerid = 0;
	while (timerid < timers_.size()) {
		if (timers_[timerid] == 0) {
			timers_[timerid] = timer;
			break;
		}
		++timerid;
	}
	if (timerid == timers_.size()) {
		timers_.push_back(timer);
	}
	return timerid;
}

bool Timer::DestroyTimer(int timerid) {
	if (timerid < 0 || timerid >= static_cast<int>(timers_.size())) {
		return false;
	}

	Timer *timer = timers_[timerid];
	delete timer;

	if (timerid == timers_.size()) {
		timers_.pop_back();
	} else {
		timers_[timerid] = 0;
	}

	return true;
}

void Timer::ProcessTimers() {
	int time = GetServerTickCount();
	for (size_t i = 0; i < timers_.size(); ++i) {
		Timer *timer = timers_[i];
		int elapsedTime = time - timer->GetStartTime();
		if (elapsedTime >= timer->GetInterval()) {
			timer->Fire(elapsedTime);
			if (!timer->IsRepeating()) {
				DestroyTimer(i);
			}
		}
	}
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers() {
	Timer::ProcessTimers();
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreateTimer(int interval, bool repeat, TimerHandler handler, void *param) {
	return Timer::CreateTimer(interval, repeat, handler, param);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyTimer(int timerid) {
	return Timer::DestroyTimer(timerid);
}
