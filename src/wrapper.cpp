// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <sampgdk/wrapper.h>

#include "wrapperimpl.h"

namespace sampgdk {

Wrapper::Wrapper() {
    pimpl_ = new WrapperImpl;
}

Wrapper::~Wrapper() {
    delete pimpl_;
}

Wrapper *Wrapper::GetInstance() {
    static Wrapper w;
    return &w;
}

void Wrapper::Initialize(void **ppPluginData) {
    pimpl_->Initialize(ppPluginData);
}

void Wrapper::SetNative(const char *name, AMX_NATIVE native) {
    pimpl_->SetNative(name, native);
}

AMX_NATIVE Wrapper::GetNative(const char *name) const {
    return pimpl_->GetNative(name);
}

void Wrapper::SetPublicHook(const char *name, PublicHook handler) {
    pimpl_->SetPublicHook(name, handler);
}

bool Wrapper::ExecutePublicHook(AMX *amx, cell *retval, const char *name) const {
    return pimpl_->ExecutePublicHook(amx, retval, name);
}

} // namespace sampgdk

