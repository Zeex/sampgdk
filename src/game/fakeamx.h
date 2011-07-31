#ifndef FAKEAMX_H
#define FAKEAMX_H

#include <sampgdk/plugin/amx/amx.h>

extern AMX fakeAmx;

cell FakeAmxPush(void *what, size_t cells);
void FakeAmxPop(cell address);

class FakeAmxHeapObject {
public:
    FakeAmxHeapObject(void *obj, size_t cells) 
        : size_(cells), address_(FakeAmxPush(obj, cells))
    {}

    ~FakeAmxHeapObject() { FakeAmxPop(address_); }

    cell address() const { return address_; }

    size_t size() const { return size_; }

    cell asCell() const { 
        return *reinterpret_cast<cell*>(::fakeAmx.data + address_); 
    }

    float asFloat() const {
        cell v = this->asCell();
        return amx_ctof(v);
    }

    char *asString() const {
        return reinterpret_cast<char*>(::fakeAmx.data + address_);
    }

private:
    size_t size_;
    cell address_;
};

#endif

