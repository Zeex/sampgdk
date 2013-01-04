#include <cstring>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#ifdef WIN32
	#include <windows.h>
#else
	#include <dirent.h>
	#include <fnmatch.h>
#endif

#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include "filterscript.h"
#include "plugin.h"

#ifdef WIN32
	#define PLUGIN_EXT "dll"
#else
	#define PLUGIN_EXT "so"
#endif

#define logprintf sampgdk_logprintf

static void **ppPluginData;

static std::list<Plugin_*> plugins;
static std::list<FilterScript*> filterscripts;

static bool loading = false;

static void *AMXAPI my_amx_Align(void *v) {
	return v;
}

static int AMXAPI my_amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);

	AMX_FUNCSTUBNT *natives = reinterpret_cast<AMX_FUNCSTUBNT*>(amx->base + hdr->natives);
	int num_natives = (hdr->libraries - hdr->natives) / hdr->defsize;

	int error = AMX_ERR_NONE;

	for (int i = 0; i < number || (number <= 0 && nativelist[i].name != 0); i++) {
		for (int j = 0; j < num_natives; j++) {
			char *name = reinterpret_cast<char*>(amx->base + natives[j].nameofs);
			if (natives[j].address == 0 && std::strcmp(name, nativelist[i].name) == 0) {
				natives[j].address = reinterpret_cast<ucell>(nativelist[i].func);
				continue;
			}
		}
	}

	for (int i = 0; i < num_natives; i++) {
		if (natives[i].address == 0) {
			amx->flags &= ~AMX_FLAG_NTVREG;
			return AMX_ERR_NOTFOUND;
		}
	}

	amx->flags |= AMX_FLAG_NTVREG;
	return error;
}

#if defined _WIN32

	template<typename OutputIterator>
	static void GetFilesInDirectory(const std::string &dir,
	                                const std::string &pattern,
	                                OutputIterator result) 
	{
		WIN32_FIND_DATA findFileData;
		HANDLE hFindFile = FindFirstFile((dir + "\\" + pattern).c_str(), &findFileData);
		if (hFindFile != INVALID_HANDLE_VALUE) {
			do {
				if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					*result++ = dir + "\\" + findFileData.cFileName;
				}
			} while (FindNextFile(hFindFile, &findFileData) != 0);
			FindClose(hFindFile);
		}
	}

#else

	template<typename OutputIterator>
	static void GetFilesInDirectory(const std::string &dir,
	                                const std::string &pattern,
	                                OutputIterator result) 
	{
		DIR *dp = 0;
		if ((dp = opendir(dir.c_str())) != 0) {
			struct dirent *dirp;
			while ((dirp = readdir(dp)) != 0) {
				if (!fnmatch(pattern.c_str(), dirp->d_name,
								FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
					*result++ = dir + "/" + dirp->d_name;
				}
			}
			closedir(dp);
		}
	}

#endif

static std::string GetBaseName(const std::string &path) {
	std::string::size_type dot = path.find_last_of(".");
	if (dot == std::string::npos) {
		dot = path.length();
	}
	std::string::size_type sep = path.find_last_of("/\\") + 1;
	if (sep == std::string::npos) {
		sep = 0;
	}
	return std::string(path.begin() + sep, path.begin() + dot);
}

typedef std::list<FilterScript*>::iterator FSIter;

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		if (!(*it)->Exec("OnGameModeInit")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit() {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		if (!(*it)->Exec("OnGameModeExit")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerConnect")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(reason);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerDisconnect")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerSpawn")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(reason);
		ctx.PushCell(killerid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerDeath")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(vehicleid);
		if (!(*it)->Exec("OnVehicleSpawn")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(killerid);
		ctx.PushCell(vehicleid);
		if (!(*it)->Exec("OnVehicleDeath")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char text[]) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushString(text);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerText")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char cmdtext[]) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushString(cmdtext);
		ctx.PushCell(playerid);
		if ((*it)->Exec("OnPlayerCommandText", false)) {
			return true;
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(classid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerRequestClass")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, int ispassenger) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(ispassenger);
		ctx.PushCell(vehicleid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerEnterVehicle")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(vehicleid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerExitVehicle")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(oldstate);
		ctx.PushCell(newstate);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerStateChange")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerEnterCheckpoint")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerLeaveCheckpoint")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerEnterRaceCheckpoint")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerLeaveRaceCheckpoint")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char cmd[]) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushString(cmd);
		if (!(*it)->Exec("OnRconCommand")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerRequestSpawn")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(objectid);
		if (!(*it)->Exec("OnObjectMoved")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(objectid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerObjectMoved")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(pickupid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerPickUpPickup")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(componentid);
		ctx.PushCell(vehicleid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnVehicleMod")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(interiorid);
		ctx.PushCell(enterexit);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnEnterExitModShop")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(paintjobid);
		ctx.PushCell(vehicleid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnVehiclePaintjob")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(color2);
		ctx.PushCell(color1);
		ctx.PushCell(vehicleid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnVehicleRespray")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		ctx.PushCell(vehicleid);
		if (!(*it)->Exec("OnVehicleDamageStatusUpdate")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(passenger_seat);
		ctx.PushCell(playerid);
		ctx.PushCell(vehicleid);
		if (!(*it)->Exec("OnUnoccupiedVehicleUpdate")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(row);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerSelectedMenuRow")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerExitedMenu")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(oldinteriorid);
		ctx.PushCell(newinteriorid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerInteriorChange")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(oldkeys);
		ctx.PushCell(newkeys);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerKeyStateChange")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char ip[], const char password[], int success) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(success);
		ctx.PushString(password);
		ctx.PushString(ip);
		if (!(*it)->Exec("OnRconLoginAttempt")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerUpdate")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(forplayerid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerStreamIn")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(forplayerid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerStreamOut")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(forplayerid);
		ctx.PushCell(vehicleid);
		if (!(*it)->Exec("OnVehicleStreamIn")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(forplayerid);
		ctx.PushCell(vehicleid);
		if (!(*it)->Exec("OnVehicleStreamOut")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char inputtext[]) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushString(inputtext);
		ctx.PushCell(listitem);
		ctx.PushCell(response);
		ctx.PushCell(dialogid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnDialogResponse")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(weaponid);
		ctx.PushFloat(amount);
		ctx.PushCell(issuerid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerTakeDamage")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushCell(weaponid);
		ctx.PushFloat(amount);
		ctx.PushCell(damagedid);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerGiveDamage")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ) {
	for (FSIter it = filterscripts.begin(); it != filterscripts.end(); ++it) {
		ExecContext ctx(*it);
		ctx.PushFloat(fZ);
		ctx.PushFloat(fY);
		ctx.PushFloat(fX);
		ctx.PushCell(playerid);
		if (!(*it)->Exec("OnPlayerClickMap")) {
			return false;
		}
	}
	return true;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
	if (::loading) {
		return false;
	}

	::ppPluginData = ppData;

	void *pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];

	((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align16] = (void*)my_amx_Align;
	((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align32] = (void*)my_amx_Align;
	((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align64] = (void*)my_amx_Align;

	sampgdk_initialize_plugin(ppData);

	return (::loading = true);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
	if (!loading) {
		// Everything is alrady loaded
		return AMX_ERR_NONE;
	}

	logprintf("");
	logprintf("Server Plugins");
	logprintf("--------------");

	std::list<std::string> files;
	GetFilesInDirectory("plugins", "*."PLUGIN_EXT, std::back_inserter(files));

	for (std::list<std::string>::iterator iterator = files.begin();
			iterator != files.end(); ++iterator) {
		std::string plugin_name = GetBaseName(*iterator);
		if (plugin_name == "unlimitedfs") {
			continue;
		}
		logprintf(" Loading plugin: %s", plugin_name.c_str());
		Plugin_ *plugin = new Plugin_(*iterator);
		if (plugin != 0) {
			PluginError error = plugin->Load(ppPluginData);
			if (plugin->IsLoaded()) {
				plugins.push_back(plugin);
				logprintf("  Loaded.");
			} else {
				switch (error) {
					case PLUGIN_ERROR_LOAD: {
						logprintf("  Failed.");
						break;
					}
					case PLUGIN_ERROR_VERSION:
						logprintf("  Unsupported version.");
						break;
					case PLUGIN_ERROR_API:
						logprintf("  Plugin does not conform to acrhitecture.");
						break;
					default:
						break;
				}
				delete plugin;
			}
		}
	}

	logprintf(" Loaded %d plugins.", plugins.size());
	logprintf("\n");

	// Load ALL scripts from "filterscripts/"
	files.clear();
	GetFilesInDirectory("filterscripts", "*.amx", std::back_inserter(files));
	for (std::list<std::string>::iterator iterator = files.begin();
			iterator != files.end(); ++iterator) {
		std::string fs_name = GetBaseName(*iterator);
		logprintf("  Loading filter script: %s", fs_name.c_str());
		FilterScript *fs = new FilterScript(*iterator);
		if (fs != 0) {
			if (fs->IsLoaded()) {
				filterscripts.push_back(fs);
				my_amx_Register(fs->amx(), sampgdk_get_natives(), -1);
				for (std::list<Plugin_*>::iterator iterator = plugins.begin();
						iterator != plugins.end(); ++iterator) {
					(*iterator)->AmxLoad(fs->amx());
				}
				cell retval;
				fs->Init(retval);
				logprintf("   Loaded.");
			} else {
				logprintf("   Failed.");
				delete fs;
			}
		}
	}

	for (std::list<Plugin_*>::iterator iterator = plugins.begin();
			iterator != plugins.end(); ++iterator) {
		(*iterator)->AmxLoad(amx);
	}

	::loading = false;
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
	for (std::list<Plugin_*>::iterator iterator = plugins.begin();
			iterator != plugins.end(); ++iterator) {
		(*iterator)->AmxUnload(amx);
	}
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	sampgdk_finalize();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
	sampgdk_process_timers();
	for (std::list<Plugin_*>::iterator iterator = plugins.begin();
			iterator != plugins.end(); ++iterator) {
		(*iterator)->ProcessTick();
	}
}
