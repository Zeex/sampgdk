#include "script.h"
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
  OnPlayerConnect(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerConnect", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerDisconnect {
 public:
  OnPlayerDisconnect(int playerid, int reason): playerid_(playerid), reason_(reason) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), reason_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerDisconnect", true);
    return ret;
  }
 private:
  int playerid_;
  int reason_;
};

class OnPlayerSpawn {
 public:
  OnPlayerSpawn(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerSpawn", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerDeath {
 public:
  OnPlayerDeath(int playerid, int killerid, int reason): playerid_(playerid), killerid_(killerid), reason_(reason) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), reason_);
    amx_Push(s->amx(), killerid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerDeath", true);
    return ret;
  }
 private:
  int playerid_;
  int killerid_;
  int reason_;
};

class OnVehicleSpawn {
 public:
  OnVehicleSpawn(int vehicleid): vehicleid_(vehicleid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), vehicleid_);
    bool ret = s->Exec("OnVehicleSpawn", true);
    return ret;
  }
 private:
  int vehicleid_;
};

class OnVehicleDeath {
 public:
  OnVehicleDeath(int vehicleid, int killerid): vehicleid_(vehicleid), killerid_(killerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), killerid_);
    amx_Push(s->amx(), vehicleid_);
    bool ret = s->Exec("OnVehicleDeath", true);
    return ret;
  }
 private:
  int vehicleid_;
  int killerid_;
};

class OnPlayerText {
 public:
  OnPlayerText(int playerid, const char * text): playerid_(playerid), text_(text) {}
  bool operator()(Script *s) {
    cell text_addr;
    amx_PushString(s->amx(), &text_addr, 0, text_, 0, 0);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerText", true);
    amx_Release(s->amx(), text_addr);
    return ret;
  }
 private:
  int playerid_;
  const char * text_;
};

class OnPlayerCommandText {
 public:
  OnPlayerCommandText(int playerid, const char * cmdtext): playerid_(playerid), cmdtext_(cmdtext) {}
  bool operator()(Script *s) {
    cell cmdtext_addr;
    amx_PushString(s->amx(), &cmdtext_addr, 0, cmdtext_, 0, 0);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerCommandText", false);
    amx_Release(s->amx(), cmdtext_addr);
    return ret;
  }
 private:
  int playerid_;
  const char * cmdtext_;
};

class OnPlayerRequestClass {
 public:
  OnPlayerRequestClass(int playerid, int classid): playerid_(playerid), classid_(classid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), classid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerRequestClass", true);
    return ret;
  }
 private:
  int playerid_;
  int classid_;
};

class OnPlayerEnterVehicle {
 public:
  OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger): playerid_(playerid), vehicleid_(vehicleid), ispassenger_(ispassenger) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), ispassenger_);
    amx_Push(s->amx(), vehicleid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerEnterVehicle", true);
    return ret;
  }
 private:
  int playerid_;
  int vehicleid_;
  bool ispassenger_;
};

class OnPlayerExitVehicle {
 public:
  OnPlayerExitVehicle(int playerid, int vehicleid): playerid_(playerid), vehicleid_(vehicleid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), vehicleid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerExitVehicle", true);
    return ret;
  }
 private:
  int playerid_;
  int vehicleid_;
};

class OnPlayerStateChange {
 public:
  OnPlayerStateChange(int playerid, int newstate, int oldstate): playerid_(playerid), newstate_(newstate), oldstate_(oldstate) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), oldstate_);
    amx_Push(s->amx(), newstate_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerStateChange", true);
    return ret;
  }
 private:
  int playerid_;
  int newstate_;
  int oldstate_;
};

class OnPlayerEnterCheckpoint {
 public:
  OnPlayerEnterCheckpoint(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerEnterCheckpoint", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerLeaveCheckpoint {
 public:
  OnPlayerLeaveCheckpoint(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerLeaveCheckpoint", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerEnterRaceCheckpoint {
 public:
  OnPlayerEnterRaceCheckpoint(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerEnterRaceCheckpoint", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerLeaveRaceCheckpoint {
 public:
  OnPlayerLeaveRaceCheckpoint(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerLeaveRaceCheckpoint", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnRconCommand {
 public:
  OnRconCommand(const char * cmd): cmd_(cmd) {}
  bool operator()(Script *s) {
    cell cmd_addr;
    amx_PushString(s->amx(), &cmd_addr, 0, cmd_, 0, 0);
    bool ret = s->Exec("OnRconCommand", false);
    amx_Release(s->amx(), cmd_addr);
    return ret;
  }
 private:
  const char * cmd_;
};

class OnPlayerRequestSpawn {
 public:
  OnPlayerRequestSpawn(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerRequestSpawn", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnObjectMoved {
 public:
  OnObjectMoved(int objectid): objectid_(objectid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), objectid_);
    bool ret = s->Exec("OnObjectMoved", true);
    return ret;
  }
 private:
  int objectid_;
};

class OnPlayerObjectMoved {
 public:
  OnPlayerObjectMoved(int playerid, int objectid): playerid_(playerid), objectid_(objectid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), objectid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerObjectMoved", true);
    return ret;
  }
 private:
  int playerid_;
  int objectid_;
};

class OnPlayerPickUpPickup {
 public:
  OnPlayerPickUpPickup(int playerid, int pickupid): playerid_(playerid), pickupid_(pickupid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), pickupid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerPickUpPickup", true);
    return ret;
  }
 private:
  int playerid_;
  int pickupid_;
};

class OnVehicleMod {
 public:
  OnVehicleMod(int playerid, int vehicleid, int componentid): playerid_(playerid), vehicleid_(vehicleid), componentid_(componentid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), componentid_);
    amx_Push(s->amx(), vehicleid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnVehicleMod", true);
    return ret;
  }
 private:
  int playerid_;
  int vehicleid_;
  int componentid_;
};

class OnEnterExitModShop {
 public:
  OnEnterExitModShop(int playerid, int enterexit, int interiorid): playerid_(playerid), enterexit_(enterexit), interiorid_(interiorid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), interiorid_);
    amx_Push(s->amx(), enterexit_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnEnterExitModShop", true);
    return ret;
  }
 private:
  int playerid_;
  int enterexit_;
  int interiorid_;
};

class OnVehiclePaintjob {
 public:
  OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid): playerid_(playerid), vehicleid_(vehicleid), paintjobid_(paintjobid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), paintjobid_);
    amx_Push(s->amx(), vehicleid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnVehiclePaintjob", true);
    return ret;
  }
 private:
  int playerid_;
  int vehicleid_;
  int paintjobid_;
};

class OnVehicleRespray {
 public:
  OnVehicleRespray(int playerid, int vehicleid, int color1, int color2): playerid_(playerid), vehicleid_(vehicleid), color1_(color1), color2_(color2) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), color2_);
    amx_Push(s->amx(), color1_);
    amx_Push(s->amx(), vehicleid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnVehicleRespray", true);
    return ret;
  }
 private:
  int playerid_;
  int vehicleid_;
  int color1_;
  int color2_;
};

class OnVehicleDamageStatusUpdate {
 public:
  OnVehicleDamageStatusUpdate(int vehicleid, int playerid): vehicleid_(vehicleid), playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    amx_Push(s->amx(), vehicleid_);
    bool ret = s->Exec("OnVehicleDamageStatusUpdate", true);
    return ret;
  }
 private:
  int vehicleid_;
  int playerid_;
};

class OnUnoccupiedVehicleUpdate {
 public:
  OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z): vehicleid_(vehicleid), playerid_(playerid), passenger_seat_(passenger_seat), new_x_(new_x), new_y_(new_y), new_z_(new_z) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(new_z_));
    amx_Push(s->amx(), amx_ftoc(new_y_));
    amx_Push(s->amx(), amx_ftoc(new_x_));
    amx_Push(s->amx(), passenger_seat_);
    amx_Push(s->amx(), playerid_);
    amx_Push(s->amx(), vehicleid_);
    bool ret = s->Exec("OnUnoccupiedVehicleUpdate", true);
    return ret;
  }
 private:
  int vehicleid_;
  int playerid_;
  int passenger_seat_;
  float new_x_;
  float new_y_;
  float new_z_;
};

class OnPlayerSelectedMenuRow {
 public:
  OnPlayerSelectedMenuRow(int playerid, int row): playerid_(playerid), row_(row) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), row_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerSelectedMenuRow", true);
    return ret;
  }
 private:
  int playerid_;
  int row_;
};

class OnPlayerExitedMenu {
 public:
  OnPlayerExitedMenu(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerExitedMenu", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerInteriorChange {
 public:
  OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid): playerid_(playerid), newinteriorid_(newinteriorid), oldinteriorid_(oldinteriorid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), oldinteriorid_);
    amx_Push(s->amx(), newinteriorid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerInteriorChange", true);
    return ret;
  }
 private:
  int playerid_;
  int newinteriorid_;
  int oldinteriorid_;
};

class OnPlayerKeyStateChange {
 public:
  OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys): playerid_(playerid), newkeys_(newkeys), oldkeys_(oldkeys) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), oldkeys_);
    amx_Push(s->amx(), newkeys_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerKeyStateChange", true);
    return ret;
  }
 private:
  int playerid_;
  int newkeys_;
  int oldkeys_;
};

class OnRconLoginAttempt {
 public:
  OnRconLoginAttempt(const char * ip, const char * password, bool success): ip_(ip), password_(password), success_(success) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), success_);
    cell password_addr;
    amx_PushString(s->amx(), &password_addr, 0, password_, 0, 0);
    cell ip_addr;
    amx_PushString(s->amx(), &ip_addr, 0, ip_, 0, 0);
    bool ret = s->Exec("OnRconLoginAttempt", true);
    amx_Release(s->amx(), ip_addr);
    amx_Release(s->amx(), password_addr);
    return ret;
  }
 private:
  const char * ip_;
  const char * password_;
  bool success_;
};

class OnPlayerUpdate {
 public:
  OnPlayerUpdate(int playerid): playerid_(playerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerUpdate", true);
    return ret;
  }
 private:
  int playerid_;
};

class OnPlayerStreamIn {
 public:
  OnPlayerStreamIn(int playerid, int forplayerid): playerid_(playerid), forplayerid_(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerStreamIn", true);
    return ret;
  }
 private:
  int playerid_;
  int forplayerid_;
};

class OnPlayerStreamOut {
 public:
  OnPlayerStreamOut(int playerid, int forplayerid): playerid_(playerid), forplayerid_(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerStreamOut", true);
    return ret;
  }
 private:
  int playerid_;
  int forplayerid_;
};

class OnVehicleStreamIn {
 public:
  OnVehicleStreamIn(int vehicleid, int forplayerid): vehicleid_(vehicleid), forplayerid_(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid_);
    amx_Push(s->amx(), vehicleid_);
    bool ret = s->Exec("OnVehicleStreamIn", true);
    return ret;
  }
 private:
  int vehicleid_;
  int forplayerid_;
};

class OnVehicleStreamOut {
 public:
  OnVehicleStreamOut(int vehicleid, int forplayerid): vehicleid_(vehicleid), forplayerid_(forplayerid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), forplayerid_);
    amx_Push(s->amx(), vehicleid_);
    bool ret = s->Exec("OnVehicleStreamOut", true);
    return ret;
  }
 private:
  int vehicleid_;
  int forplayerid_;
};

class OnDialogResponse {
 public:
  OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext): playerid_(playerid), dialogid_(dialogid), response_(response), listitem_(listitem), inputtext_(inputtext) {}
  bool operator()(Script *s) {
    cell inputtext_addr;
    amx_PushString(s->amx(), &inputtext_addr, 0, inputtext_, 0, 0);
    amx_Push(s->amx(), listitem_);
    amx_Push(s->amx(), response_);
    amx_Push(s->amx(), dialogid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnDialogResponse", false);
    amx_Release(s->amx(), inputtext_addr);
    return ret;
  }
 private:
  int playerid_;
  int dialogid_;
  int response_;
  int listitem_;
  const char * inputtext_;
};

class OnPlayerTakeDamage {
 public:
  OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart): playerid_(playerid), issuerid_(issuerid), amount_(amount), weaponid_(weaponid), bodypart_(bodypart) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), bodypart_);
    amx_Push(s->amx(), weaponid_);
    amx_Push(s->amx(), amx_ftoc(amount_));
    amx_Push(s->amx(), issuerid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerTakeDamage", true);
    return ret;
  }
 private:
  int playerid_;
  int issuerid_;
  float amount_;
  int weaponid_;
  int bodypart_;
};

class OnPlayerGiveDamage {
 public:
  OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart): playerid_(playerid), damagedid_(damagedid), amount_(amount), weaponid_(weaponid), bodypart_(bodypart) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), bodypart_);
    amx_Push(s->amx(), weaponid_);
    amx_Push(s->amx(), amx_ftoc(amount_));
    amx_Push(s->amx(), damagedid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerGiveDamage", true);
    return ret;
  }
 private:
  int playerid_;
  int damagedid_;
  float amount_;
  int weaponid_;
  int bodypart_;
};

class OnPlayerClickMap {
 public:
  OnPlayerClickMap(int playerid, float fX, float fY, float fZ): playerid_(playerid), fX_(fX), fY_(fY), fZ_(fZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fZ_));
    amx_Push(s->amx(), amx_ftoc(fY_));
    amx_Push(s->amx(), amx_ftoc(fX_));
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerClickMap", true);
    return ret;
  }
 private:
  int playerid_;
  float fX_;
  float fY_;
  float fZ_;
};

class OnPlayerClickTextDraw {
 public:
  OnPlayerClickTextDraw(int playerid, int clickedid): playerid_(playerid), clickedid_(clickedid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), clickedid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerClickTextDraw", false);
    return ret;
  }
 private:
  int playerid_;
  int clickedid_;
};

class OnPlayerClickPlayerTextDraw {
 public:
  OnPlayerClickPlayerTextDraw(int playerid, int playertextid): playerid_(playerid), playertextid_(playertextid) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), playertextid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerClickPlayerTextDraw", false);
    return ret;
  }
 private:
  int playerid_;
  int playertextid_;
};

class OnIncomingConnection {
 public:
  OnIncomingConnection(int playerid, const char * ip_address, int port): playerid_(playerid), ip_address_(ip_address), port_(port) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), port_);
    cell ip_address_addr;
    amx_PushString(s->amx(), &ip_address_addr, 0, ip_address_, 0, 0);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnIncomingConnection", true);
    amx_Release(s->amx(), ip_address_addr);
    return ret;
  }
 private:
  int playerid_;
  const char * ip_address_;
  int port_;
};

class OnPlayerClickPlayer {
 public:
  OnPlayerClickPlayer(int playerid, int clickedplayerid, int source): playerid_(playerid), clickedplayerid_(clickedplayerid), source_(source) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), source_);
    amx_Push(s->amx(), clickedplayerid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerClickPlayer", true);
    return ret;
  }
 private:
  int playerid_;
  int clickedplayerid_;
  int source_;
};

class OnPlayerEditObject {
 public:
  OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ): playerid_(playerid), playerobject_(playerobject), objectid_(objectid), response_(response), fX_(fX), fY_(fY), fZ_(fZ), fRotX_(fRotX), fRotY_(fRotY), fRotZ_(fRotZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fRotZ_));
    amx_Push(s->amx(), amx_ftoc(fRotY_));
    amx_Push(s->amx(), amx_ftoc(fRotX_));
    amx_Push(s->amx(), amx_ftoc(fZ_));
    amx_Push(s->amx(), amx_ftoc(fY_));
    amx_Push(s->amx(), amx_ftoc(fX_));
    amx_Push(s->amx(), response_);
    amx_Push(s->amx(), objectid_);
    amx_Push(s->amx(), playerobject_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerEditObject", true);
    return ret;
  }
 private:
  int playerid_;
  bool playerobject_;
  int objectid_;
  int response_;
  float fX_;
  float fY_;
  float fZ_;
  float fRotX_;
  float fRotY_;
  float fRotZ_;
};

class OnPlayerEditAttachedObject {
 public:
  OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ): playerid_(playerid), response_(response), index_(index), modelid_(modelid), boneid_(boneid), fOffsetX_(fOffsetX), fOffsetY_(fOffsetY), fOffsetZ_(fOffsetZ), fRotX_(fRotX), fRotY_(fRotY), fRotZ_(fRotZ), fScaleX_(fScaleX), fScaleY_(fScaleY), fScaleZ_(fScaleZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fScaleZ_));
    amx_Push(s->amx(), amx_ftoc(fScaleY_));
    amx_Push(s->amx(), amx_ftoc(fScaleX_));
    amx_Push(s->amx(), amx_ftoc(fRotZ_));
    amx_Push(s->amx(), amx_ftoc(fRotY_));
    amx_Push(s->amx(), amx_ftoc(fRotX_));
    amx_Push(s->amx(), amx_ftoc(fOffsetZ_));
    amx_Push(s->amx(), amx_ftoc(fOffsetY_));
    amx_Push(s->amx(), amx_ftoc(fOffsetX_));
    amx_Push(s->amx(), boneid_);
    amx_Push(s->amx(), modelid_);
    amx_Push(s->amx(), index_);
    amx_Push(s->amx(), response_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerEditAttachedObject", true);
    return ret;
  }
 private:
  int playerid_;
  int response_;
  int index_;
  int modelid_;
  int boneid_;
  float fOffsetX_;
  float fOffsetY_;
  float fOffsetZ_;
  float fRotX_;
  float fRotY_;
  float fRotZ_;
  float fScaleX_;
  float fScaleY_;
  float fScaleZ_;
};

class OnPlayerSelectObject {
 public:
  OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ): playerid_(playerid), type_(type), objectid_(objectid), modelid_(modelid), fX_(fX), fY_(fY), fZ_(fZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fZ_));
    amx_Push(s->amx(), amx_ftoc(fY_));
    amx_Push(s->amx(), amx_ftoc(fX_));
    amx_Push(s->amx(), modelid_);
    amx_Push(s->amx(), objectid_);
    amx_Push(s->amx(), type_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerSelectObject", true);
    return ret;
  }
 private:
  int playerid_;
  int type_;
  int objectid_;
  int modelid_;
  float fX_;
  float fY_;
  float fZ_;
};

class OnPlayerWeaponShot {
 public:
  OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ): playerid_(playerid), weaponid_(weaponid), hittype_(hittype), hitid_(hitid), fX_(fX), fY_(fY), fZ_(fZ) {}
  bool operator()(Script *s) {
    amx_Push(s->amx(), amx_ftoc(fZ_));
    amx_Push(s->amx(), amx_ftoc(fY_));
    amx_Push(s->amx(), amx_ftoc(fX_));
    amx_Push(s->amx(), hitid_);
    amx_Push(s->amx(), hittype_);
    amx_Push(s->amx(), weaponid_);
    amx_Push(s->amx(), playerid_);
    bool ret = s->Exec("OnPlayerWeaponShot", true);
    return ret;
  }
 private:
  int playerid_;
  int weaponid_;
  int hittype_;
  int hitid_;
  float fX_;
  float fY_;
  float fZ_;
};

} // namespace ufs

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  return ufs::UFS::Instance().ForEachScript(ufs::OnGameModeInit(), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit() {
  return ufs::UFS::Instance().ForEachScript(ufs::OnGameModeExit(), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerConnect(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerDisconnect(playerid, reason), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerSpawn(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerDeath(playerid, killerid, reason), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleSpawn(vehicleid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleDeath(vehicleid, killerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char * text) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerText(playerid, text), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerCommandText(playerid, cmdtext), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerRequestClass(playerid, classid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerEnterVehicle(playerid, vehicleid, ispassenger), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerExitVehicle(playerid, vehicleid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerStateChange(playerid, newstate, oldstate), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerEnterCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerLeaveCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerEnterRaceCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerLeaveRaceCheckpoint(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char * cmd) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnRconCommand(cmd), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerRequestSpawn(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnObjectMoved(objectid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerObjectMoved(playerid, objectid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerPickUpPickup(playerid, pickupid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleMod(playerid, vehicleid, componentid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnEnterExitModShop(playerid, enterexit, interiorid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehiclePaintjob(playerid, vehicleid, paintjobid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleRespray(playerid, vehicleid, color1, color2), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleDamageStatusUpdate(vehicleid, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, new_x, new_y, new_z), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerSelectedMenuRow(playerid, row), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerExitedMenu(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerKeyStateChange(playerid, newkeys, oldkeys), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char * ip, const char * password, bool success) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnRconLoginAttempt(ip, password, success), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerUpdate(playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerStreamIn(playerid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerStreamOut(playerid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleStreamIn(vehicleid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnVehicleStreamOut(vehicleid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnDialogResponse(playerid, dialogid, response, listitem, inputtext), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerGiveDamage(playerid, damagedid, amount, weaponid, bodypart), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerClickMap(playerid, fX, fY, fZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerClickTextDraw(playerid, clickedid), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerClickPlayerTextDraw(playerid, playertextid), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnIncomingConnection(int playerid, const char * ip_address, int port) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnIncomingConnection(playerid, ip_address, port), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayer(int playerid, int clickedplayerid, int source) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerClickPlayer(playerid, clickedplayerid, source), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerEditObject(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerSelectObject(playerid, type, objectid, modelid, fX, fY, fZ), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ) {
  return ufs::UFS::Instance().ForEachScript(ufs::OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ), true);
}

