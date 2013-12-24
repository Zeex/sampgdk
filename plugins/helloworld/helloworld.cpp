#include <cstdio>
#include <cstring>

#include <plugin.h>

#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>

using namespace sampgdk;

static ThisPlugin helloworld;

static void SAMPGDK_TIMER_CALL RepeatingTimer(int, void *) {
  ServerLog::Printf("RepeatingTimer");
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  SetGameModeText("Hello, World!");
  AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);
  SetTimer(1000, true, RepeatingTimer, 0);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
  SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
  SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
  SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f, CAMERA_CUT);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) {
  if (std::strcmp(cmdtext, "/hello") == 0) {
    char name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name);
    char message[128];
    std::sprintf(message, "Hello, %s!", name);
    SendClientMessage(playerid, 0x00FF00FF, message);
    return true;
  }
  return false;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return SUPPORTS_VERSION | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  return helloworld.Load(ppData) >= 0;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  helloworld.Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  helloworld.ProcessTimers();
}
