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

#include "callbacks.h"
#include "eventhandler.h"
#include "wrapper.h"

#include "plugin/amx/amx.h"

// Gets a single cell from AMX stack with the specified index
static cell GetCellFromStack(AMX *amx, int index) {
    auto hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
    auto data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
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

    Wrapper::GetInstance()->SetPublicHandler("OnGameModeInit", OnGameModeInit);
    Wrapper::GetInstance()->SetPublicHandler("OnGameModeExit", OnGameModeExit);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerConnect", OnPlayerConnect);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerDisconnect", OnPlayerDisconnect);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerSpawn", OnPlayerSpawn);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerDeath", OnPlayerDeath);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleSpawn", OnVehicleSpawn);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleDeath", OnVehicleDeath);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerText", OnPlayerText);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerCommandText", OnPlayerCommandText);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerRequestClass", OnPlayerRequestClass);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerEnterVehicle", OnPlayerEnterVehicle);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerExitVehicle", OnPlayerExitVehicle);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerStateChange", OnPlayerStateChange);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerEnterCheckpoint", OnPlayerEnterCheckpoint);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerLeaveCheckpoint", OnPlayerLeaveCheckpoint);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerEnterRaceCheckpoint", OnPlayerEnterRaceCheckpoint);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerLeaveRaceCheckpoint", OnPlayerLeaveRaceCheckpoint);
    Wrapper::GetInstance()->SetPublicHandler("OnRconCommand", OnRconCommand);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerRequestSpawn", OnPlayerRequestSpawn);
    Wrapper::GetInstance()->SetPublicHandler("OnObjectMoved", OnObjectMoved);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerObjectMoved", OnPlayerObjectMoved);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerPickUpPickup", OnPlayerPickUpPickup);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleMod", OnVehicleMod);
    Wrapper::GetInstance()->SetPublicHandler("OnEnterExitModShop", OnEnterExitModShop);
    Wrapper::GetInstance()->SetPublicHandler("OnVehiclePaintjob", OnVehiclePaintjob);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleRespray", OnVehicleRespray);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleDamageStatusUpdate", OnVehicleDamageStatusUpdate);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerSelectedMenuRow", OnPlayerSelectedMenuRow);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerExitedMenu", OnPlayerExitedMenu);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerInteriorChange", OnPlayerInteriorChange);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerKeyStateChange", OnPlayerKeyStateChange);
    Wrapper::GetInstance()->SetPublicHandler("OnRconLoginAttempt", OnRconLoginAttempt);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerUpdate", OnPlayerUpdate);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerStreamIn", OnPlayerStreamIn);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerStreamOut", OnPlayerStreamOut);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleStreamIn", OnVehicleStreamIn);
    Wrapper::GetInstance()->SetPublicHandler("OnVehicleStreamOut", OnVehicleStreamOut);
    Wrapper::GetInstance()->SetPublicHandler("OnDialogResponse", OnDialogResponse);
    Wrapper::GetInstance()->SetPublicHandler("OnPlayerClickPlayer", OnPlayerClickPlayer);
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
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerConnect(playerid);
}

cell OnPlayerDisconnect(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto reason = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerDisconnect(playerid, reason);
}

cell OnPlayerSpawn(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerSpawn(playerid);
}

cell OnPlayerDeath(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto killerid = GetCellFromStack(amx, 1);
    auto reason = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerDeath(playerid, killerid, reason);
}

cell OnVehicleSpawn(AMX *amx) {
    auto vehicleid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnVehicleSpawn(vehicleid);
}

cell OnVehicleDeath(AMX *amx) {
    auto vehicleid = GetCellFromStack(amx, 0);
    auto killerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleDeath(vehicleid, killerid);
}

cell OnPlayerText(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto text = GetStringFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerText(playerid, text);
}

cell OnPlayerCommandText(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto cmdtext = GetStringFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerCommandText(playerid, cmdtext);
}

cell OnPlayerRequestClass(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto classid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerRequestClass(playerid, classid);
}

cell OnPlayerEnterVehicle(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto vehicleid = GetCellFromStack(amx, 1);
    auto ispassenger = GetCellFromStack(amx, 2) != 0;
    return EventHandler::GetEventHandler()->OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
}

cell OnPlayerExitVehicle(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto vehicleid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerExitVehicle(playerid, vehicleid);
}

cell OnPlayerStateChange(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto newstate = GetCellFromStack(amx, 1);
    auto oldstate = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerStateChange(playerid, newstate, oldstate);
}

cell OnPlayerEnterCheckpoint(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerEnterCheckpoint(playerid);
}

cell OnPlayerLeaveCheckpoint(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerLeaveCheckpoint(playerid);
}

cell OnPlayerEnterRaceCheckpoint(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerEnterRaceCheckpoint(playerid);
}

cell OnPlayerLeaveRaceCheckpoint(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerLeaveRaceCheckpoint(playerid);
}

cell OnRconCommand(AMX *amx) {
    auto cmd = GetStringFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnRconCommand(cmd);
}

cell OnPlayerRequestSpawn(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerRequestSpawn(playerid);
}

cell OnObjectMoved(AMX *amx) {
    auto objectid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnObjectMoved(objectid);
}

cell OnPlayerObjectMoved(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto objectid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerObjectMoved(playerid, objectid);
}

cell OnPlayerPickUpPickup(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto pickupid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerPickUpPickup(playerid, pickupid);
}

cell OnVehicleMod(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto vehicleid = GetCellFromStack(amx, 1);
    auto componentid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnVehicleMod(playerid, vehicleid, componentid);
}

cell OnEnterExitModShop(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto enterexit = GetCellFromStack(amx, 1) != 0;
    auto interiorid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnEnterExitModShop(playerid, enterexit, interiorid);
}

cell OnVehiclePaintjob(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto vehicleid = GetCellFromStack(amx, 1);
    auto paintjobid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnVehiclePaintjob(playerid, vehicleid, paintjobid);
}

cell OnVehicleRespray(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto vehicleid = GetCellFromStack(amx, 1);
    auto color1 = GetCellFromStack(amx, 2);
    auto color2 = GetCellFromStack(amx, 3);
    return EventHandler::GetEventHandler()->OnVehicleRespray(playerid, vehicleid, color1, color2);
}

cell OnVehicleDamageStatusUpdate(AMX *amx) {
    auto vehicleid = GetCellFromStack(amx, 0);
    auto playerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleDamageStatusUpdate(vehicleid, playerid);
}

cell OnPlayerSelectedMenuRow(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto row = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerSelectedMenuRow(playerid, row);
}

cell OnPlayerExitedMenu(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerExitedMenu(playerid);
}

cell OnPlayerInteriorChange(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto newinteriorid = GetCellFromStack(amx, 1);
    auto oldinteriorid = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
}

cell OnPlayerKeyStateChange(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto newkeys = GetCellFromStack(amx, 1);
    auto oldkeys = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
}

cell OnRconLoginAttempt(AMX *amx) {
    auto ip = GetStringFromStack(amx, 0);
    auto password = GetStringFromStack(amx, 1);
    auto success = GetCellFromStack(amx, 2) != 0;
    return EventHandler::GetEventHandler()->OnRconLoginAttempt(ip, password, success);
}

cell OnPlayerUpdate(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    return EventHandler::GetEventHandler()->OnPlayerUpdate(playerid);
}

cell OnPlayerStreamIn(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerStreamIn(playerid, forplayerid);
}

cell OnPlayerStreamOut(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnPlayerStreamOut(playerid, forplayerid);
}

cell OnVehicleStreamIn(AMX *amx) {
    auto vehicleid = GetCellFromStack(amx, 0);
    auto forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleStreamIn(vehicleid, forplayerid);
}

cell OnVehicleStreamOut(AMX *amx) {
    auto vehicleid = GetCellFromStack(amx, 0);
    auto forplayerid = GetCellFromStack(amx, 1);
    return EventHandler::GetEventHandler()->OnVehicleStreamOut(vehicleid, forplayerid);
}

cell OnDialogResponse(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto dialogid = GetCellFromStack(amx, 1);
    auto response = GetCellFromStack(amx, 2) != 0;
    auto listitem = GetCellFromStack(amx, 3);
    auto inputtext = GetStringFromStack(amx, 4);
    return EventHandler::GetEventHandler()->OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
}

cell OnPlayerClickPlayer(AMX *amx) {
    auto playerid = GetCellFromStack(amx, 0);
    auto clickedplayerid = GetCellFromStack(amx, 1);
    auto source = GetCellFromStack(amx, 2);
    return EventHandler::GetEventHandler()->OnPlayerClickPlayer(playerid, clickedplayerid, source);
}

} // namespace callbacks 
} // namespace samp 