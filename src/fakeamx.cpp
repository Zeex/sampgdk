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
#include <sampgdk/amx.h>

#include <cstddef>
#include <cstring>
#include <limits>

#include "fakeamx.h"

namespace sampgdk {

FakeAmx::FakeAmx()
	: heap_(INITIAL_HEAP_SIZE)
{
	std::memset(&amxhdr_, 0, sizeof(amxhdr_));
	amxhdr_.magic = AMX_MAGIC;
	amxhdr_.file_version = MIN_FILE_VERSION;
	amxhdr_.amx_version = MIN_AMX_VERSION;
	amxhdr_.dat = reinterpret_cast<int32_t>(GetHeapPtr()) - reinterpret_cast<int32_t>(&amxhdr_);

	std::memset(&amx_, 0, sizeof(amx_));
	amx_.base = reinterpret_cast<unsigned char*>(&amxhdr_);
	amx_.data = reinterpret_cast<unsigned char*>(GetHeapPtr());
	amx_.callback = amx_Callback;
	amx_.stp = std::numeric_limits<int32_t>::max();
}

// static
FakeAmx *FakeAmx::GetGlobal() {
	static FakeAmx instance;
	return &instance;
}

cell FakeAmx::Push(std::size_t cells) {
	cell address = amx_.hea;
	amx_.hea += cells * sizeof(cell);
	if (amx_.hea / sizeof(cell) >= static_cast<cell>(heap_.size())) {
		ResizeHeap(amx_.hea / sizeof(cell));
	}
	return address;
}

cell FakeAmx::Push(const char *s) {
	std::size_t size = std::strlen(s) + 1;
	cell address = Push(size);
	amx_SetString(GetHeapPtr() + address / sizeof(cell), s, 0, 0, size);
	return address;
}

void FakeAmx::Get(cell address, cell &value) {
	value = heap_[address / sizeof(cell)];
}

void FakeAmx::Get(cell address, char *value, size_t size) {
	const cell *ptr = GetHeapPtr() + address / sizeof(cell);
	amx_GetString(value, ptr, 0, size);
}

void FakeAmx::Pop(cell address) {
	if (amx_.hea > address) {
		amx_.hea = address;
	}
}

void FakeAmx::ResizeHeap(std::size_t size) {
	heap_.resize(amx_.hea / sizeof(cell));

	// Since the heap address has changed we have to update data pointers.
	amx_.data = reinterpret_cast<unsigned char*>(GetHeapPtr());
	amxhdr_.dat = reinterpret_cast<int32_t>(GetHeapPtr()) - reinterpret_cast<int32_t>(&amxhdr_);
}

FakeAmxHeapObject::FakeAmxHeapObject(FakeAmx *fa)
	: fa_(fa), size_(1), address_(fa->Push(1))
{}

FakeAmxHeapObject::FakeAmxHeapObject(FakeAmx *fa, size_t cells)
	: fa_(fa), size_(cells), address_(fa->Push(cells))
{}

FakeAmxHeapObject::FakeAmxHeapObject(FakeAmx *fa, const char *s)
	: fa_(fa), size_(std::strlen(s) + 1), address_(fa->Push(s))
{}

FakeAmxHeapObject::~FakeAmxHeapObject() {
	fa_->Pop(address_);
}

cell FakeAmxHeapObject::Get() const {
	cell value;
	fa_->Get(address_, value);
	return value;
}

bool FakeAmxHeapObject::GetAsBool() const {
	return Get() != 0;
}

float FakeAmxHeapObject::GetAsFloat() const {
	cell value = Get();
	return amx_ctof(value);
}

void FakeAmxHeapObject::GetAsString(char *s, std::size_t size) const {
	fa_->Get(address_, s, size);
}

} // namespace sampgdk
