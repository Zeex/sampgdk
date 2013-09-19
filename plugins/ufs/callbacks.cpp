#include <stack>
#include "rcon.h"
#include "script.h"

namespace {

class ExecContext {
 public:
  ExecContext(ufs::Script *s) : amx_(s->amx()) {}

  ~ExecContext() {
    while (!heap_args_.empty()) {
      amx_Release(amx_, heap_args_.top());
      heap_args_.pop();
    }
  }

  void PushCell(cell c) {
    amx_Push(amx_, c);
  }

  void PushFloat(float f) {
    amx_Push(amx_, amx_ftoc(f));
  }

  void PushString(const char *s) {
    cell amx_addr;
    amx_PushString(amx_, &amx_addr, 0, s, 0, 0);
    heap_args_.push(amx_addr);
  }

 private:
  AMX *amx_;
  std::stack<cell> heap_args_;
};

} // anonymous namespace

namespace ufs {
  namespace callbacks {

bool OnGameModeInit(Script *s) {
  return s->Exec("OnGameModeInit");
}

bool OnGameModeExit(Script *s) {
  return s->Exec("OnGameModeExit");
}

bool OnPlayerConnect(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerConnect");
}

bool OnPlayerDisconnect(Script *s, int playerid, int reason) {
  ExecContext ctx(s);
  ctx.PushCell(reason);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerDisconnect");
}

bool OnPlayerSpawn(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerSpawn");
}

bool OnPlayerDeath(Script *s, int playerid, int killerid, int reason) {
  ExecContext ctx(s);
  ctx.PushCell(reason);
  ctx.PushCell(killerid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerDeath");
}

bool OnVehicleSpawn(Script *s, int vehicleid) {
  ExecContext ctx(s);
  ctx.PushCell(vehicleid);
  return s->Exec("OnVehicleSpawn");
}

bool OnVehicleDeath(Script *s, int vehicleid, int killerid) {
  ExecContext ctx(s);
  ctx.PushCell(killerid);
  ctx.PushCell(vehicleid);
  return s->Exec("OnVehicleDeath");
}

bool OnPlayerText(Script *s, int playerid, const char text[]) {
  ExecContext ctx(s);
  ctx.PushString(text);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerText");
}

bool OnPlayerCommandText(Script *s, int playerid, const char cmdtext[]) {
  ExecContext ctx(s);
  ctx.PushString(cmdtext);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerCommandText", false);
}

bool OnPlayerRequestClass(Script *s, int playerid, int classid) {
  ExecContext ctx(s);
  ctx.PushCell(classid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerRequestClass");
}

bool OnPlayerEnterVehicle(Script *s, int playerid, int vehicleid, int ispassenger) {
  ExecContext ctx(s);
  ctx.PushCell(ispassenger);
  ctx.PushCell(vehicleid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerEnterVehicle");
}

bool OnPlayerExitVehicle(Script *s, int playerid, int vehicleid) {
  ExecContext ctx(s);
  ctx.PushCell(vehicleid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerExitVehicle");
}

bool OnPlayerStateChange(Script *s, int playerid, int newstate, int oldstate) {
  ExecContext ctx(s);
  ctx.PushCell(oldstate);
  ctx.PushCell(newstate);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerStateChange");
}

bool OnPlayerEnterCheckpoint(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerEnterCheckpoint");
}

bool OnPlayerLeaveCheckpoint(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerLeaveCheckpoint");
}

bool OnPlayerEnterRaceCheckpoint(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerEnterRaceCheckpoint");
}

bool OnPlayerLeaveRaceCheckpoint(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerLeaveRaceCheckpoint");
}

bool OnRconCommand(Script *s, const char cmd[]) {
  ProcessRconCommand(cmd);
  ExecContext ctx(s);
  ctx.PushString(cmd);
  return s->Exec("OnRconCommand");
}

bool OnPlayerRequestSpawn(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerRequestSpawn");
}

bool OnObjectMoved(Script *s, int objectid) {
  ExecContext ctx(s);
  ctx.PushCell(objectid);
  return s->Exec("OnObjectMoved");
}

bool OnPlayerObjectMoved(Script *s, int playerid, int objectid) {
  ExecContext ctx(s);
  ctx.PushCell(objectid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerObjectMoved");
}

bool OnPlayerPickUpPickup(Script *s, int playerid, int pickupid) {
  ExecContext ctx(s);
  ctx.PushCell(pickupid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerPickUpPickup");
}

bool OnVehicleMod(Script *s, int playerid, int vehicleid, int componentid) {
  ExecContext ctx(s);
  ctx.PushCell(componentid);
  ctx.PushCell(vehicleid);
  ctx.PushCell(playerid);
  return s->Exec("OnVehicleMod");
}

bool OnEnterExitModShop(Script *s, int playerid, int enterexit, int interiorid) {
  ExecContext ctx(s);
  ctx.PushCell(interiorid);
  ctx.PushCell(enterexit);
  ctx.PushCell(playerid);
  return s->Exec("OnEnterExitModShop");
}

bool OnVehiclePaintjob(Script *s, int playerid, int vehicleid, int paintjobid) {
  ExecContext ctx(s);
  ctx.PushCell(paintjobid);
  ctx.PushCell(vehicleid);
  ctx.PushCell(playerid);
  return s->Exec("OnVehiclePaintjob");
}

bool OnVehicleRespray(Script *s, int playerid, int vehicleid, int color1, int color2) {
  ExecContext ctx(s);
  ctx.PushCell(color2);
  ctx.PushCell(color1);
  ctx.PushCell(vehicleid);
  ctx.PushCell(playerid);
  return s->Exec("OnVehicleRespray");
}

bool OnVehicleDamageStatusUpdate(Script *s, int vehicleid, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  ctx.PushCell(vehicleid);
  return s->Exec("OnVehicleDamageStatusUpdate");
}

bool OnUnoccupiedVehicleUpdate(Script *s, int vehicleid, int playerid, int passenger_seat) {
  ExecContext ctx(s);
  ctx.PushCell(passenger_seat);
  ctx.PushCell(playerid);
  ctx.PushCell(vehicleid);
  return s->Exec("OnUnoccupiedVehicleUpdate");
}

bool OnPlayerSelectedMenuRow(Script *s, int playerid, int row) {
  ExecContext ctx(s);
  ctx.PushCell(row);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerSelectedMenuRow");
}

bool OnPlayerExitedMenu(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerExitedMenu");
}

bool OnPlayerInteriorChange(Script *s, int playerid, int newinteriorid, int oldinteriorid) {
  ExecContext ctx(s);
  ctx.PushCell(oldinteriorid);
  ctx.PushCell(newinteriorid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerInteriorChange");
}

bool OnPlayerKeyStateChange(Script *s, int playerid, int newkeys, int oldkeys) {
  ExecContext ctx(s);
  ctx.PushCell(oldkeys);
  ctx.PushCell(newkeys);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerKeyStateChange");
}

bool OnRconLoginAttempt(Script *s, const char ip[], const char password[], int success) {
  ExecContext ctx(s);
  ctx.PushCell(success);
  ctx.PushString(password);
  ctx.PushString(ip);
  return s->Exec("OnRconLoginAttempt");
}

bool OnPlayerUpdate(Script *s, int playerid) {
  ExecContext ctx(s);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerUpdate");
}

bool OnPlayerStreamIn(Script *s, int playerid, int forplayerid) {
  ExecContext ctx(s);
  ctx.PushCell(forplayerid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerStreamIn");
}

bool OnPlayerStreamOut(Script *s, int playerid, int forplayerid) {
  ExecContext ctx(s);
  ctx.PushCell(forplayerid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerStreamOut");
}

bool OnVehicleStreamIn(Script *s, int vehicleid, int forplayerid) {
  ExecContext ctx(s);
  ctx.PushCell(forplayerid);
  ctx.PushCell(vehicleid);
  return s->Exec("OnVehicleStreamIn");
}

bool OnVehicleStreamOut(Script *s, int vehicleid, int forplayerid) {
  ExecContext ctx(s);
  ctx.PushCell(forplayerid);
  ctx.PushCell(vehicleid);
  return s->Exec("OnVehicleStreamOut");
}

bool OnDialogResponse(Script *s, int playerid, int dialogid, int response, int listitem, const char inputtext[]) {
  ExecContext ctx(s);
  ctx.PushString(inputtext);
  ctx.PushCell(listitem);
  ctx.PushCell(response);
  ctx.PushCell(dialogid);
  ctx.PushCell(playerid);
  return s->Exec("OnDialogResponse");
}

bool OnPlayerTakeDamage(Script *s, int playerid, int issuerid, float amount, int weaponid) {
  ExecContext ctx(s);
  ctx.PushCell(weaponid);
  ctx.PushFloat(amount);
  ctx.PushCell(issuerid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerTakeDamage");
}

bool OnPlayerGiveDamage(Script *s, int playerid, int damagedid, float amount, int weaponid) {
  ExecContext ctx(s);
  ctx.PushCell(weaponid);
  ctx.PushFloat(amount);
  ctx.PushCell(damagedid);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerGiveDamage");
}

bool OnPlayerClickMap(Script *s, int playerid, float fX, float fY, float fZ) {
  ExecContext ctx(s);
  ctx.PushFloat(fZ);
  ctx.PushFloat(fY);
  ctx.PushFloat(fX);
  ctx.PushCell(playerid);
  return s->Exec("OnPlayerClickMap");
}

} // namespace callbacks
} // namespace ufs
