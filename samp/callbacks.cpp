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

#include "callbacks.h"
#include "wrapper.h"

#include "plugin/amx/amx.h"

namespace samp { 
namespace callbacks {

void InitializeCallbacks() {
    using samp::Wrapper;

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

cell OnPlayerConnect(AMX *amx) {
    return 0;
}

cell OnPlayerDisconnect(AMX *amx) {
    return 0;
}

cell OnPlayerSpawn(AMX *amx) {
    return 0;
}

cell OnPlayerDeath(AMX *amx) {
    return 0;
}

cell OnVehicleSpawn(AMX *amx) {
    return 0;
}

cell OnVehicleDeath(AMX *amx) {
    return 0;
}

cell OnPlayerText(AMX *amx) {
    return 0;
}

cell OnPlayerCommandText(AMX *amx) {
    return 0;
}

cell OnPlayerRequestClass(AMX *amx) {
    return 0;
}

cell OnPlayerEnterVehicle(AMX *amx) {
    return 0;
}

cell OnPlayerExitVehicle(AMX *amx) {
    return 0;
}

cell OnPlayerStateChange(AMX *amx) {
    return 0;
}

cell OnPlayerEnterCheckpoint(AMX *amx) {
    return 0;
}

cell OnPlayerLeaveCheckpoint(AMX *amx) {
    return 0;
}

cell OnPlayerEnterRaceCheckpoint(AMX *amx) {
    return 0;
}

cell OnPlayerLeaveRaceCheckpoint(AMX *amx) {
    return 0;
}

cell OnRconCommand(AMX *amx) {
    return 0;
}

cell OnPlayerRequestSpawn(AMX *amx) {
    return 0;
}

cell OnObjectMoved(AMX *amx) {
    return 0;
}

cell OnPlayerObjectMoved(AMX *amx) {
    return 0;
}

cell OnPlayerPickUpPickup(AMX *amx) {
    return 0;
}

cell OnVehicleMod(AMX *amx) {
    return 0;
}

cell OnEnterExitModShop(AMX *amx) {
    return 0;
}

cell OnVehiclePaintjob(AMX *amx) {
    return 0;
}

cell OnVehicleRespray(AMX *amx) {
    return 0;
}

cell OnVehicleDamageStatusUpdate(AMX *amx) {
    return 0;
}

cell OnPlayerSelectedMenuRow(AMX *amx) {
    return 0;
}

cell OnPlayerExitedMenu(AMX *amx) {
    return 0;
}

cell OnPlayerInteriorChange(AMX *amx) {
    return 0;
}

cell OnPlayerKeyStateChange(AMX *amx) {
    return 0;
}

cell OnRconLoginAttempt(AMX *amx) {
    return 0;
}

cell OnPlayerUpdate(AMX *amx) {
    return 0;
}

cell OnPlayerStreamIn(AMX *amx) {
    return 0;
}

cell OnPlayerStreamOut(AMX *amx) {
    return 0;
}

cell OnVehicleStreamIn(AMX *amx) {
    return 0;
}

cell OnVehicleStreamOut(AMX *amx) {
    return 0;
}

cell OnDialogResponse(AMX *amx) {
    return 0;
}

cell OnPlayerClickPlayer(AMX *amx) {
    return 0;
}

} // namespace callbacks 
} // namespace samp 