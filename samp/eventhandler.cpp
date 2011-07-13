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

#include "eventhandler.h"
#include "logprintf.h"

#ifdef DEBUG_CALLBACKS
    #define dlogprintf logprintf
#else
    #define dlogprintf (void)
#endif

namespace samp { 

static std::shared_ptr<EventHandler> theDefaultEventHandler(new EventHandler);

std::shared_ptr<EventHandler> EventHandler::currentHandler_ = theDefaultEventHandler;

void EventHandler::SetEventHandler(std::shared_ptr<EventHandler> handler) {
    if (handler == 0) {
        EventHandler::currentHandler_ = theDefaultEventHandler;
    } else {
        EventHandler::currentHandler_ = handler;
    }
}

std::shared_ptr<EventHandler> EventHandler::GetEventHandler() {
    return EventHandler::currentHandler_;
}

void EventHandler::OnGameModeInit() { 
    dlogprintf("OnGameModeInit()");
}

void EventHandler::OnGameModeExit() { 
    dlogprintf("OnGameModeExit()");
}

bool EventHandler::OnPlayerConnect(int playerid) { 
    dlogprintf("OnPlayerConnect(%d)", playerid);
    return true; 
}

bool EventHandler::OnPlayerDisconnect(int playerid, int reason) { 
    dlogprintf("OnPlayerDisconnect(%d, %d)", playerid, reason);
    return true; 
}

bool EventHandler::OnPlayerSpawn(int playerid) {
    dlogprintf("OnPlayerSpawn(%d)", playerid);
    return true;
}

bool EventHandler::OnPlayerDeath(int playerid, int killerid, int reason) {
    dlogprintf("OnPlayerDeath(%d, %d, %d)", playerid, killerid, reason);
    return true;
}

bool EventHandler::OnVehicleSpawn(int vehicleid) {
    dlogprintf("OnVehicleSpawn(%d)", vehicleid);
    return true;
}

bool EventHandler::OnVehicleDeath(int vehicleid, int killerid) {
    dlogprintf("OnVehicleDeath(%d, %d)", vehicleid, killerid);
    return true;
}

bool EventHandler::OnPlayerText(int playerid, const std::string &text) {
    dlogprintf("OnPlayerText(%d, %s)", playerid, text.c_str());
    return true;
}

bool EventHandler::OnPlayerCommandText(int playerid, const std::string &cmdtext) {
    dlogprintf("OnPlayerCommandText(%d, %s)", playerid, cmdtext.c_str());
    return false;
}

bool EventHandler::OnPlayerRequestClass(int playerid, int classid) {
    dlogprintf("OnPlayerRequestClass(%d, %d)", playerid, classid);
    return true;
}

bool EventHandler::OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger) {
    dlogprintf("OnPlayerEnterVehicle(%d, %d, %d)", playerid, vehicleid, ispassenger);
    return true;
}

bool EventHandler::OnPlayerExitVehicle(int playerid, int vehicleid) {
    dlogprintf("OnPlayerExitVehicle(%d, %d)", playerid, vehicleid);
    return true;
}

bool EventHandler::OnPlayerStateChange(int playerid, int newstate, int oldstate) {
    dlogprintf("OnPlayerStateChange(%d, %d, %d)", playerid, newstate, oldstate);
    return true;
}

bool EventHandler::OnPlayerEnterCheckpoint(int playerid) {
    dlogprintf("OnPlayerEnterCheckpoint(%d)", playerid);
    return true;
}

bool EventHandler::OnPlayerLeaveCheckpoint(int playerid) {
    dlogprintf("OnPlayerLeaveCheckpoint(%d)", playerid);
    return true;
}

bool EventHandler::OnPlayerEnterRaceCheckpoint(int playerid) {
    dlogprintf("OnPlayerEnterRaceCheckpoint(%d)", playerid);
    return true;
}

bool EventHandler::OnPlayerLeaveRaceCheckpoint(int playerid) {
    dlogprintf("OnPlayerLeaveRaceCheckpoint(%d)", playerid);
    return true;
}

bool EventHandler::OnRconCommand(const std::string &cmd) {
    dlogprintf("OnRconCommand(%s)", cmd.c_str());
    return false;
}

bool EventHandler::OnPlayerRequestSpawn(int playerid) {
    dlogprintf("OnPlayerRequestSpawn(%d)", playerid);
    return true;
}

bool EventHandler::OnObjectMoved(int objectid) {
    dlogprintf("OnObjectMoved(%d)", objectid);
    return true;
}

bool EventHandler::OnPlayerObjectMoved(int playerid, int objectid) {
    dlogprintf("OnPlayerObjectMoved(%d, %d)", playerid, objectid);
    return true;
}

bool EventHandler::OnPlayerPickUpPickup(int playerid, int pickupid) {
    dlogprintf("OnPlayerPickUpPickup(%d, %d)", playerid, pickupid);
    return true;
}

bool EventHandler::OnVehicleMod(int playerid, int vehicleid, int componentid) {
    dlogprintf("OnVehicleMod(%d, %d, %d)", playerid, vehicleid, componentid);
    return true;
}

bool EventHandler::OnEnterExitModShop(int playerid, bool enterexit, int interiorid) {
    dlogprintf("OnEnterExitModShop(%d, %d, %d)", playerid, enterexit, interiorid);
    return true;
}

bool EventHandler::OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
    dlogprintf("OnVehiclePaintjob(%d, %d, %d)", playerid, vehicleid, paintjobid);
    return true;
}

bool EventHandler::OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
    dlogprintf("OnVehicleRespray(%d, %d, %d, %d)", playerid, vehicleid, color1, color2);
    return true;
}

bool EventHandler::OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
    dlogprintf("OnVehicleDamageStatusUpdate(%d, %d)", vehicleid, playerid);
    return true;
}

bool EventHandler::OnPlayerSelectedMenuRow(int playerid, int row) {
    dlogprintf("OnPlayerSelectedMenuRow(%d, %d)", playerid, row);
    return true;
}

bool EventHandler::OnPlayerExitedMenu(int playerid) {
    dlogprintf("OnPlayerExitedMenu(%d)", playerid);
    return true;
}

bool EventHandler::OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
    dlogprintf("OnPlayerInteriorChange(%d, %d, %d)", playerid, newinteriorid, oldinteriorid);
    return true;
}

bool EventHandler::OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
    dlogprintf("OnPlayerKeyStateChange(%d, %d, %d)", playerid, newkeys, oldkeys);
    return true;
}

bool EventHandler::OnRconLoginAttempt(const std::string &ip, const std::string &password, bool success) {
    dlogprintf("OnRconLoginAttempt(%s, %s, %d)", ip.c_str(), password.c_str(), success);
    return true;
}

bool EventHandler::OnPlayerUpdate(int playerid) {
    dlogprintf("OnPlayerUpdate(%d)", playerid);
    return true;
}

bool EventHandler::OnPlayerStreamIn(int playerid, int forplayerid) {
    dlogprintf("OnPlayerStreamIn(%d, %d)", playerid, forplayerid);
    return true;
}

bool EventHandler::OnPlayerStreamOut(int playerid, int forplayerid) {
    dlogprintf("OnPlayerStreamOut(%d, %d)", playerid, forplayerid);
    return true;
}

bool EventHandler::OnVehicleStreamIn(int vehicleid, int forplayerid) {
    dlogprintf("OnVehicleStreamIn(%d, %d)", vehicleid, forplayerid);
    return true;
}

bool EventHandler::OnVehicleStreamOut(int vehicleid, int forplayerid) {
    dlogprintf("OnVehicleStreamOut(%d, %d)", vehicleid, forplayerid);
    return true;
}

bool EventHandler::OnDialogResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext) {
    dlogprintf("OnDialogResponse(%d, %d, %d, %d, %s)", playerid, dialogid, response, listitem, inputtext.c_str());
    return true;
}

bool EventHandler::OnPlayerClickPlayer(int playerid, int clickedplayerid, int source) {
    dlogprintf("OnPlayerClickPlayer(%d, %d, %d)", playerid, clickedplayerid, source);
    return true;
}

} // namespace samp