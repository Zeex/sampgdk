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

#ifndef SAMPGDK_FAKEAMX_H
#define SAMPGDK_FAKEAMX_H

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

#include <cstddef>
#include <vector>

namespace sampgdk {

class FakeAmx {
public:
	static const std::size_t INITIAL_HEAP_SIZE = 1024;

	FakeAmx();
	static FakeAmx *GetGlobal();

	AMX *amx();

	cell Push(std::size_t cells);
	cell Push(const char *s);

	void Get(cell address, cell &value);
	void Get(cell address, char *value, size_t size);

	void Pop(cell address);

	inline cell CallNative(AMX_NATIVE native, cell *params) {
		return native(&amx_, params);
	}
	inline bool CallNativeBool(AMX_NATIVE native, cell *params) {
		return CallNative(native, params) != 0;
	}
	inline float CallNativeFloat(AMX_NATIVE native, cell *params) {
		cell retval = CallNative(native, params);
		return amx_ctof(retval);
	}

	// Parameter-less versions
	inline cell CallNative(AMX_NATIVE native) {
		return native(&amx_, 0);
	}
	inline bool CallNativeBool(AMX_NATIVE native) {
		return CallNative(native) != 0;
	}
	inline float CallNativeFloat(AMX_NATIVE native) {
		cell retval = CallNative(native);
		return amx_ctof(retval);
	}

private:
	inline cell *GetHeapPtr() {
		return static_cast<cell*>(&heap_[0]);
	}

	void ResizeHeap(std::size_t size);

private:
	AMX amx_;
	AMX_HEADER amxhdr_;

	std::vector<cell> heap_;
};

class FakeAmxHeapObject {
public:
	FakeAmxHeapObject(FakeAmx *fa);
	FakeAmxHeapObject(FakeAmx *fa, std::size_t cells);
	FakeAmxHeapObject(FakeAmx *fa, const char *s);
	~FakeAmxHeapObject();

	inline cell address() const {
		return address_;
	}
	inline std::size_t size() const {
		return size_;
	}

	cell Get() const;
	bool GetAsBool() const;
	float GetAsFloat() const;
	void GetAsString(char *s, std::size_t size) const;

private:
	FakeAmx *fa_;
	std::size_t size_;
	cell address_;
};

} // namespace sampgdk

#endif // !SAMPGDK_FAKEAMX
