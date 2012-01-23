/* Copyright (c) 2011 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_VEHICLES_H
#define SAMPGDK_VEHICLES_H

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#define CARMODTYPE_SPOILER      (0)
#define CARMODTYPE_HOOD         (1)
#define CARMODTYPE_ROOF         (2)
#define CARMODTYPE_SIDESKIRT    (3)
#define CARMODTYPE_LAMPS        (4)
#define CARMODTYPE_NITRO        (5)
#define CARMODTYPE_EXHAUST      (6)
#define CARMODTYPE_WHEELS       (7)
#define CARMODTYPE_STEREO       (8)
#define CARMODTYPE_HYDRAULICS   (9)
#define CARMODTYPE_FRONT_BUMPER (10)
#define CARMODTYPE_REAR_BUMPER  (11)
#define CARMODTYPE_VENT_RIGHT   (12)
#define CARMODTYPE_VENT_LEFT    (13)

#define VEHICLE_PARAMS_UNSET  (-1)
#define VEHICLE_PARAMS_OFF    (0)
#define VEHICLE_PARAMS_ON     (1)

SAMPGDK_EXPORT float SAMPGDK_CALL GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z);
SAMPGDK_EXPORT int SAMPGDK_CALL CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay);
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyVehicle(int vehicleid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsVehicleStreamedIn(int vehicleid, int forplayerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehiclePos(int vehicleid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehiclePos(int vehicleid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleZAngle(int vehicleid, float *z_angle);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleRotationQuat(int vehicleid, float *w, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleZAngle(int vehicleid, float z_angle);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked);
SAMPGDK_EXPORT void SAMPGDK_CALL ManualVehicleEngineAndLights();
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleParamsEx(int vehicleid, int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleParamsEx(int vehicleid, int *engine, int *lights, int *alarm, int *doors, int *bonnet, int *boot, int *objective);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleToRespawn(int vehicleid);
SAMPGDK_EXPORT bool SAMPGDK_CALL LinkVehicleToInterior(int vehicleid, int interiorid);
SAMPGDK_EXPORT bool SAMPGDK_CALL AddVehicleComponent(int vehicleid, int componentid);
SAMPGDK_EXPORT bool SAMPGDK_CALL RemoveVehicleComponent(int vehicleid, int componentid);
SAMPGDK_EXPORT bool SAMPGDK_CALL ChangeVehicleColor(int vehicleid, int color1, int color2);
SAMPGDK_EXPORT bool SAMPGDK_CALL ChangeVehiclePaintjob(int vehicleid, int paintjobid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleHealth(int vehicleid, float health);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleHealth(int vehicleid, float *health);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachTrailerToVehicle(int trailerid, int vehicleid);
SAMPGDK_EXPORT void SAMPGDK_CALL DetachTrailerFromVehicle(int vehicleid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsTrailerAttachedToVehicle(int vehicleid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleTrailer(int vehicleid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleNumberPlate(int vehicleid, const char *numberplate);
SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleModel(int vehicleid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleComponentInSlot(int vehicleid, int slot);
SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleComponentType(int component); 
SAMPGDK_EXPORT bool SAMPGDK_CALL RepairVehicle(int vehicleid); 
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleVelocity(int vehicleid, float *X, float *Y, float *Z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleVelocity(int vehicleid, float X, float Y, float Z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleDamageStatus(int vehicleid, int *panels, int *doors, int *lights, int *tires);
SAMPGDK_EXPORT bool SAMPGDK_CALL UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires);

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleVirtualWorld(int vehicleid, int worldid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleVirtualWorld(int vehicleid);

#endif /* !SAMPGDK_VEHICLES_H */
