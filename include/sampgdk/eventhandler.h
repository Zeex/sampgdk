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

#ifndef SAMPGDK_EVENTHANDLER_H
#define SAMPGDK_EVENTHANDLER_H

#include <sampgdk/export.h>

namespace sampgdk {

class SAMPGDK_EXPORT EventHandler {
public:
    EventHandler();
    virtual ~EventHandler();

    void Register();
    void Unregister();

    bool IsRegistered() const;

    static EventHandler *GetFirstEventHandler();
    EventHandler *GetNext() const;

    virtual void OnGameModeInit();
    virtual void OnGameModeExit();
    virtual bool OnPlayerConnect(int playerid);
    virtual bool OnPlayerDisconnect(int playerid, int reason);
    virtual bool OnPlayerSpawn(int playerid);
    virtual bool OnPlayerDeath(int playerid, int killerid, int reason);
    virtual bool OnVehicleSpawn(int vehicleid);
    virtual bool OnVehicleDeath(int vehicleid, int killerid);
    virtual bool OnPlayerText(int playerid, const char *text);
    virtual bool OnPlayerCommandText(int playerid, const char *cmdtext);
    virtual bool OnPlayerRequestClass(int playerid, int classid);
    virtual bool OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger);
    virtual bool OnPlayerExitVehicle(int playerid, int vehicleid);
    virtual bool OnPlayerStateChange(int playerid, int newstate, int oldstate);
    virtual bool OnPlayerEnterCheckpoint(int playerid);
    virtual bool OnPlayerLeaveCheckpoint(int playerid);
    virtual bool OnPlayerEnterRaceCheckpoint(int playerid);
    virtual bool OnPlayerLeaveRaceCheckpoint(int playerid);
    virtual bool OnRconCommand(const char *cmd);
    virtual bool OnPlayerRequestSpawn(int playerid);
    virtual bool OnObjectMoved(int objectid);
    virtual bool OnPlayerObjectMoved(int playerid, int objectid);
    virtual bool OnPlayerPickUpPickup(int playerid, int pickupid);
    virtual bool OnVehicleMod(int playerid, int vehicleid, int componentid);
    virtual bool OnEnterExitModShop(int playerid, bool enterexit, int interiorid);
    virtual bool OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid);
    virtual bool OnVehicleRespray(int playerid, int vehicleid, int color1, int color2);
    virtual bool OnVehicleDamageStatusUpdate(int vehicleid, int playerid);
    virtual bool OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat);
    virtual bool OnPlayerSelectedMenuRow(int playerid, int row);
    virtual bool OnPlayerExitedMenu(int playerid);
    virtual bool OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid);
    virtual bool OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys);
    virtual bool OnRconLoginAttempt(const char *ip, const char *password, bool success);
    virtual bool OnPlayerUpdate(int playerid);
    virtual bool OnPlayerStreamIn(int playerid, int forplayerid);
    virtual bool OnPlayerStreamOut(int playerid, int forplayerid);
    virtual bool OnVehicleStreamIn(int vehicleid, int forplayerid);
    virtual bool OnVehicleStreamOut(int vehicleid, int forplayerid);
    virtual bool OnDialogResponse(int playerid, int dialogid, bool response, int listitem, const char *inputtext);
    virtual bool OnPlayerClickPlayer(int playerid, int clickedplayerid, int source);
	virtual bool OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid);

private:
    bool registered_;
    EventHandler *next_;
    EventHandler *prev_;
};

} // namespace sampgdk

#endif

