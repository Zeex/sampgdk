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

#ifndef SAMPGDK_TIMERS_H
#define SAMPGDK_TIMERS_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>

#include <set>
#include <vector>

namespace sampgdk {

class Timer {
public:
	static int CreateTimer(int interval, bool repeat, TimerHandler handler, void *param);
	static bool DestroyTimer(int timerid);

	~Timer();

	int GetInterval() const
		{ return interval_; }
	bool IsRepeating() const
		{ return repeating_; }
	int GetStartTime() const
		{ return startTime_; }

	void Fire(int elapsedTime);

	static int Clock();
	static void ProcessTimers();

private:
	Timer(int interval, bool repeat, TimerHandler hander, void *param);

	int interval_;
	bool repeating_;
	TimerHandler handler_;
	void *param_;

	int startTime_;

	static std::vector<Timer*> timers_;
};

} // namespace sampgdk

#endif // SAMPGDK_TIMERS_H
