// Copyright (c) 2011 Zeex
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
#include <sampgdk/amx/amx.h>

#include "fakeamx.h"

#include <cstddef>
#include <cstring>
#include <limits>

FakeAmx::FakeAmx() 
	: heap_(INITIAL_HEAP_SIZE)
{
	std::memset(&hdr_, 0, sizeof(hdr_));
	std::memset(&amx_, 0, sizeof(amx_));

	hdr_.magic = AMX_MAGIC;
	hdr_.file_version = MIN_FILE_VERSION;
	hdr_.amx_version = MIN_AMX_VERSION;
	hdr_.dat = reinterpret_cast<int32_t>(&heap_[0]) - 
		reinterpret_cast<int32_t>(&hdr_);

	amx_.base = reinterpret_cast<unsigned char*>(&hdr_);
	amx_.data = reinterpret_cast<unsigned char*>(&heap_[0]);
	amx_.callback = amx_Callback;
	amx_.stp = std::numeric_limits<cell>::max();
	amx_.error = AMX_ERR_NONE;
}

FakeAmx::~FakeAmx() {
}

FakeAmx &FakeAmx::GetInstance() {
	static FakeAmx instance;
	return instance;
}

cell FakeAmx::Push(size_t cells) {
	cell address = amx_.hea;
	amx_.hea += cells * sizeof(cell);
	if (amx_.hea >= static_cast<cell>(heap_.size())) {
		heap_.resize(amx_.hea);
	}
	return address;
}

cell FakeAmx::Push(const char *s) {
	std::size_t size = std::strlen(s) + 1;
	cell address = Push(size);
	amx_SetString(&heap_[0] + address/sizeof(cell), s, 0, 0, size);
	return address;
}

void FakeAmx::Get(cell address, cell &value) const {
	value = heap_[address/sizeof(cell)];
}

void FakeAmx::Get(cell address, char *value, size_t size) const {
	const cell *ptr = &heap_[0] + address/sizeof(cell);
	amx_GetString(value, ptr, 0, size);
}

void FakeAmx::Pop(cell address) {
	if (amx_.hea > address) {
		amx_.hea = address;
	}
}

cell FakeAmx::CallNative(AMX_NATIVE native, cell *params) {
	return native(&amx_, params);
}

bool FakeAmx::CallBooleanNative(AMX_NATIVE native, cell *params) {
	return CallNative(native, params) != 0;
}

FakeAmxHeapObject::FakeAmxHeapObject()
	: size_(1), address_(FakeAmx::GetInstance().Push(1))
{}

FakeAmxHeapObject::FakeAmxHeapObject(size_t cells)
	: size_(cells), address_(FakeAmx::GetInstance().Push(cells))
{}

FakeAmxHeapObject::FakeAmxHeapObject(const char *s)
	: size_(std::strlen(s) + 1), address_(FakeAmx::GetInstance().Push(s))
{}

FakeAmxHeapObject::~FakeAmxHeapObject() { FakeAmx::GetInstance().Pop(address_); }

cell FakeAmxHeapObject::address() const { return address_; }

size_t FakeAmxHeapObject::size() const { return size_; }

cell FakeAmxHeapObject::Get() const {
	cell value;
	FakeAmx::GetInstance().Get(address_, value);
	return value;
}

float FakeAmxHeapObject::GetAsFloat() const {
	cell value = this->Get();
	return amx_ctof(value);
}

void FakeAmxHeapObject::GetAsString(char *s, size_t size) const {
	FakeAmx::GetInstance().Get(address_, s, size);
}
