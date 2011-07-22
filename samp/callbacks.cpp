// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

#if defined WIN32 || defined _WIN32
    #include <malloc.h>
#endif

#include "callbacks.h"
#include "eventhandler.h"
#include "wrapper.h"

#include "plugin/amx/amx.h"

// Gets a single cell from AMX stack with the specified index
static cell GetCellFromStack(AMX *amx, int index) {
    AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
    unsigned char *data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
    return *reinterpret_cast<cell*>(data + amx->stk + sizeof(cell)*index);
}

// Gets a string from AMX stack
static std::string GetStringFromStack(AMX *amx, int index) {
    cell amxAddr = GetCellFromStack(amx, index);
    char *str;
    amx_StrParam(amx, amxAddr, str);
    return std::string(str);
}

namespace samp {
namespace callbacks {

void InitializeCallbacks() {
    using samp::Wrapper;

    Wrapper::GetInstance()->SetPublicHook("OnGameModeInit", PublicHook(OnGameModeInit, 0));
    Wrapper::GetInstance()->SetPublicHook("OnGameModeExit", PublicHook(OnGameModeExit, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerConnect", PublicHook(OnPlayerConnect, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerDisconnect", PublicHook(OnPlayerDisconnect, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerSpawn", PublicHook(OnPlayerSpawn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerDeath", PublicHook(OnPlayerDeath, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleSpawn", PublicHook(OnVehicleSpawn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleDeath", PublicHook(OnVehicleDeath, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerText", PublicHook(OnPlayerText, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerCommandText", PublicHook(OnPlayerCommandText, 1));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerRequestClass", PublicHook(OnPlayerRequestClass, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerEnterVehicle", PublicHook(OnPlayerEnterVehicle, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerExitVehicle", PublicHook(OnPlayerExitVehicle, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerStateChange", PublicHook(OnPlayerStateChange, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerEnterCheckpoint", PublicHook(OnPlayerEnterCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerLeaveCheckpoint", PublicHook(OnPlayerLeaveCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerEnterRaceCheckpoint", PublicHook(OnPlayerEnterRaceCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerLeaveRaceCheckpoint", PublicHook(OnPlayerLeaveRaceCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnRconCommand", PublicHook(OnRconCommand, 1));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerRequestSpawn", PublicHook(OnPlayerRequestSpawn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnObjectMoved", PublicHook(OnObjectMoved, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerObjectMoved", PublicHook(OnPlayerObjectMoved, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerPickUpPickup", PublicHook(OnPlayerPickUpPickup, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleMod", PublicHook(OnVehicleMod, 0));
    Wrapper::GetInstance()->SetPublicHook("OnEnterExitModShop", PublicHook(OnEnterExitModShop, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehiclePaintjob", PublicHook(OnVehiclePaintjob, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleRespray", PublicHook(OnVehicleRespray, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleDamageStatusUpdate", PublicHook(OnVehicleDamageStatusUpdate, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerSelectedMenuRow", PublicHook(OnPlayerSelectedMenuRow, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerExitedMenu", PublicHook(OnPlayerExitedMenu, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerInteriorChange", PublicHook(OnPlayerInteriorChange, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerKeyStateChange", PublicHook(OnPlayerKeyStateChange, 0));
    Wrapper::GetInstance()->SetPublicHook("OnRconLoginAttempt", PublicHook(OnRconLoginAttempt, 1)); // TODO: the 1 is just a guess, need a test
    Wrapper::GetInstance()->SetPublicHook("OnPlayerUpdate", PublicHook(OnPlayerUpdate, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerStreamIn", PublicHook(OnPlayerStreamIn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerStreamOut", PublicHook(OnPlayerStreamOut, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleStreamIn", PublicHook(OnVehicleStreamIn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleStreamOut", PublicHook(OnVehicleStreamOut, 0));
    Wrapper::GetInstance()->SetPublicHook("OnDialogResponse", PublicHook(OnDialogResponse, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerClickPlayer", PublicHook(OnPlayerClickPlayer, 0));
}

cell OnGameModeInit(AMX *amx) {
    EventHandler::GetEventHandler()->OnGameModeInit();
    return 1;
}

cell OnGameModeExit(AMX *amx) {
    EventHandler::GetEventHandler()->OnGameModeExit();
    return 1;
}

cell OnPlayerConnect(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerConnect(playerid);
}

cell OnPlayerDisconnect(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int reason = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerDisconnect(playerid, reason);
}

cell OnPlayerSpawn(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerSpawn(playerid);
}

cell OnPlayerDeath(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int killerid = GetCellFromStack(amx, 1);
    int reason = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerDeath(playerid, killerid, reason);
}

cell OnVehicleSpawn(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnVehicleSpawn(vehicleid);
}

cell OnVehicleDeath(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int killerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleDeath(vehicleid, killerid);
}

cell OnPlayerText(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    std::string text = GetStringFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerText(playerid, text);
}

cell OnPlayerCommandText(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    std::string cmdtext = GetStringFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerCommandText(playerid, cmdtext);
}

cell OnPlayerRequestClass(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int classid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerRequestClass(playerid, classid);
}

cell OnPlayerEnterVehicle(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    bool ispassenger = GetCellFromStack(amx, 2) != 0;
    return EventHandler::GetEventHandler()->OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
}

cell OnPlayerExitVehicle(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerExitVehicle(playerid, vehicleid);
}

cell OnPlayerStateChange(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int newstate = GetCellFromStack(amx, 1);
    int oldstate = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerStateChange(playerid, newstate, oldstate);
}

cell OnPlayerEnterCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerEnterCheckpoint(playerid);
}

cell OnPlayerLeaveCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerLeaveCheckpoint(playerid);
}

cell OnPlayerEnterRaceCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerEnterRaceCheckpoint(playerid);
}

cell OnPlayerLeaveRaceCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerLeaveRaceCheckpoint(playerid);
}

cell OnRconCommand(AMX *amx) {
    std::string cmd = GetStringFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnRconCommand(cmd);
}

cell OnPlayerRequestSpawn(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerRequestSpawn(playerid);
}

cell OnObjectMoved(AMX *amx) {
    int objectid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnObjectMoved(objectid);
}

cell OnPlayerObjectMoved(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int objectid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerObjectMoved(playerid, objectid);
}

cell OnPlayerPickUpPickup(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int pickupid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerPickUpPickup(playerid, pickupid);
}

cell OnVehicleMod(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int componentid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnVehicleMod(playerid, vehicleid, componentid);
}

cell OnEnterExitModShop(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    bool enterexit = GetCellFromStack(amx, 1) != 0;
    int interiorid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnEnterExitModShop(playerid, enterexit, interiorid);
}

cell OnVehiclePaintjob(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int paintjobid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnVehiclePaintjob(playerid, vehicleid, paintjobid);
}

cell OnVehicleRespray(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int color1 = GetCellFromStack(amx, 2);
    int color2 = GetCellFromStack(amx, 3);
    return EventHandler::GetEventHandler()->OnVehicleRespray(playerid, vehicleid, color1, color2);
}

cell OnVehicleDamageStatusUpdate(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int playerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleDamageStatusUpdate(vehicleid, playerid);
}

cell OnPlayerSelectedMenuRow(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int row = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerSelectedMenuRow(playerid, row);
}

cell OnPlayerExitedMenu(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerExitedMenu(playerid);
}

cell OnPlayerInteriorChange(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int newinteriorid = GetCellFromStack(amx, 1);
    int oldinteriorid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
}

cell OnPlayerKeyStateChange(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int newkeys = GetCellFromStack(amx, 1);
    int oldkeys = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
}

cell OnRconLoginAttempt(AMX *amx) {
    std::string ip = GetStringFromStack(amx, 0);
    std::string password = GetStringFromStack(amx, 1);
    bool success = GetCellFromStack(amx, 2) != 0;
    return EventHandler::GetEventHandler()->OnRconLoginAttempt(ip, password, success);
}

cell OnPlayerUpdate(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerUpdate(playerid);
}

cell OnPlayerStreamIn(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerStreamIn(playerid, forplayerid);
}

cell OnPlayerStreamOut(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerStreamOut(playerid, forplayerid);
}

cell OnVehicleStreamIn(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleStreamIn(vehicleid, forplayerid);
}

cell OnVehicleStreamOut(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleStreamOut(vehicleid, forplayerid);
}

cell OnDialogResponse(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int dialogid = GetCellFromStack(amx, 1);
    bool response = GetCellFromStack(amx, 2) != 0;
    int listitem = GetCellFromStack(amx, 3);
    std::string inputtext = GetStringFromStack(amx, 4);
    return EventHandler::GetEventHandler()->OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
}

cell OnPlayerClickPlayer(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int clickedplayerid = GetCellFromStack(amx, 1);
    int source = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerClickPlayer(playerid, clickedplayerid, source);
}

} // namespace callbacks
} // namespace samp

