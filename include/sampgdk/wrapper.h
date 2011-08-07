// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#ifndef SAMPGDK_WRAPPER_H
#define SAMPGDK_WRAPPER_H

#include <sampgdk/amxplugin.h>
#include <sampgdk/export.h>

namespace sampgdk {

class PublicHook {
public:
    typedef cell (AMXAPI *Handler)(AMX *amx);

    PublicHook(Handler handler, cell badReturn) 
        : handler_(handler), badReturn_(badReturn)
    {}

    inline bool Execute(AMX *amx, cell *retval) const {
        return ((*retval = handler_(amx)) != badReturn_);
    }

private:
    Handler handler_;
    cell badReturn_;
};

class WrapperImpl;

class SAMPGDK_EXPORT Wrapper {
public:
    ~Wrapper();

    static Wrapper *GetInstance();

    void Initialize(void **ppPluginData);

    void SetNative(const char *name, AMX_NATIVE native);
    AMX_NATIVE GetNative(const char *name) const;

    void SetPublicHook(const char *name, PublicHook handler);
    bool ExecutePublicHook(AMX *amx, cell *retval, const char *name) const;

private:
    Wrapper();
    WrapperImpl *pimpl_;
};

} // namespace sampgdk

#endif

