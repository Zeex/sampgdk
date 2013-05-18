#include <cstring>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <sstream>
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
  #define PLUGIN_EXT ".dll"
#else
  #define PLUGIN_EXT ".so"
#endif

namespace {

ThisPlugin ufs;

void **ppPluginData;

typedef std::map<std::string, unlimitedfs::FilterScript*> FSMap;
FSMap fs_map;

typedef std::map<std::string, unlimitedfs::Plugin*> PluginMap;
PluginMap plugin_map;

bool loading = false;

void *AMXAPI my_amx_Align(void *v) {
  return v;
}

int AMXAPI my_amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
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

std::string GetServerCfgOption(const std::string &option) {
  std::string name, value;
  std::string line;
  std::fstream server_cfg("server.cfg");
  if (server_cfg) {
    while (std::getline(server_cfg, line)) {
      std::stringstream ss(line);
      ss >> name;
      if (name == option) {
        ss >> value;
        break;
      }
    }
  }
  return value;
}

void SplitString(const std::string &string, std::list<std::string> &substrings) {
  std::stringstream stream(string);
  std::copy(
    std::istream_iterator<std::string>(stream),
    std::istream_iterator<std::string>(),
    std::back_inserter(substrings)
  );
}

void GetFilterScriptNames(std::list<std::string> &names) {
  std::string opt = GetServerCfgOption("filterscripts2");
  if (!opt.empty()) {
    SplitString(opt, names);
  }
}

static void GetPluginNames(std::list<std::string> &names) {
  std::string opt = GetServerCfgOption("plugins2");
  if (!opt.empty()) {
    SplitString(opt, names);
  }
}

bool StringEndsWith(const std::string &s, const std::string &what) {
  return s.rfind(what) == s.length() - what.length();
}

std::string GetItemPath(const std::string &name, const std::string &dir,
                        const std::string &ext) {
  std::string path;
  path.append(dir);
  path.append("/");
  path.append(name);
  if (!StringEndsWith(name, ext)) {
    path.append(ext);
  }
  return path;
}

std::string GetFilterScriptPath(const std::string &name) {
  return GetItemPath(name, "filterscripts", ".amx");
}

std::string GetPluginPath(const std::string &name) {
  return GetItemPath(name, "plugins", PLUGIN_EXT);
}

bool LoadFilterScript(const std::string &name) {
  unlimitedfs::FilterScript *fs = new unlimitedfs::FilterScript(GetFilterScriptPath(name));
  if (fs == 0 || !fs->IsLoaded()) {
    delete fs;
    return false;
  }

  fs_map.insert(std::make_pair(name, fs));

  // Notify plugins about the newly loaded AMX.
  my_amx_Register(fs->amx(), sampgdk_get_natives(), -1);
  for (PluginMap::iterator it = plugin_map.begin(); it != plugin_map.end(); ++it) {
    unlimitedfs::Plugin *plugin = it->second;
    plugin->AmxLoad(fs->amx());
  }

  fs->Init();
  return true;
}

bool UnloadFilterScript(unlimitedfs::FilterScript *fs) {
  fs->Exit();
  fs->Unload();
  return true;
}

bool UnloadFilterScript(const std::string &name) {
  FSMap::iterator it = fs_map.find(name);
  if (it == fs_map.end()) {
    return false;
  }

  unlimitedfs::FilterScript *fs = it->second;
  return UnloadFilterScript(fs);
}

void LoadFilterScriptRcon(const std::string &name) {
  if (!LoadFilterScript(name)) {
    ServerLog::Printf("  Filterscript '%s' load failed.", name.c_str());
  }
}

void UnloadFilterScriptRcon(const std::string &name) {
  if (!UnloadFilterScript(name)) {
    ServerLog::Printf("  Filterscript '%s' unload failed.", name.c_str());
  }
}

void ProcessRconCommand(const char *cmd) {
  std::string name, value;
  std::stringstream stream(cmd);
  stream >> name;
  stream >> value;

  const std::string &fs_name = value;
  if (name == "loadfs2") {
    LoadFilterScriptRcon(fs_name);
  } else if (name == "unloadfs2") {
    UnloadFilterScriptRcon(fs_name);
  } else if (name == "reloadfs2") {
    LoadFilterScriptRcon(fs_name);
    UnloadFilterScriptRcon(fs_name);
  }
}

} // anonymous namespace

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    if (!it->second->Exec("OnGameModeInit")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit() {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    if (!it->second->Exec("OnGameModeExit")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerConnect")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(reason);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerDisconnect")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerSpawn")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(reason);
    ctx.PushCell(killerid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerDeath")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(vehicleid);
    if (!it->second->Exec("OnVehicleSpawn")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(killerid);
    ctx.PushCell(vehicleid);
    if (!it->second->Exec("OnVehicleDeath")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char text[]) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushString(text);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerText")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char cmdtext[]) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushString(cmdtext);
    ctx.PushCell(playerid);
    if (it->second->Exec("OnPlayerCommandText", false)) {
      return true;
    }
  }
  return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(classid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerRequestClass")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, int ispassenger) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(ispassenger);
    ctx.PushCell(vehicleid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerEnterVehicle")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(vehicleid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerExitVehicle")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(oldstate);
    ctx.PushCell(newstate);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerStateChange")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerEnterCheckpoint")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerLeaveCheckpoint")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerEnterRaceCheckpoint")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerLeaveRaceCheckpoint")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char cmd[]) {
  ProcessRconCommand(cmd);
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushString(cmd);
    if (!it->second->Exec("OnRconCommand")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerRequestSpawn")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(objectid);
    if (!it->second->Exec("OnObjectMoved")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(objectid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerObjectMoved")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(pickupid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerPickUpPickup")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(componentid);
    ctx.PushCell(vehicleid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnVehicleMod")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(interiorid);
    ctx.PushCell(enterexit);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnEnterExitModShop")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(paintjobid);
    ctx.PushCell(vehicleid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnVehiclePaintjob")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(color2);
    ctx.PushCell(color1);
    ctx.PushCell(vehicleid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnVehicleRespray")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    ctx.PushCell(vehicleid);
    if (!it->second->Exec("OnVehicleDamageStatusUpdate")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(passenger_seat);
    ctx.PushCell(playerid);
    ctx.PushCell(vehicleid);
    if (!it->second->Exec("OnUnoccupiedVehicleUpdate")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(row);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerSelectedMenuRow")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerExitedMenu")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(oldinteriorid);
    ctx.PushCell(newinteriorid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerInteriorChange")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(oldkeys);
    ctx.PushCell(newkeys);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerKeyStateChange")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char ip[], const char password[], int success) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(success);
    ctx.PushString(password);
    ctx.PushString(ip);
    if (!it->second->Exec("OnRconLoginAttempt")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerUpdate")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(forplayerid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerStreamIn")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(forplayerid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerStreamOut")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(forplayerid);
    ctx.PushCell(vehicleid);
    if (!it->second->Exec("OnVehicleStreamIn")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(forplayerid);
    ctx.PushCell(vehicleid);
    if (!it->second->Exec("OnVehicleStreamOut")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char inputtext[]) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushString(inputtext);
    ctx.PushCell(listitem);
    ctx.PushCell(response);
    ctx.PushCell(dialogid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnDialogResponse")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(weaponid);
    ctx.PushFloat(amount);
    ctx.PushCell(issuerid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerTakeDamage")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushCell(weaponid);
    ctx.PushFloat(amount);
    ctx.PushCell(damagedid);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerGiveDamage")) {
      return false;
    }
  }
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ) {
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    unlimitedfs::ExecContext ctx(it->second);
    ctx.PushFloat(fZ);
    ctx.PushFloat(fY);
    ctx.PushFloat(fX);
    ctx.PushCell(playerid);
    if (!it->second->Exec("OnPlayerClickMap")) {
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

  if (ufs.Load(ppData) < 0) {
    return false;
  }

  return (::loading = true);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
  ServerLog::Printf("");
  ServerLog::Printf("Server Plugins");
  ServerLog::Printf("--------------");

  std::list<std::string> plugin_names;
  GetPluginNames(plugin_names);

  for (std::list<std::string>::const_iterator it = plugin_names.begin(); it != plugin_names.end(); ++it) {
    const std::string &plugin_name = *it;
    ServerLog::Printf(" Loading plugin: %s", plugin_name.c_str());

    unlimitedfs::Plugin *plugin = new unlimitedfs::Plugin(GetPluginPath(plugin_name));
    if (plugin != 0) {
      unlimitedfs::PluginError error = plugin->Load(ppPluginData);
      if (plugin->IsLoaded()) {
        ::plugin_map.insert(std::make_pair(plugin_name, plugin));
        ServerLog::Printf("  Loaded.");
      } else {
        switch (error) {
          case unlimitedfs::PLUGIN_ERROR_LOAD: {
            ServerLog::Printf("  Failed.");
            break;
          }
          case unlimitedfs::PLUGIN_ERROR_VERSION:
            ServerLog::Printf("  Unsupported version.");
            break;
          case unlimitedfs::PLUGIN_ERROR_API:
            ServerLog::Printf("  Plugin does not conform to acrhitecture.");
            break;
          default:
            break;
        }
        delete plugin;
      }
    }
  }

  ServerLog::Printf(" Loaded %d plugin", ::plugin_map.size());
  ServerLog::Printf("\n");

  std::list<std::string> fs_names;
  GetFilterScriptNames(fs_names);

  for (std::list<std::string>::const_iterator it = fs_names.begin(); it != fs_names.end(); ++it) {
    const std::string &fs_name = *it;
    ServerLog::Printf("  Loading filter script: %s", fs_name.c_str());

    if (LoadFilterScript(fs_name)) {
      ServerLog::Printf("   Loaded.");
    } else {
      ServerLog::Printf("   Failed.");
    }
  }

  for (PluginMap::iterator it = ::plugin_map.begin(); it != ::plugin_map.end(); ++it) {
    it->second->AmxLoad(amx);
  }

  ::loading = false;
  return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
  for (PluginMap::iterator it = ::plugin_map.begin(); it != ::plugin_map.end(); ++it) {
    it->second->AmxUnload(amx);
  }
  return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  ufs.Unload();
  for (FSMap::iterator it = ::fs_map.begin(); it != ::fs_map.end(); ++it) {
    UnloadFilterScript(it->second);
  }
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  ufs.ProcessTimers();
  for (PluginMap::iterator it = ::plugin_map.begin(); it != ::plugin_map.end(); ++it) {
    it->second->ProcessTick();
  }
}
