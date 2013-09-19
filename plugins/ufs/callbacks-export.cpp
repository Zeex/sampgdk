#include "ufs.h"
#include "callbacks.h"

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  return ufs::UFS::Instance().ForEachScript(
    &ufs::callbacks::OnGameModeInit, true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit() {
  return ufs::UFS::Instance().ForEachScript(
    &ufs::callbacks::OnGameModeExit, true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerConnect, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerDisconnect, playerid, reason), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerSpawn, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerDeath, playerid, killerid, reason), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleSpawn, vehicleid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleDeath, vehicleid, killerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char text[]) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerText, playerid, text), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char cmdtext[]) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerCommandText, playerid, cmdtext), false);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerRequestClass, playerid, classid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, int ispassenger) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerEnterVehicle, playerid, vehicleid, ispassenger), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerExitVehicle, playerid, vehicleid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerStateChange, playerid, newstate, oldstate), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerEnterCheckpoint, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerLeaveCheckpoint, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerEnterRaceCheckpoint, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerLeaveRaceCheckpoint, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char cmd[]) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnRconCommand, cmd), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerRequestSpawn, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnObjectMoved, objectid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerObjectMoved, playerid, objectid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerPickUpPickup, playerid, pickupid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleMod, playerid, vehicleid, componentid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnEnterExitModShop, playerid, enterexit, interiorid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehiclePaintjob, playerid, vehicleid, paintjobid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleRespray, playerid, vehicleid, color1, color2), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleDamageStatusUpdate, vehicleid, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnUnoccupiedVehicleUpdate, vehicleid, playerid, passenger_seat), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerSelectedMenuRow, playerid, row), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerExitedMenu, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerInteriorChange, playerid, newinteriorid, oldinteriorid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerKeyStateChange, playerid, newkeys, oldkeys), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char ip[], const char password[], int success) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnRconLoginAttempt, ip, password, success), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerUpdate, playerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerStreamIn, playerid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerStreamOut, playerid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleStreamIn, vehicleid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnVehicleStreamOut, vehicleid, forplayerid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char inputtext[]) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnDialogResponse, playerid, dialogid, response, listitem, inputtext), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerTakeDamage, playerid, issuerid, amount, weaponid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerGiveDamage, playerid, damagedid, amount, weaponid), true);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ) {
  return ufs::UFS::Instance().ForEachScript(
    ufs::MakeCallback(&ufs::callbacks::OnPlayerClickMap, playerid, fX, fY, fZ), true);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}
