#include "helloworld.h"

#include <sampgdk/logprintf.h>
#include <sampgdk/game/samp.h>
#include <sampgdk/game/players.h>
#include <sampgdk/plugin/plugin.h>
#include <sampgdk/wrapper/wrapper.h>

using namespace samp;

static HelloWorld theGameMode;

HelloWorld::HelloWorld() {
    // Register our gamemode in order to catch events - if we don't do this
    // somewhere none of the HelloWorld callbacks will be ever called.
    this->Register();
}

HelloWorld::~HelloWorld() {}

void HelloWorld::OnGameModeInit() {
    SetGameModeText("Hello, World!");

    AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

    logprintf("------------------------------------------\n");
    logprintf(" HelloWorld gamemode got loaded. \n");
    logprintf("------------------------------------------\n");
}

bool HelloWorld::OnPlayerConnect(int playerid) {
    SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
    return true;
}

bool HelloWorld::OnPlayerRequestClass(int playerid, int classid) {
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

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData) {
    // Initialize the wrapper - this always should be done here.
    Wrapper::GetInstance()->Initialize(ppPluginData);
    // Do not call any natives here - they are not yet prepared for use at this stage.
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    return;
}