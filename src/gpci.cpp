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

#include <sampgdk/gpci.h>
#include <sampgdk/wrapper.h>

#include "fakeamx.h"

namespace sampgdk {

bool gpci(int playerid, char *buffer, std::size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("gpci");
	FakeAmxHeapObject buffer_(size);
	cell params[] = {
		3 * 4,
		playerid,
		buffer_.address(),
		size
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	buffer_.GetAsString(buffer, size);
	return ret;
}

} // namespace sampgdk
