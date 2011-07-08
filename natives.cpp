// Calling SA:MP natives from C++

#include <stdexcept>
#include <string>
#include <unordered_map>

#include "jump.h"
#include "plugin.h"

extern void *pAMXFunctions;

static std::unordered_map<std::string, AMX_NATIVE> nativeMap;

static uint32_t amx_Register_addr;
static unsigned char amx_Register_code[5];

static int my_amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, size_t number) {
    // Restore old amx_Register's code so we can invoke it
    memcpy(reinterpret_cast<void*>(::amx_Register_addr), ::amx_Register_code, 5);

    // Store natives in our global container
    for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
        ::nativeMap[nativelist[i].name] = nativelist[i].func;
    }

    // Call the original function
    int retVal = amx_Register(amx, nativelist, number);

    // Set jump again to catch further calls
    SetJump(::amx_Register_addr, reinterpret_cast<uint32_t>(my_amx_Register), ::amx_Register_code);

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

typedef std::basic_string<cell> cellstring;

// A little example. Can be called right from Load().
void SetGameModeText(const std::string &text) {
    static AMX_NATIVE native = 0;
    if (native == 0) {
        // Here for convenience we use the pre-defined __FUNCTION__ macro.
        native = ::nativeMap[__FUNCTION__];
    }
    // Convert std::string to cellstring before passing it.
    cellstring text_(text.begin(), text.end());
    cell params[] = {
        // params[0] is the number of arguments multiplied by sizeof(cell).
        1 * sizeof(cell), 
        // Note that we pass a physical address (see fakeAmxHeader's definition for why, hehe).
        reinterpret_cast<cell>(text_.c_str())
    };
    native(&::fakeAmx, params);
}

// Here we have additional parameters passed by value.
bool SendClientMessage(int playerid, long color, const std::string &message) {
    static AMX_NATIVE native = 0;
    if (native == 0) {
        native = ::nativeMap[__FUNCTION__];
    }
    cellstring message_(message.begin(), message.end());
    cell params[] = {
        3 * sizeof(cell),
        playerid,
        color,
        reinterpret_cast<cell>(message_.c_str())
    };
    return bool(native(&::fakeAmx, params));
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()  {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)  {
    pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

    ::amx_Register_addr = reinterpret_cast<uint32_t>(
        (static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_Register]);
    // Replace first 5 bytes of amx_Register's code with "JMP my_amx_Register"
    SetJump(::amx_Register_addr, reinterpret_cast<uint32_t>(my_amx_Register), ::amx_Register_code);

    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
    SetGameModeText("Hello from C++!!");
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
    return AMX_ERR_NONE;
}
