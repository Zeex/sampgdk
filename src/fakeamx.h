// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

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
        : size_(std::strlen(s)), address_(FakeAmxPush(s))
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

