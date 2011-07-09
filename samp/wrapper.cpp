#include "wrapper.h"
#include "jump.h"

#include "plugin/amx/amx.h"
#include "plugin/plugincommon.h"

extern void *pAMXFunctions;

static uint32_t amx_Register_addr;
static unsigned char amx_Register_code[5];

namespace samp {

Wrapper::Wrapper() {}

Wrapper *Wrapper::GetInstance() {
    static Wrapper w;
    return &w;
}

static int my_amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, size_t number) {
    // Restore old amx_Register's code so we can call it
    memcpy(reinterpret_cast<void*>(::amx_Register_addr), ::amx_Register_code, 5);

    // Store natives in our global container
    for (size_t i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
        Wrapper::GetInstance()->SetNative(nativelist[i].name, nativelist[i].func);
    }

    // Call the original function
    int retVal = amx_Register(amx, nativelist, number);

    // Set jump again to catch further calls
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), my_amx_Register, ::amx_Register_code);

    return retVal;
}

void Wrapper::Initialize(void **ppPluginData) {
    pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

    ::amx_Register_addr = reinterpret_cast<uint32_t>(
        (static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_Register]);
    // Replace first 5 bytes of amx_Register's code with "JMP my_amx_Register"
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), my_amx_Register, ::amx_Register_code);
}

void Wrapper::SetNative(const std::string &name, AMX_NATIVE native) {
    if (!name.empty()) {
        natives_[name] = native;
    }
}
    
AMX_NATIVE Wrapper::GetNative(const std::string &name) const {
    auto it = natives_.find(name);
    if (it != natives_.end()) {
        return it->second;
    } 
    return 0;
}

} // namespace samp