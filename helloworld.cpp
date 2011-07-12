#include "helloworld.h"

using namespace samp;

static HelloWorld theGameMode;

void HelloWorld::OnGameModeInit() {
    SetGameModeText("Hello, World!");

    AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

    logprintf("------------------------------------------\n");
    logprintf("      HelloWorld gamemode got loaded.     \n"); 
    logprintf("------------------------------------------\n");
}

bool HelloWorld::OnPlayerConnect(int playerid) {
    SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
    return true;
}

bool HelloWorld::OnPlayerRequestClass(int playerid) {
    SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    return true;
}

bool HelloWorld::OnPlayerCommandText(int playerid, const std::string &cmdtext) {
    if (cmdtext == "/hello") {
        SendClientMessage(playerid, 0x00FF00FF, "Hello, " + GetPlayerName(playerid) + "!");
        return true;
    }
    return false;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()  {
    return SUPPORTS_VERSION;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)  {
    // This always must be called first
    Wrapper::GetInstance()->Initialize(ppPluginData);
    // Set our gamemode as the main event handler
    EventHandler::SetEventHandler(&::theGameMode);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
}
