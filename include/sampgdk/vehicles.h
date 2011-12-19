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

#ifndef SAMPGDK_VEHICLES_H
#define SAMPGDK_VEHICLES_H

#include <sampgdk/config.h>

namespace sampgdk {

const int CARMODTYPE_SPOILER = 0;
const int CARMODTYPE_HOOD = 1;
const int CARMODTYPE_ROOF = 2;
const int CARMODTYPE_SIDESKIRT = 3;
const int CARMODTYPE_LAMPS = 4;
const int CARMODTYPE_NITRO = 5;
const int CARMODTYPE_EXHAUST = 6;
const int CARMODTYPE_WHEELS = 7;
const int CARMODTYPE_STEREO = 8;
const int CARMODTYPE_HYDRAULICS = 9;
const int CARMODTYPE_FRONT_BUMPER = 10;
const int CARMODTYPE_REAR_BUMPER = 11;
const int CARMODTYPE_VENT_RIGHT = 12;
const int CARMODTYPE_VENT_LEFT = 13;

const int VEHICLE_PARAMS_UNSET = -1;
const int VEHICLE_PARAMS_OFF = 0;
const int VEHICLE_PARAMS_ON = 1;

// Vehicle
float GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z);
int CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, long respawn_delay);
bool DestroyVehicle(int vehicleid);
bool IsVehicleStreamedIn(int vehicleid, int forplayerid);
bool GetVehiclePos(int vehicleid, float &x, float &y, float &z);
bool SetVehiclePos(int vehicleid, float x, float y, float z);
bool GetVehicleZAngle(int vehicleid, float &z_angle);
bool GetVehicleRotationQuat(int vehicleid, float &w, float &x, float &y, float &z);
bool SetVehicleZAngle(int vehicleid, float z_angle);
bool SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked);
void ManualVehicleEngineAndLights();
bool SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective);
bool GetVehicleParamsEx(int vehicleid, bool &engine, bool &lights, bool &alarm, bool &doors, bool &bonnet, bool &boot, bool &objective);
bool SetVehicleToRespawn(int vehicleid);
bool LinkVehicleToInterior(int vehicleid, int interiorid);
bool AddVehicleComponent(int vehicleid, int componentid);
bool RemoveVehicleComponent(int vehicleid, int componentid);
bool ChangeVehicleColor(int vehicleid, int color1, int color2);
bool ChangeVehiclePaintjob(int vehicleid, int paintjobid);
bool SetVehicleHealth(int vehicleid, float health);
bool GetVehicleHealth(int vehicleid, float &health);
void AttachTrailerToVehicle(int trailerid, int vehicleid);
void DetachTrailerFromVehicle(int vehicleid);
bool IsTrailerAttachedToVehicle(int vehicleid);
int GetVehicleTrailer(int vehicleid);
bool SetVehicleNumberPlate(int vehicleid, const char *numberplate);
int GetVehicleModel(int vehicleid);
int GetVehicleComponentInSlot(int vehicleid, int slot); // There is 1 slot for each CARMODTYPE_*
int GetVehicleComponentType(int component); // Find CARMODTYPE_* for component id
bool RepairVehicle(int vehicleid); // Repairs the damage model and resets the health
bool GetVehicleVelocity(int vehicleid, float &X, float &Y, float &Z);
bool SetVehicleVelocity(int vehicleid, float X, float Y, float Z);
bool SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z);
bool GetVehicleDamageStatus(int vehicleid, long &panels, long &doors, long &lights, long &tires);
bool UpdateVehicleDamageStatus(int vehicleid, long panels, long doors, long lights, long tires);

// Virtual Worlds
bool SetVehicleVirtualWorld(int vehicleid, int worldid);
bool GetVehicleVirtualWorld(int vehicleid);

} // namespace sampgdk

#endif

