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

#ifndef SAMP_EVENTHANDLER_H
#define SAMP_EVENTHANDLER_H

#include <string>

namespace samp { 

class EventHandler {
public:
    static void SetEventHandler(EventHandler handler);
    static EventHandler GetEventHandler();

    virtual bool OnPlayerConnect(int playerid);
    virtual bool OnPlayerDisconnect(int playerid, int reason);
    virtual bool OnPlayerSpawn(int playerid);
    virtual bool OnPlayerDeath(int playerid, int killerid, int reason);
    virtual bool OnVehicleSpawn(int vehicleid);
    virtual bool OnVehicleDeath(int vehicleid, int killerid);
    virtual bool OnPlayerText(int playerid, const std::string &text);
    virtual bool OnPlayerCommandText(int playerid, const std::string &cmdtext);
    virtual bool OnPlayerRequestClass(int playerid, int classid);
    virtual bool OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger);
    virtual bool OnPlayerExitVehicle(int playerid, int vehicleid);
    virtual bool OnPlayerStateChange(int playerid, int newstate, int oldstate);
    virtual bool OnPlayerEnterCheckpoint(int playerid);
    virtual bool OnPlayerLeaveCheckpoint(int playerid);
    virtual bool OnPlayerEnterRaceCheckpoint(int playerid);
    virtual bool OnPlayerLeaveRaceCheckpoint(int playerid);
    virtual bool OnRconCommand(const std::string &cmd);
    virtual bool OnPlayerRequestSpawn(int playerid);
    virtual bool OnObjectMoved(int objectid);
    virtual bool OnPlayerObjectMoved(int playerid, int objectid);
    virtual bool OnPlayerPickUpPickup(int playerid, int pickupid);
    virtual bool OnVehicleMod(int playerid, int vehicleid, int componentid);
    virtual bool OnEnterExitModShop(int playerid, bool enterexit, int interiorid);
    virtual bool OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid);
    virtual bool OnVehicleRespray(int playerid, int vehicleid, int color1, int color2);
    virtual bool OnVehicleDamageStatusUpdate(int vehicleid, int playerid);
    virtual bool OnPlayerSelectedMenuRow(int playerid, int row);
    virtual bool OnPlayerExitedMenu(int playerid);
    virtual bool OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid);
    virtual bool OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys);
    virtual bool OnRconLoginAttempt(const std::string &ip, const std::string &password, bool success);
    virtual bool OnPlayerUpdate(int playerid);
    virtual bool OnPlayerStreamIn(int playerid, int forplayerid);
    virtual bool OnPlayerStreamOut(int playerid, int forplayerid);
    virtual bool OnVehicleStreamIn(int vehicleid, int forplayerid);
    virtual bool OnVehicleStreamOut(int vehicleid, int forplayerid);
    virtual bool OnDialogResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
    virtual bool OnPlayerClickPlayer(int playerid, int clickedplayerid, int source);

private:
    static EventHandler currentHandler_;
};

} // namespace samp

#endif