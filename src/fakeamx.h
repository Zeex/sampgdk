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

#ifndef FAKEAMX_H
#define FAKEAMX_H

#include <cstring>

#include <sampgdk/amxplugin.h>

extern AMX fakeAmx;

cell FakeAmxPush(size_t cells);
cell FakeAmxPush(const char *s);

void FakeAmxGet(cell address, cell &value);
void FakeAmxGet(cell address, char *value, size_t size);

void FakeAmxPop(cell address);

class FakeAmxHeapObject {
public:
    FakeAmxHeapObject()
        : size_(1), address_(FakeAmxPush(1))
    {}

    FakeAmxHeapObject(size_t cells)
        : size_(cells), address_(FakeAmxPush(cells))
    {}

    FakeAmxHeapObject(const char *s)
        : size_(std::strlen(s) + 1), address_(FakeAmxPush(s))
    {}

    ~FakeAmxHeapObject() { FakeAmxPop(address_); }

    cell address() const { return address_; }

    size_t size() const { return size_; }

    cell Get() const {
        return *reinterpret_cast<cell*>(::fakeAmx.data + address_);
    }

    float GetAsFloat() const {
        cell value = this->Get();
        return amx_ctof(value);
    }

    void GetAsString(char *s, size_t size) const {
        FakeAmxGet(address_, s, size);
    }

private:
    size_t size_;
    cell address_;
};

#endif

