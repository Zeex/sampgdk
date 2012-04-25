// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#include "fakeamx.h"
#include "natives.h"
#include "timers.h"

#include "generated/a_samp.cpp"

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_SetTimer(int interval, bool repeat, TimerHandler handler, void *param) {
	return sampgdk::Timers::GetInstance().SetTimer(interval, repeat, handler, param);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL sampgdk_KillTimer(int timerid) {
	return sampgdk::Timers::GetInstance().KillTimer(timerid);
}
