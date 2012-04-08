/* Copyright (C) 2011-2012, Zeex
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
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>
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
SAMPGDK_EXPORT bool SAMPGDK_CALL ManualVehicleEngineAndLights();
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
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachTrailerToVehicle(int trailerid, int vehicleid);
SAMPGDK_EXPORT bool SAMPGDK_CALL DetachTrailerFromVehicle(int vehicleid);
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

#define VEHICLE_MODEL_INFO_SIZE				1
#define VEHICLE_MODEL_INFO_FRONTSEAT		2
#define VEHICLE_MODEL_INFO_REARSEAT			3
#define VEHICLE_MODEL_INFO_PETROLCAP		4
#define VEHICLE_MODEL_INFO_WHEELSFRONT		5
#define VEHICLE_MODEL_INFO_WHEELSREAR		6
#define VEHICLE_MODEL_INFO_WHEELSMID		7
#define VEHICLE_MODEL_INFO_FRONT_BUMPER_Z	8
#define VEHICLE_MODEL_INFO_REAR_BUMPER_Z	9

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleModelInfo(int model, int infotype, float *X, float *Y, float *Z);

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
	bool SetParamsEx(int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective) const
		{ return ::SetVehicleParamsEx(id_, engine, lights, alarm, doors, bonnet, boot, objective); }
	bool GetVehicleParamsEx(int *engine, int *lights, int *alarm, int *doors, int *bonnet, int *boot, int *objective) const
		{ return ::GetVehicleParamsEx(id_, engine, lights, alarm, doors, bonnet, boot, objective); }
	bool GetVehicleParamsEx(int &engine, int &lights, int &alarm, int &doors, int &bonnet, int &boot, int &objective) const
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
	int GetComponentInSlot(int vehicleid, int slot) const
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
	const int vehicleid_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_VEHICLES_H */
