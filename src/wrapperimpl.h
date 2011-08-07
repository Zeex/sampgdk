// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <map>
#include <string>

#include <sampgdk/amx/amx.h>
#include <sampgdk/wrapper.h>

namespace sampgdk {

class WrapperImpl {
public:
    WrapperImpl();

    void Initialize(void **ppPluginData);

    void SetNative(const char *name, AMX_NATIVE native);
    AMX_NATIVE GetNative(const char *name) const;

    void SetPublicHook(const char *name, PublicHook handler);
    bool ExecutePublicHook(AMX *amx, cell *retval, const char *name) const;

private:
    std::map<std::string, AMX_NATIVE> natives_;
    std::map<std::string, PublicHook> publicHooks_;
};

} // namespace sampgdk
