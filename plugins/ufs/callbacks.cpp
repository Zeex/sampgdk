#include "ufs.h"

namespace ufs {

class OnGameModeInit {
 public:
  OnGameModeInit() {}
  bool operator()(Script *s) {
    return s->Exec("OnGameModeInit", true);
  }
 private:
};

class OnGameModeExit {
 public:
  OnGameModeExit() {}
  bool operator()(Script *s) {
    return s->Exec("OnGameModeExit", true);
  }
 private:
};

class OnPlayerConnect {
 public:
  OnPlayerConnect(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerConnect", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerDisconnect {
 public:
  OnPlayerDisconnect(int playerid, int reason): playerid(playerid), reason(reason) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), reason);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerDisconnect", true);
    return ret;
  }
 private:
  int playerid;
  int reason;
};

class OnPlayerSpawn {
 public:
  OnPlayerSpawn(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerSpawn", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerDeath {
 public:
  OnPlayerDeath(int playerid, int killerid, int reason): playerid(playerid), killerid(killerid), reason(reason) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), reason);
    amx_Push(s->amx(), killerid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerDeath", true);
    return ret;
  }
 private:
  int playerid;
  int killerid;
  int reason;
};

class OnVehicleSpawn {
 public:
  OnVehicleSpawn(int vehicleid): vehicleid(vehicleid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), vehicleid);
    bool ret = s->Exec("OnVehicleSpawn", true);
    return ret;
  }
 private:
  int vehicleid;
};

class OnVehicleDeath {
 public:
  OnVehicleDeath(int vehicleid, int killerid): vehicleid(vehicleid), killerid(killerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), killerid);
    amx_Push(s->amx(), vehicleid);
    bool ret = s->Exec("OnVehicleDeath", true);
    return ret;
  }
 private:
  int vehicleid;
  int killerid;
};

class OnPlayerText {
 public:
  OnPlayerText(int playerid, const char * text): playerid(playerid), text(text) {}
  bool operator()(Script *s) {
    cell text_;
    amx_PushString(s->amx(), &text_, 0, text, 0, 0);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerText", true);
    amx_Release(s->amx(), text_);
    return ret;
  }
 private:
  int playerid;
  const char * text;
};

class OnPlayerCommandText {
 public:
  OnPlayerCommandText(int playerid, const char * cmdtext): playerid(playerid), cmdtext(cmdtext) {}
  bool operator()(Script *s) {
    cell cmdtext_;
    amx_PushString(s->amx(), &cmdtext_, 0, cmdtext, 0, 0);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerCommandText", false);
    amx_Release(s->amx(), cmdtext_);
    return ret;
  }
 private:
  int playerid;
  const char * cmdtext;
};

class OnPlayerRequestClass {
 public:
  OnPlayerRequestClass(int playerid, int classid): playerid(playerid), classid(classid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), classid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerRequestClass", true);
    return ret;
  }
 private:
  int playerid;
  int classid;
};

class OnPlayerEnterVehicle {
 public:
  OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger): playerid(playerid), vehicleid(vehicleid), ispassenger(ispassenger) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), ispassenger);
    amx_Push(s->amx(), vehicleid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerEnterVehicle", true);
    return ret;
  }
 private:
  int playerid;
  int vehicleid;
  bool ispassenger;
};

class OnPlayerExitVehicle {
 public:
  OnPlayerExitVehicle(int playerid, int vehicleid): playerid(playerid), vehicleid(vehicleid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), vehicleid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerExitVehicle", true);
    return ret;
  }
 private:
  int playerid;
  int vehicleid;
};

class OnPlayerStateChange {
 public:
  OnPlayerStateChange(int playerid, int newstate, int oldstate): playerid(playerid), newstate(newstate), oldstate(oldstate) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), oldstate);
    amx_Push(s->amx(), newstate);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerStateChange", true);
    return ret;
  }
 private:
  int playerid;
  int newstate;
  int oldstate;
};

class OnPlayerEnterCheckpoint {
 public:
  OnPlayerEnterCheckpoint(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerEnterCheckpoint", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerLeaveCheckpoint {
 public:
  OnPlayerLeaveCheckpoint(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerLeaveCheckpoint", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerEnterRaceCheckpoint {
 public:
  OnPlayerEnterRaceCheckpoint(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerEnterRaceCheckpoint", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerLeaveRaceCheckpoint {
 public:
  OnPlayerLeaveRaceCheckpoint(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerLeaveRaceCheckpoint", true);
    return ret;
  }
 private:
  int playerid;
};

class OnRconCommand {
 public:
  OnRconCommand(const char * cmd): cmd(cmd) {}
  bool operator()(Script *s) {
    cell cmd_;
    amx_PushString(s->amx(), &cmd_, 0, cmd, 0, 0);
    bool ret = s->Exec("OnRconCommand", false);
    amx_Release(s->amx(), cmd_);
    return ret;
  }
 private:
  const char * cmd;
};

class OnPlayerRequestSpawn {
 public:
  OnPlayerRequestSpawn(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerRequestSpawn", true);
    return ret;
  }
 private:
  int playerid;
};

class OnObjectMoved {
 public:
  OnObjectMoved(int objectid): objectid(objectid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), objectid);
    bool ret = s->Exec("OnObjectMoved", true);
    return ret;
  }
 private:
  int objectid;
};

class OnPlayerObjectMoved {
 public:
  OnPlayerObjectMoved(int playerid, int objectid): playerid(playerid), objectid(objectid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), objectid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerObjectMoved", true);
    return ret;
  }
 private:
  int playerid;
  int objectid;
};

class OnPlayerPickUpPickup {
 public:
  OnPlayerPickUpPickup(int playerid, int pickupid): playerid(playerid), pickupid(pickupid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), pickupid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerPickUpPickup", true);
    return ret;
  }
 private:
  int playerid;
  int pickupid;
};

class OnVehicleMod {
 public:
  OnVehicleMod(int playerid, int vehicleid, int componentid): playerid(playerid), vehicleid(vehicleid), componentid(componentid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), componentid);
    amx_Push(s->amx(), vehicleid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnVehicleMod", true);
    return ret;
  }
 private:
  int playerid;
  int vehicleid;
  int componentid;
};

class OnEnterExitModShop {
 public:
  OnEnterExitModShop(int playerid, int enterexit, int interiorid): playerid(playerid), enterexit(enterexit), interiorid(interiorid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), interiorid);
    amx_Push(s->amx(), enterexit);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnEnterExitModShop", true);
    return ret;
  }
 private:
  int playerid;
  int enterexit;
  int interiorid;
};

class OnVehiclePaintjob {
 public:
  OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid): playerid(playerid), vehicleid(vehicleid), paintjobid(paintjobid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), paintjobid);
    amx_Push(s->amx(), vehicleid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnVehiclePaintjob", true);
    return ret;
  }
 private:
  int playerid;
  int vehicleid;
  int paintjobid;
};

class OnVehicleRespray {
 public:
  OnVehicleRespray(int playerid, int vehicleid, int color1, int color2): playerid(playerid), vehicleid(vehicleid), color1(color1), color2(color2) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), color2);
    amx_Push(s->amx(), color1);
    amx_Push(s->amx(), vehicleid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnVehicleRespray", true);
    return ret;
  }
 private:
  int playerid;
  int vehicleid;
  int color1;
  int color2;
};

class OnVehicleDamageStatusUpdate {
 public:
  OnVehicleDamageStatusUpdate(int vehicleid, int playerid): vehicleid(vehicleid), playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    amx_Push(s->amx(), vehicleid);
    bool ret = s->Exec("OnVehicleDamageStatusUpdate", true);
    return ret;
  }
 private:
  int vehicleid;
  int playerid;
};

class OnUnoccupiedVehicleUpdate {
 public:
  OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat): vehicleid(vehicleid), playerid(playerid), passenger_seat(passenger_seat) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), passenger_seat);
    amx_Push(s->amx(), playerid);
    amx_Push(s->amx(), vehicleid);
    bool ret = s->Exec("OnUnoccupiedVehicleUpdate", true);
    return ret;
  }
 private:
  int vehicleid;
  int playerid;
  int passenger_seat;
};

class OnPlayerSelectedMenuRow {
 public:
  OnPlayerSelectedMenuRow(int playerid, int row): playerid(playerid), row(row) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), row);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerSelectedMenuRow", true);
    return ret;
  }
 private:
  int playerid;
  int row;
};

class OnPlayerExitedMenu {
 public:
  OnPlayerExitedMenu(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerExitedMenu", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerInteriorChange {
 public:
  OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid): playerid(playerid), newinteriorid(newinteriorid), oldinteriorid(oldinteriorid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), oldinteriorid);
    amx_Push(s->amx(), newinteriorid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerInteriorChange", true);
    return ret;
  }
 private:
  int playerid;
  int newinteriorid;
  int oldinteriorid;
};

class OnPlayerKeyStateChange {
 public:
  OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys): playerid(playerid), newkeys(newkeys), oldkeys(oldkeys) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), oldkeys);
    amx_Push(s->amx(), newkeys);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerKeyStateChange", true);
    return ret;
  }
 private:
  int playerid;
  int newkeys;
  int oldkeys;
};

class OnRconLoginAttempt {
 public:
  OnRconLoginAttempt(const char * ip, const char * password, bool success): ip(ip), password(password), success(success) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), success);
    cell password_;
    amx_PushString(s->amx(), &password_, 0, password, 0, 0);
    cell ip_;
    amx_PushString(s->amx(), &ip_, 0, ip, 0, 0);
    bool ret = s->Exec("OnRconLoginAttempt", true);
    amx_Release(s->amx(), ip_);
    amx_Release(s->amx(), password_);
    return ret;
  }
 private:
  const char * ip;
  const char * password;
  bool success;
};

class OnPlayerUpdate {
 public:
  OnPlayerUpdate(int playerid): playerid(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerUpdate", true);
    return ret;
  }
 private:
  int playerid;
};

class OnPlayerStreamIn {
 public:
  OnPlayerStreamIn(int playerid, int forplayerid): playerid(playerid), forplayerid(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerStreamIn", true);
    return ret;
  }
 private:
  int playerid;
  int forplayerid;
};

class OnPlayerStreamOut {
 public:
  OnPlayerStreamOut(int playerid, int forplayerid): playerid(playerid), forplayerid(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerStreamOut", true);
    return ret;
  }
 private:
  int playerid;
  int forplayerid;
};

class OnVehicleStreamIn {
 public:
  OnVehicleStreamIn(int vehicleid, int forplayerid): vehicleid(vehicleid), forplayerid(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid);
    amx_Push(s->amx(), vehicleid);
    bool ret = s->Exec("OnVehicleStreamIn", true);
    return ret;
  }
 private:
  int vehicleid;
  int forplayerid;
};

class OnVehicleStreamOut {
 public:
  OnVehicleStreamOut(int vehicleid, int forplayerid): vehicleid(vehicleid), forplayerid(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid);
    amx_Push(s->amx(), vehicleid);
    bool ret = s->Exec("OnVehicleStreamOut", true);
    return ret;
  }
 private:
  int vehicleid;
  int forplayerid;
};

class OnDialogResponse {
 public:
  OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext): playerid(playerid), dialogid(dialogid), response(response), listitem(listitem), inputtext(inputtext) {}
  bool operator()(Script *s) {
    cell inputtext_;
    amx_PushString(s->amx(), &inputtext_, 0, inputtext, 0, 0);
    amx_Push(s->amx(), listitem);
    amx_Push(s->amx(), response);
    amx_Push(s->amx(), dialogid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnDialogResponse", false);
    amx_Release(s->amx(), inputtext_);
    return ret;
  }
 private:
  int playerid;
  int dialogid;
  int response;
  int listitem;
  const char * inputtext;
};

class OnPlayerTakeDamage {
 public:
  OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid): playerid(playerid), issuerid(issuerid), amount(amount), weaponid(weaponid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), weaponid);
    amx_Push(s->amx(), amx_ftoc(amount));
    amx_Push(s->amx(), issuerid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerTakeDamage", true);
    return ret;
  }
 private:
  int playerid;
  int issuerid;
  float amount;
  int weaponid;
};

class OnPlayerGiveDamage {
 public:
  OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid): playerid(playerid), damagedid(damagedid), amount(amount), weaponid(weaponid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), weaponid);
    amx_Push(s->amx(), amx_ftoc(amount));
    amx_Push(s->amx(), damagedid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerGiveDamage", true);
    return ret;
  }
 private:
  int playerid;
  int damagedid;
  float amount;
  int weaponid;
};

class OnPlayerClickMap {
 public:
  OnPlayerClickMap(int playerid, float fX, float fY, float fZ): playerid(playerid), fX(fX), fY(fY), fZ(fZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fZ));
    amx_Push(s->amx(), amx_ftoc(fY));
    amx_Push(s->amx(), amx_ftoc(fX));
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerClickMap", true);
    return ret;
  }
 private:
  int playerid;
  float fX;
  float fY;
  float fZ;
};

class OnPlayerClickTextDraw {
 public:
  OnPlayerClickTextDraw(int playerid, int clickedid): playerid(playerid), clickedid(clickedid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), clickedid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerClickTextDraw", false);
    return ret;
  }
 private:
  int playerid;
  int clickedid;
};

class OnPlayerClickPlayerTextDraw {
 public:
  OnPlayerClickPlayerTextDraw(int playerid, int playertextid): playerid(playerid), playertextid(playertextid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playertextid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerClickPlayerTextDraw", false);
    return ret;
  }
 private:
  int playerid;
  int playertextid;
};

class OnPlayerClickPlayer {
 public:
  OnPlayerClickPlayer(int playerid, int clickedplayerid, int source): playerid(playerid), clickedplayerid(clickedplayerid), source(source) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), source);
    amx_Push(s->amx(), clickedplayerid);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerClickPlayer", true);
    return ret;
  }
 private:
  int playerid;
  int clickedplayerid;
  int source;
};

class OnPlayerEditObject {
 public:
  OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ): playerid(playerid), playerobject(playerobject), objectid(objectid), response(response), fX(fX), fY(fY), fZ(fZ), fRotX(fRotX), fRotY(fRotY), fRotZ(fRotZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fRotZ));
    amx_Push(s->amx(), amx_ftoc(fRotY));
    amx_Push(s->amx(), amx_ftoc(fRotX));
    amx_Push(s->amx(), amx_ftoc(fZ));
    amx_Push(s->amx(), amx_ftoc(fY));
    amx_Push(s->amx(), amx_ftoc(fX));
    amx_Push(s->amx(), response);
    amx_Push(s->amx(), objectid);
    amx_Push(s->amx(), playerobject);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerEditObject", true);
    return ret;
  }
 private:
  int playerid;
  bool playerobject;
  int objectid;
  int response;
  float fX;
  float fY;
  float fZ;
  float fRotX;
  float fRotY;
  float fRotZ;
};

class OnPlayerEditAttachedObject {
 public:
  OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ): playerid(playerid), response(response), index(index), modelid(modelid), boneid(boneid), fOffsetX(fOffsetX), fOffsetY(fOffsetY), fOffsetZ(fOffsetZ), fRotX(fRotX), fRotY(fRotY), fRotZ(fRotZ), fScaleX(fScaleX), fScaleY(fScaleY), fScaleZ(fScaleZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fScaleZ));
    amx_Push(s->amx(), amx_ftoc(fScaleY));
    amx_Push(s->amx(), amx_ftoc(fScaleX));
    amx_Push(s->amx(), amx_ftoc(fRotZ));
    amx_Push(s->amx(), amx_ftoc(fRotY));
    amx_Push(s->amx(), amx_ftoc(fRotX));
    amx_Push(s->amx(), amx_ftoc(fOffsetZ));
    amx_Push(s->amx(), amx_ftoc(fOffsetY));
    amx_Push(s->amx(), amx_ftoc(fOffsetX));
    amx_Push(s->amx(), boneid);
    amx_Push(s->amx(), modelid);
    amx_Push(s->amx(), index);
    amx_Push(s->amx(), response);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerEditAttachedObject", true);
    return ret;
  }
 private:
  int playerid;
  int response;
  int index;
  int modelid;
  int boneid;
  float fOffsetX;
  float fOffsetY;
  float fOffsetZ;
  float fRotX;
  float fRotY;
  float fRotZ;
  float fScaleX;
  float fScaleY;
  float fScaleZ;
};

class OnPlayerSelectObject {
 public:
  OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ): playerid(playerid), type(type), objectid(objectid), modelid(modelid), fX(fX), fY(fY), fZ(fZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fZ));
    amx_Push(s->amx(), amx_ftoc(fY));
    amx_Push(s->amx(), amx_ftoc(fX));
    amx_Push(s->amx(), modelid);
    amx_Push(s->amx(), objectid);
    amx_Push(s->amx(), type);
    amx_Push(s->amx(), playerid);
    bool ret = s->Exec("OnPlayerSelectObject", true);
    return ret;
  }
 private:
  int playerid;
  int type;
  int objectid;
  int modelid;
  float fX;
  float fY;
  float fZ;
};

} // namespace ufs

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnGameModeInit(), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit() {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnGameModeExit(), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerConnect(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerDisconnect(playerid, reason), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerSpawn(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerDeath(playerid, killerid, reason), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleSpawn(vehicleid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleDeath(vehicleid, killerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char * text) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerText(playerid, text), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerCommandText(playerid, cmdtext), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerRequestClass(playerid, classid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerEnterVehicle(playerid, vehicleid, ispassenger), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerExitVehicle(playerid, vehicleid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerStateChange(playerid, newstate, oldstate), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerEnterCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerLeaveCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerEnterRaceCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerLeaveRaceCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char * cmd) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnRconCommand(cmd), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerRequestSpawn(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnObjectMoved(objectid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerObjectMoved(playerid, objectid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerPickUpPickup(playerid, pickupid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleMod(playerid, vehicleid, componentid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnEnterExitModShop(playerid, enterexit, interiorid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehiclePaintjob(playerid, vehicleid, paintjobid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleRespray(playerid, vehicleid, color1, color2), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleDamageStatusUpdate(vehicleid, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerSelectedMenuRow(playerid, row), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerExitedMenu(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerKeyStateChange(playerid, newkeys, oldkeys), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char * ip, const char * password, bool success) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnRconLoginAttempt(ip, password, success), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerUpdate(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerStreamIn(playerid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerStreamOut(playerid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleStreamIn(vehicleid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnVehicleStreamOut(vehicleid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnDialogResponse(playerid, dialogid, response, listitem, inputtext), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerTakeDamage(playerid, issuerid, amount, weaponid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerGiveDamage(playerid, damagedid, amount, weaponid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerClickMap(playerid, fX, fY, fZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerClickTextDraw(playerid, clickedid), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerClickPlayerTextDraw(playerid, playertextid), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayer(int playerid, int clickedplayerid, int source) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerClickPlayer(playerid, clickedplayerid, source), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerEditObject(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ) {
  using namespace ufs;
  return UFS::Instance().ForEachScript(
    ufs::OnPlayerSelectObject(playerid, type, objectid, modelid, fX, fY, fZ), true);
}

