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

namespace samp { 

EventHandler EventHandler::currentHandler_;

void EventHandler::SetEventHandler(EventHandler handler) {
    EventHandler::currentHandler_ = handler;
}

EventHandler EventHandler::GetEventHandler() {
    return EventHandler::currentHandler_;
}

bool OnPlayerConnect(int playerid) { 
    return true; 
}

bool OnPlayerDisconnect(int playerid, int reason) { 
    return true; 
}

bool OnPlayerSpawn(int playerid) {
    return true;
}

bool OnPlayerDeath(int playerid, int killerid, int reason) {
    return true;
}

bool OnVehicleSpawn(int vehicleid) {
    return true;
}

bool OnVehicleDeath(int vehicleid, int killerid) {
    return true;
}

bool OnPlayerText(int playerid, const std::string &text) {
    return true;
}

bool OnPlayerCommandText(int playerid, const std::string &cmdtext) {
    return false;
}

bool OnPlayerRequestClass(int playerid, int classid) {
    return true;
}

bool OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger) {
    return true;
}

bool OnPlayerExitVehicle(int playerid, int vehicleid) {
    return true;
}

bool OnPlayerStateChange(int playerid, int newstate, int oldstate) {
    return true;
}

bool OnPlayerEnterCheckpoint(int playerid) {
    return true;
}

bool OnPlayerLeaveCheckpoint(int playerid) {
    return true;
}

bool OnPlayerEnterRaceCheckpoint(int playerid) {
    return true;
}

bool OnPlayerLeaveRaceCheckpoint(int playerid) {
    return true;
}

bool OnRconCommand(const std::string &cmd) {
    return false;
}

bool OnPlayerRequestSpawn(int playerid) {
    return true;
}

bool OnObjectMoved(int objectid) {
    return true;
}

bool OnPlayerObjectMoved(int playerid, int objectid) {
    return true;
}

bool OnPlayerPickUpPickup(int playerid, int pickupid) {
    return true;
}

bool OnVehicleMod(int playerid, int vehicleid, int componentid) {
    return true;
}

bool OnEnterExitModShop(int playerid, bool enterexit, int interiorid) {
    return true;
}

bool OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) {
    return true;
}

bool OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) {
    return true;
}

bool OnVehicleDamageStatusUpdate(int vehicleid, int playerid) {
    return true;
}

bool OnPlayerSelectedMenuRow(int playerid, int row) {
    return true;
}

bool OnPlayerExitedMenu(int playerid) {
    return true;
}

bool OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid) {
    return true;
}

bool OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) {
    return true;
}

bool OnRconLoginAttempt(const std::string &ip, const std::string &password, bool success ) {
    return true;
}

bool OnPlayerUpdate(int playerid) {
    return true;
}

bool OnPlayerStreamIn(int playerid, int forplayerid) {
    return true;
}

bool OnPlayerStreamOut(int playerid, int forplayerid) {
    return true;
}

bool OnVehicleStreamIn(int vehicleid, int forplayerid) {
    return true;
}

bool OnVehicleStreamOut(int vehicleid, int forplayerid) {
    return true;
}

bool OnDialogResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext) {
    return true;
}

bool OnPlayerClickPlayer(int playerid, int clickedplayerid, int source) {
    return true;
}

} // namespace samp