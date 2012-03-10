#include <cstdio>
#include <cstring>

#include <sampgdk/core.h>
#include <sampgdk/players.h>
#include <sampgdk/plugin.h>
#include <sampgdk/samp.h>

typedef void (*logprintf_t)(const char *format, ...);
static logprintf_t logprintf;

void SAMPGDK_CALL Timer(int timerid, void *param) {
	logprintf("timer!");
};

PLUGIN_EXPORT int PLUGIN_CALL OnGameModeInit() {
	SetGameModeText("Hello, World!");

	AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

	logprintf("------------------------------------------\n");
	logprintf("      HelloWorld gamemode got loaded.     \n");
	logprintf("------------------------------------------\n");

	CreateTimer(1000, true, Timer, 0);

	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL OnPlayerConnect(int playerid) {
	SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
	SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
	SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
	SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f, CAMERA_CUT);
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) {
	if (std::strcmp(cmdtext, "/hello") == 0) {
		char name[MAX_PLAYER_NAME];
		GetPlayerName(playerid, name, MAX_PLAYER_NAME);
		char message[128];
		std::sprintf(message, "Hello, %s!", name);
		SendClientMessage(playerid, 0x00FF00FF, message);
		return 1;
	}
	if (std::strcmp(cmdtext, "/pos") == 0) {
		float x, y, z;
		GetPlayerPos(playerid, &x, &y, &z);
		char message[128];
		std::sprintf(message, "You are at (%f, %f, %f)", x, y, z);
		SendClientMessage(playerid, 0xFFFFFFFF, message);
		return 1;
	}
	return 0;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData) {
	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	sampgdk_initialize_plugin(ppPluginData);
	return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	return;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
	sampgdk_process_timers();
}
