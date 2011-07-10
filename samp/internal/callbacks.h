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

#include "../plugin/amx/amx.h"

namespace samp { 
namespace internal { 
namespace callbacks {

cell OnGameModeInit(AMX *amx);
cell OnGameModeExit(AMX *amx);
cell OnPlayerConnect(AMX *amx);
cell OnPlayerDisconnect(AMX *amx);
cell OnPlayerSpawn(AMX *amx);
cell OnPlayerDeath(AMX *amx);
cell OnVehicleSpawn(AMX *amx);
cell OnVehicleDeath(AMX *amx);
cell OnPlayerText(AMX *amx);
cell OnPlayerCommandText(AMX *amx);
cell OnPlayerRequestClass(AMX *amx);
cell OnPlayerEnterVehicle(AMX *amx);
cell OnPlayerExitVehicle(AMX *amx);
cell OnPlayerStateChange(AMX *amx);
cell OnPlayerEnterCheckpoint(AMX *amx);
cell OnPlayerLeaveCheckpoint(AMX *amx);
cell OnPlayerEnterRaceCheckpoint(AMX *amx);
cell OnPlayerLeaveRaceCheckpoint(AMX *amx);
cell OnRconCommand(AMX *amx);
cell OnPlayerRequestSpawn(AMX *amx);
cell OnObjectMoved(AMX *amx);
cell OnPlayerObjectMoved(AMX *amx);
cell OnPlayerPickUpPickup(AMX *amx);
cell OnVehicleMod(AMX *amx);
cell OnEnterExitModShop(AMX *amx);
cell OnVehiclePaintjob(AMX *amx);
cell OnVehicleRespray(AMX *amx);
cell OnVehicleDamageStatusUpdate(AMX *amx);
cell OnPlayerSelectedMenuRow(AMX *amx);
cell OnPlayerExitedMenu(AMX *amx);
cell OnPlayerInteriorChange(AMX *amx);
cell OnPlayerKeyStateChange(AMX *amx);
cell OnRconLoginAttempt(AMX *amx);
cell OnPlayerUpdate(AMX *amx);
cell OnPlayerStreamIn(AMX *amx);
cell OnPlayerStreamOut(AMX *amx);
cell OnVehicleStreamIn(AMX *amx);
cell OnVehicleStreamOut(AMX *amx);
cell OnDialogResponse(AMX *amx);
cell OnPlayerClickPlayer(AMX *amx);
 
} // namespace callbacks 
} // namespace internal 
} // namespace samp 

#endif