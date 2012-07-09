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

#include <set>
#include <vector>

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#include "timers.h"

namespace sampgdk {

Timer::Timer(int interval, bool repeat, TimerCallback callback, void *param)
	: interval_(interval)
	, repeating_(repeat)
	, callback_(callback)
	, param_(param)
	, plugin_(sampgdk_get_plugin_handle((void*)callback))
	, start_time_(GetTickCount())
{
}

Timer::~Timer() {
}

void Timer::Fire(int elapsed_time) {
	callback_(TimerManager::GetInstance().GetTimerId(this), param_);
	if (repeating_) {
		start_time_ = GetTickCount() - (elapsed_time - interval_);
	}
}

// static
TimerManager &TimerManager::GetInstance() {
	static TimerManager timers;
	return timers;
}

int TimerManager::GetTimerId(Timer *timer) const {
	int timerid = 0;
	while (timerid < static_cast<int>(timers_.size())) {
		if (timers_[timerid] == timer) {
			break;
		}
		++timerid;
	}
	return timerid;
}

int TimerManager::SetTimer(int interval, bool repeat, TimerCallback handler, void *param) {
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

bool TimerManager::KillTimer(int timerid) {
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

void TimerManager::ProcessTimers(void *plugin) {
	int time = GetTickCount();
	for (size_t i = 0; i < timers_.size(); ++i) {
		Timer *timer = timers_[i];
		if (plugin != 0 && timer->GetPlugin() != plugin) {
			continue;
		}
		int elapsed_time = time - timer->GetStartTime();
		if (elapsed_time >= timer->GetInterval()) {
			timer->Fire(elapsed_time);
			if (!timer->IsRepeating()) {
				KillTimer(i);
			}
		}
	}
}

} // namespace sampgdk
