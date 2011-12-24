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
#include <sampgdk/timers.h>

#include <set>

#ifdef SAMPGDK_WINDOWS
	#include <Windows.h>
#else
	#include <time.h>
#endif

namespace sampgdk {

std::set<Timer*> Timers::timers_;

Timer::Timer(int interval, bool repeat, TimerHandler hander, void *param) 
	: interval_(interval)
	, repeating_(repeat)
	, handler_(hander)
	, param_(param)
	, startTime_(GetTime())
	, isAlive_(true)
{
	Timers::CreateTimer(this);
}

Timer::~Timer() {
	Timers::DestroyTimer(this);
}

void Timer::Fire(int elapsedTime) {
	handler_(reinterpret_cast<long>(this), param_);
	if (repeating_) {
		startTime_ = GetTime() - (elapsedTime - interval_);
	} else {
		isAlive_ = false;
	}
}

#ifdef SAMPGDK_WINDOWS
	long Timer::GetTime() {
		return ::GetTickCount();
	}
#else 
	long Timer::GetTime() {
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		return ts.tv_nsec / 1000L;
	}
#endif

void Timers::CreateTimer(Timer *timer) {
	timers_.insert(timer);
}

void Timers::DestroyTimer(Timer *timer) {
	timers_.erase(timer);
}

void Timers::ProcessTimers() {
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

long SetTimer(long interval, bool repeat, TimerHandler hander, void *param) {
	return reinterpret_cast<long>(new Timer(interval, repeat, hander, param));
}

void KillTimer(long timerid) {
	delete reinterpret_cast<Timer*>(timerid);
}

} // namespace sampgdk
