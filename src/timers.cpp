// Copyright (C) 2011-2012, Zeex
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

#include <set>
#include <vector>

#include "timers.h"

namespace sampgdk {

Timer::Timer(int interval, bool repeat, TimerHandler hander, void *param)
	: interval_(interval)
	, repeating_(repeat)
	, handler_(hander)
	, param_(param)
	, startTime_(GetTickCount())
{
}

Timer::~Timer() {
}

void Timer::Fire(int elapsedTime) {
	handler_(Timers::GetInstance().GetTimerId(this), param_);
	if (repeating_) {
		startTime_ = GetTickCount() - (elapsedTime - interval_);
	}
}

// static
Timers &Timers::GetInstance() {
	static Timers timers;
	return timers;
}

int Timers::GetTimerId(Timer *timer) const {
	int timerid = 0;
	while (timerid < static_cast<int>(timers_.size())) {
		if (timers_[timerid] == timer) {
			break;
		}
		++timerid;
	}
	return timerid;
}

int Timers::SetTimer(int interval, bool repeat, TimerHandler handler, void *param) {
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

bool Timers::KillTimer(int timerid) {
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

void Timers::ProcessTimers() {
	int time = GetTickCount();
	for (size_t i = 0; i < timers_.size(); ++i) {
		Timer *timer = timers_[i];
		int elapsedTime = time - timer->GetStartTime();
		if (elapsedTime >= timer->GetInterval()) {
			timer->Fire(elapsedTime);
			if (!timer->IsRepeating()) {
				KillTimer(i);
			}
		}
	}
}

} // namespace sampgdk
