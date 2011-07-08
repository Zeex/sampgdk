// Calling SA:MP natives from C++

#include "plugin.h"
#include "samp.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()  {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)  {
    SAMPWrapper::GetInstance().Initialize(ppPluginData);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
    try {
        SetGameModeText("Hello from C++!!");
    } catch (std::exception &e) {
        printf("%s\n", e.what());
    }
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
    return AMX_ERR_NONE;
}
