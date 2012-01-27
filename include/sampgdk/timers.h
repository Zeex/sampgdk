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

#ifndef SAMPGDK_TIMERS_H
#define SAMPGDK_TIMERS_H

#include <sampgdk/config.h>
#include <sampgdk/samp.h>

#include <set>

namespace sampgdk {

class Timer;
typedef void (*TimerHandler)(Timer *timer, void *param);

class Timer {
public:
	static Timer *CreateTimer(long interval, bool repeat,
		                    TimerHandler handler, void *param = 0);
	static void DestroyTimer(Timer *timer);

	~Timer();

	long GetInterval() const
		{ return interval_; }
	bool IsRepeating() const
		{ return repeating_; }
	long GetStartTime() const
		{ return startTime_; }

	void Fire(long elapsedTime);

	static void ProcessTimers();
	static void DestroyAllTimers();

private:
	Timer(long interval, bool repeat, TimerHandler hander, void *param);

	long interval_;
	bool repeating_;
	TimerHandler handler_;
	void *param_;
	long startTime_;

	static std::set<Timer*> timers_;
};

Timer *SetTimer(long interval, bool repeat, TimerHandler handler, void *param);
void KillTimer(Timer *timer);

} // namespace sampgdk

#endif // SAMPGDK_TIMERS_H
