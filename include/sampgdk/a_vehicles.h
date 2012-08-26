/* Copyright (C) 2011-2012 Zeex
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

#ifndef SAMPGDK_A_VEHICLES_H
#define SAMPGDK_A_VEHICLES_H

#include <sampgdk/a_samp.h>
#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/generated/a_vehicles-defs.h>

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

SAMPGDK_NATIVE(float, GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z));
SAMPGDK_NATIVE(int, CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay));
SAMPGDK_NATIVE(bool, DestroyVehicle(int vehicleid));
SAMPGDK_NATIVE(bool, IsVehicleStreamedIn(int vehicleid, int forplayerid));
SAMPGDK_NATIVE(bool, GetVehiclePos(int vehicleid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, SetVehiclePos(int vehicleid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetVehicleZAngle(int vehicleid, float *z_angle));
SAMPGDK_NATIVE(bool, GetVehicleRotationQuat(int vehicleid, float *w, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, SetVehicleZAngle(int vehicleid, float z_angle));
SAMPGDK_NATIVE(bool, SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked));
SAMPGDK_NATIVE(bool, ManualVehicleEngineAndLights());
SAMPGDK_NATIVE(bool, SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective));
SAMPGDK_NATIVE(bool, GetVehicleParamsEx(int vehicleid, bool *engine, bool *lights, bool *alarm, bool *doors, bool *bonnet, bool *boot, bool *objective));
SAMPGDK_NATIVE(bool, SetVehicleToRespawn(int vehicleid));
SAMPGDK_NATIVE(bool, LinkVehicleToInterior(int vehicleid, int interiorid));
SAMPGDK_NATIVE(bool, AddVehicleComponent(int vehicleid, int componentid));
SAMPGDK_NATIVE(bool, RemoveVehicleComponent(int vehicleid, int componentid));
SAMPGDK_NATIVE(bool, ChangeVehicleColor(int vehicleid, int color1, int color2));
SAMPGDK_NATIVE(bool, ChangeVehiclePaintjob(int vehicleid, int paintjobid));
SAMPGDK_NATIVE(bool, SetVehicleHealth(int vehicleid, float health));
SAMPGDK_NATIVE(bool, GetVehicleHealth(int vehicleid, float *health));
SAMPGDK_NATIVE(bool, AttachTrailerToVehicle(int trailerid, int vehicleid));
SAMPGDK_NATIVE(bool, DetachTrailerFromVehicle(int vehicleid));
SAMPGDK_NATIVE(bool, IsTrailerAttachedToVehicle(int vehicleid));
SAMPGDK_NATIVE(int, GetVehicleTrailer(int vehicleid));
SAMPGDK_NATIVE(bool, SetVehicleNumberPlate(int vehicleid, const char *numberplate));
SAMPGDK_NATIVE(int, GetVehicleModel(int vehicleid));
SAMPGDK_NATIVE(int, GetVehicleComponentInSlot(int vehicleid, int slot));
SAMPGDK_NATIVE(int, GetVehicleComponentType(int component));
SAMPGDK_NATIVE(bool, RepairVehicle(int vehicleid));
SAMPGDK_NATIVE(bool, GetVehicleVelocity(int vehicleid, float *X, float *Y, float *Z));
SAMPGDK_NATIVE(bool, SetVehicleVelocity(int vehicleid, float X, float Y, float Z));
SAMPGDK_NATIVE(bool, SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z));
SAMPGDK_NATIVE(bool, GetVehicleDamageStatus(int vehicleid, int *panels, int *doors, int *lights, int *tires));
SAMPGDK_NATIVE(bool, UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires));
SAMPGDK_NATIVE(bool, SetVehicleVirtualWorld(int vehicleid, int worldid));
SAMPGDK_NATIVE(int, GetVehicleVirtualWorld(int vehicleid));

#define VEHICLE_MODEL_INFO_SIZE              1
#define VEHICLE_MODEL_INFO_FRONTSEAT         2
#define VEHICLE_MODEL_INFO_REARSEAT          3
#define VEHICLE_MODEL_INFO_PETROLCAP         4
#define VEHICLE_MODEL_INFO_WHEELSFRONT       5
#define VEHICLE_MODEL_INFO_WHEELSREAR        6
#define VEHICLE_MODEL_INFO_WHEELSMID         7
#define VEHICLE_MODEL_INFO_FRONT_BUMPER_Z    8
#define VEHICLE_MODEL_INFO_REAR_BUMPER_Z     9

SAMPGDK_NATIVE(bool, GetVehicleModelInfo(int model, int infotype, float *X, float *Y, float *Z));

#ifdef __cplusplus

#include <cassert>
#include <cmath>
#include <string>

class Vehicle {
public:
	// Construct from a vehicle ID
	Vehicle(int vehicleid) : id_(vehicleid) { assert(id_ != INVALID_VEHICLE_ID); }
	virtual ~Vehicle() {}

	// Implicit convertion to 'int'
	operator int() const { return id_; }

	// Explicit ID request
	int GetId() const { return id_; }

	// Sort of factory method
	static Vehicle Create(int type, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay) {
		return ::CreateVehicle(type, x, y, z, rotation, color1, color2, respawn_delay);
	}

	float GetDistanceFromPoint(float x, float y, float z) const
		{ return ::GetVehicleDistanceFromPoint(id_, x, y, z); }
	bool Destroy() const 
		{ return ::DestroyVehicle(id_); }
	bool IsStreamedInFor(int playerid) const
		{ return ::IsVehicleStreamedIn(id_, playerid); }
	bool GetPos(float *x, float *y, float *z) const
		{ return ::GetVehiclePos(id_, x, y, z); }
	bool GetPos(float &x, float &y, float &z) const
		{ return ::GetVehiclePos(id_, &x, &y, &z); }
	bool SetPos(float x, float y, float z) const
		{ return ::SetVehiclePos(id_, x, y, z); }
	bool GetZAngle(float *z_angle) const
		{ return ::GetVehicleZAngle(id_, z_angle); }
	bool GetZAngle(float &z_angle) const
		{ return ::GetVehicleZAngle(id_, &z_angle); }
	float GetZAngle() const { 
		float z_angle;
		::GetVehicleZAngle(id_, &z_angle); 
		return z_angle;
	}
	bool GetRotationQuat(float *w, float *x, float *y, float *z) const
		{ return ::GetVehicleRotationQuat(id_, w, x, y, z); }
	bool SetVehicleZAngle(float z_angle) const
		{ return ::SetVehicleZAngle(id_, z_angle); }
	bool GetRotationQuat(float &w, float &x, float &y, float &z) const
		{ return ::GetVehicleRotationQuat(id_, &w, &x, &y, &z); }
	bool SetParamsForPlayer(int playerid, bool objective, bool doorslocked) const
		{ return ::SetVehicleParamsForPlayer(id_, playerid, objective, doorslocked); }
	bool SetParamsEx(bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective) const
		{ return ::SetVehicleParamsEx(id_, engine, lights, alarm, doors, bonnet, boot, objective); }
	bool GetParamsEx(bool *engine, bool *lights, bool *alarm, bool *doors, bool *bonnet, bool *boot, bool *objective) const
		{ return ::GetVehicleParamsEx(id_, engine, lights, alarm, doors, bonnet, boot, objective); }
	bool GetParamsEx(bool &engine, bool &lights, bool &alarm, bool &doors, bool &bonnet, bool &boot, bool &objective) const
		{ return ::GetVehicleParamsEx(id_, &engine, &lights, &alarm, &doors, &bonnet, &boot, &objective); }
	bool SetToRespawn() const
		{ return ::SetVehicleToRespawn(id_); }
	bool LinkToInterior(int interiorid) const
		{ return ::LinkVehicleToInterior(id_, interiorid); }
	bool AddComponent(int componentid) const 
		{ return ::AddVehicleComponent(id_, componentid); }
	bool RemoveComponent(int componentid) const
		{ return ::RemoveVehicleComponent(id_, componentid); }
	bool ChangeColor(int color1, int color2) const
		{ return ::ChangeVehicleColor(id_, color1, color2); }
	bool ChangePaintjob(int paintjobid) const
		{ return ::ChangeVehiclePaintjob(id_, paintjobid); }
	bool SetHealth(float health) const
		{ return ::SetVehicleHealth(id_, health); }
	bool GetHealth(float *health) const
		{ return ::GetVehicleHealth(id_, health); }
	bool GetHealth(float &health) const
		{ return ::GetVehicleHealth(id_, &health); }
	float GetHealth() const {
		float health;
		::GetVehicleHealth(id_, &health);
		return health;
	}
	bool AttachTrailer(int trailerid) const
		{ return ::AttachTrailerToVehicle(trailerid, id_); }
	bool DetachTrailer() const
		{ return ::DetachTrailerFromVehicle(id_); }
	bool IsTrailerAttached() const
		{ return ::IsTrailerAttachedToVehicle(id_); }
	int GetTrailer() const
		{ return ::GetVehicleTrailer(id_); }
	bool SetNumberPlate(const char *numberplate) const
		{ return ::SetVehicleNumberPlate(id_, numberplate); }
	int GetModel() const
		{ return ::GetVehicleModel(id_); }
	int GetComponentInSlot(int slot) const
		{ return ::GetVehicleComponentInSlot(id_, slot); }
	bool Repair() const
		{ return ::RepairVehicle(id_); }
	bool GetVelocity(float *X, float *Y, float *Z) const
		{ return ::GetVehicleVelocity(id_, X, Y, Z); }
	bool GetVelocity(float &X, float &Y, float &Z) const
		{ return ::GetVehicleVelocity(id_, &X, &Y, &Z); }
	float GetSpeed() const {
		float velX, velY, velZ;
		GetVelocity(velX, velY, velZ);
		return std::sqrt(velX*velX + velY*velY + velZ*velZ);
	}
	bool SetVelocity(float X, float Y, float Z) const
		{ return ::SetVehicleVelocity(id_, X, Y, Z); }
	bool SetAngularVelocity(float X, float Y, float Z) const
		{ return ::SetVehicleAngularVelocity(id_, X, Y, Z); }
	bool GetDamageStatus(int *panels, int *doors, int *lights, int *tires) const
		{ return ::GetVehicleDamageStatus(id_, panels, doors, lights, tires); }
	bool GetDamageStatus(int &panels, int &doors, int &lights, int &tires) const
		{ return ::GetVehicleDamageStatus(id_, &panels, &doors, &lights, &tires); }
	bool UpdateDamageStatus(int panels, int doors, int lights, int tires) const
		{ return ::UpdateVehicleDamageStatus(id_, panels, doors, lights, tires); }
	bool SetVirtualWorld(int worldid) const
		{ return ::SetVehicleVirtualWorld(id_, worldid); }
	int GetVehicleVirtualWorld() const
		{ return ::GetVehicleVirtualWorld(id_); }

private:
	const int id_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_VEHICLES_H */
