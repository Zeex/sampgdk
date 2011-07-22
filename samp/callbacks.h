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

#ifndef SAMP_CALLBACKS_H
#define SAMP_CALLBACKS_H

#include "plugin/amx/amx.h"

namespace samp { 

class Callbacks {
public:
    static void Initialize();

private:
    static cell OnGameModeInit(AMX *amx);
    static cell OnGameModeExit(AMX *amx);
    static cell OnPlayerConnect(AMX *amx);
    static cell OnPlayerDisconnect(AMX *amx);
    static cell OnPlayerSpawn(AMX *amx);
    static cell OnPlayerDeath(AMX *amx);
    static cell OnVehicleSpawn(AMX *amx);
    static cell OnVehicleDeath(AMX *amx);
    static cell OnPlayerText(AMX *amx);
    static cell OnPlayerCommandText(AMX *amx);
    static cell OnPlayerRequestClass(AMX *amx);
    static cell OnPlayerEnterVehicle(AMX *amx);
    static cell OnPlayerExitVehicle(AMX *amx);
    static cell OnPlayerStateChange(AMX *amx);
    static cell OnPlayerEnterCheckpoint(AMX *amx);
    static cell OnPlayerLeaveCheckpoint(AMX *amx);
    static cell OnPlayerEnterRaceCheckpoint(AMX *amx);
    static cell OnPlayerLeaveRaceCheckpoint(AMX *amx);
    static cell OnRconCommand(AMX *amx);
    static cell OnPlayerRequestSpawn(AMX *amx);
    static cell OnObjectMoved(AMX *amx);
    static cell OnPlayerObjectMoved(AMX *amx);
    static cell OnPlayerPickUpPickup(AMX *amx);
    static cell OnVehicleMod(AMX *amx);
    static cell OnEnterExitModShop(AMX *amx);
    static cell OnVehiclePaintjob(AMX *amx);
    static cell OnVehicleRespray(AMX *amx);
    static cell OnVehicleDamageStatusUpdate(AMX *amx);
    static cell OnPlayerSelectedMenuRow(AMX *amx);
    static cell OnPlayerExitedMenu(AMX *amx);
    static cell OnPlayerInteriorChange(AMX *amx);
    static cell OnPlayerKeyStateChange(AMX *amx);
    static cell OnRconLoginAttempt(AMX *amx);
    static cell OnPlayerUpdate(AMX *amx);
    static cell OnPlayerStreamIn(AMX *amx);
    static cell OnPlayerStreamOut(AMX *amx);
    static cell OnVehicleStreamIn(AMX *amx);
    static cell OnVehicleStreamOut(AMX *amx);
    static cell OnDialogResponse(AMX *amx);
    static cell OnPlayerClickPlayer(AMX *amx);   
};

} // namespace samp 

#endif

