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

#ifndef SAMPGDK_A_OBJECTS_H
#define SAMPGDK_A_OBJECTS_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/export.h>

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float *rotX, float *rotY, float *rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyObject(int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsObjectMoving(int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL EditObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL EditPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SelectObject(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL CancelEdit(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectMaterial(int objectid, int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor);
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float *rotX, float *rotY, float *rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerObjectMoving(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor);

#ifdef __cplusplus

#include <cassert>
#include <cmath>
#include <string>

class Object {
public:
	// Construct from an object ID
	Object(int objectid) : id_(objectid) { assert(id_ != INVALID_OBJECT_ID); }
	virtual ~Object() {}

	// Implicit convertion to 'int'
	operator int() const { return id_; }

	// Explicit ID request
	int GetId() const { return id_; }

	// Sort of factory method
	static Object Create(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0f) {
		return ::CreateObject(modelid, x, y, z, rX, rY, rZ, DrawDistance);
	}
	
	bool AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachObjectToVehicle(id_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool AttachToObject(int objectid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation = true) const {
		return ::AttachObjectToObject(id_, objectid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, SyncRotation);
	}
	bool AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachObjectToPlayer(id_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool SetPos(float x, float y, float z) const
		{ return ::SetObjectPos(id_, x, y, z); } 
	bool GetPos(float *x, float *y, float *z) const
		{ return ::GetObjectPos(id_, x, y, z); } 
	bool GetPos(float &x, float &y, float &z) const
		{ return ::GetObjectPos(id_, &x, &y, &z); } 
	bool SetRot(float rotX, float rotY, float rotZ) const
		{ return ::SetObjectRot(id_, rotX, rotY, rotZ); }
	bool GetRot(float *rotX, float *rotY, float *rotZ) const
		{ return ::GetObjectRot(id_, rotX, rotY, rotZ); }
	bool GetRot(float &rotX, float &rotY, float &rotZ) const
		{ return ::GetObjectRot(id_, &rotX, &rotY, &rotZ); }
	bool IsValid() const 
		{ return ::IsValidObject(id_); }
	bool Destroy() const
		{ return ::DestroyObject(id_); }
	int Move(float X, float Y, float Z, float Speed, float RotX = -1000.0f, float RotY = -1000.0f, float RotZ = -1000.0f) const
		{ return ::MoveObject(id_, X, Y, Z, Speed, RotX, RotY, RotZ); }
	bool Stop() const
		{ return ::StopObject(id_); }
	bool IsMoving() const 
		{ return ::IsObjectMoving(id_); }
	bool SetMaterial(int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor = 0) 
		{ return ::SetObjectMaterial(id_, materialindex, modelid, txdname, texturename, materialcolor); }

private:
	const int id_;
};

class PlayerObject {
public:
	// Construct from a player ID and an object ID
	PlayerObject(int playerid, int objectid) 
		: playerid_(playerid)
		, objectid_(objectid) 
	{
		assert(objectid_ != INVALID_OBJECT_ID);
		assert(playerid_ != INVALID_PLAYER_ID);
	}

	virtual ~PlayerObject() {}

	// Explicit ID request
	int GetPlayerId() const { return playerid_; }
	int GetObjectId() const { return objectid_; }

	// Sort of factory method
	static PlayerObject Create(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0f) {
		return PlayerObject(playerid, ::CreatePlayerObject(playerid, modelid, x, y, z, rX, rY, rZ, DrawDistance));
	}
	
	bool AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachPlayerObjectToPlayer(playerid_, objectid_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ) const {
		return ::AttachPlayerObjectToVehicle(playerid_, objectid_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool SetPos(float x, float y, float z) const
		{ return ::SetPlayerObjectPos(playerid_, objectid_, x, y, z); } 
	bool GetPos(float *x, float *y, float *z) const
		{ return ::GetPlayerObjectPos(playerid_, objectid_, x, y, z); } 
	bool GetPos(float &x, float &y, float &z) const
		{ return ::GetPlayerObjectPos(playerid_, objectid_, &x, &y, &z); } 
	bool SetRot(float rotX, float rotY, float rotZ) const
		{ return ::SetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ); }
	bool GetRot(float *rotX, float *rotY, float *rotZ) const
		{ return ::GetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ); }
	bool GetRot(float &rotX, float &rotY, float &rotZ) const
		{ return ::GetPlayerObjectRot(playerid_, objectid_, &rotX, &rotY, &rotZ); }
	bool IsValid() const 
		{ return ::IsValidPlayerObject(playerid_, objectid_); }
	bool Destroy() const
		{ return ::DestroyPlayerObject(playerid_, objectid_); }
	int Move(float X, float Y, float Z, float Speed, float RotX = -1000.0f, float RotY = -1000.0f, float RotZ = -1000.0f) const
		{ return ::MovePlayerObject(playerid_, objectid_, X, Y, Z, Speed, RotX, RotY, RotZ); }
	bool Stop() const
		{ return ::StopPlayerObject(playerid_, objectid_); }
	bool IsMoving() const 
		{ return ::IsPlayerObjectMoving(playerid_, objectid_); }
	bool SetMaterial(int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor = 0) 
		{ return ::SetPlayerObjectMaterial(playerid_, objectid_, materialindex, modelid, txdname, texturename, materialcolor); }

private:
	const int playerid_;
	const int objectid_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_OBJECTS_H */
