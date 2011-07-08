#include "jump.h"
#include "plugin.h"
#include "samp.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>

extern void *pAMXFunctions;

static uint32_t amx_Register_addr;
static unsigned char amx_Register_code[5];

static int my_amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, size_t number) {
    // Restore old amx_Register's code so we can invoke it
    memcpy(reinterpret_cast<void*>(::amx_Register_addr), ::amx_Register_code, 5);

    // Store natives in our global container
    for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
        SAMPWrapper::GetInstance().SetNative(nativelist[i].name, nativelist[i].func);
    }

    // Call the original function
    int retVal = amx_Register(amx, nativelist, number);

    // Set jump again to catch further calls
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), my_amx_Register, ::amx_Register_code);

    return retVal;
}

static AMX_HEADER fakeAmxHeader = {
    0, // size
    AMX_MAGIC, // magic
    MIN_FILE_VERSION, // file_version
    MIN_AMX_VERSION, // amx_version
    0, // flags
    0, // defsize
    0, // cod
    -reinterpret_cast<int32_t>(&fakeAmxHeader), // dat
    0, // hea 
    0, // stp
    0, // cip
    0, // publics
    0, // natives
    0, // libraries
    0, // pubvars
    0, // tags
    0, // nametable
};

static AMX fakeAmx = {
    reinterpret_cast<unsigned char*>(&fakeAmxHeader), // base
    0, // data
    amx_Callback, // callback
    0, // debug hook
    0, // cip
    0, // frm
    0, // hea
    0, // hlw
    0, // stk
    INT32_MAX, // stp
    0, // flags
    0, // usertags
    0, // userdata
    AMX_ERR_NONE, // error
    0, // paramcount 
    0, // pri
    0, // alt
    0, // reset_stk
    0, // reset_hea
    0, // sysreq_d
};

static std::runtime_error NoSuchNative(const std::string &nativeName) {
    return std::runtime_error("No such native function: " + nativeName);
}

SAMPWrapper::SAMPWrapper() {}

SAMPWrapper &SAMPWrapper::GetInstance() {
    static SAMPWrapper w;
    return w;
}

void SAMPWrapper::Initialize(void **ppPluginData) {
    pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

    ::amx_Register_addr = reinterpret_cast<uint32_t>(
        (static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_Register]);
    // Replace first 5 bytes of amx_Register's code with "JMP my_amx_Register"
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), my_amx_Register, ::amx_Register_code);
}

void SAMPWrapper::SetNative(const std::string &name, AMX_NATIVE native) {
    if (!name.empty()) {
        natives_[name] = native;
    }
}
    
AMX_NATIVE SAMPWrapper::GetNative(const std::string &name) const {
    auto it = natives_.find(name);
    if (it != natives_.end()) {
        return it->second;
    } 
    return 0;
}

bool SetGameModeText(const std::string &text) {
    static AMX_NATIVE native = SAMPWrapper::GetInstance().GetNative(__FUNCTION__);
    if (native != 0) {
        cellstring text_(text.begin(), text.end());
        cell params[] = {
            1 * sizeof(cell), 
            reinterpret_cast<cell>(text_.c_str())
        };
        bool(native(&::fakeAmx, params));
    } else {
        throw NoSuchNative(__FUNCTION__);
    }
}

bool SendClientMessage(int playerid, long color, const std::string &message) {
    static AMX_NATIVE native = SAMPWrapper::GetInstance().GetNative(__FUNCTION__);
    if (native != 0) {
        cellstring message_(message.begin(), message.end());
        cell params[] = {
            3 * sizeof(cell),
            playerid,
            color,
            reinterpret_cast<cell>(message_.c_str())
        };
        return bool(native(&::fakeAmx, params));
    } else {
        throw NoSuchNative(__FUNCTION__);
    }
}
