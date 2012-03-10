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

#ifndef SAMPGDK_OBJECTS_H
#define SAMPGDK_OBJECTS_H

#include <sampgdk/config.h>
#include <sampgdk/export.h>
#include <sampgdk/samp.h>

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float *x, float *y, float *z);
SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float *rotX, float *rotY, float *rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL DestroyObject(int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsObjectMoving(int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL EditObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL EditAttachedObject(int playerid, int index);
SAMPGDK_EXPORT bool SAMPGDK_CALL EditPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL SelectObject(int playerid);
SAMPGDK_EXPORT void SAMPGDK_CALL CancelEdit(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ);
SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float *x, float *y, float *z);
SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float *rotX, float *rotY, float *rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerObjectMoving(int playerid, int objectid);

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
	static Object Create(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance) {
		return ::CreateObject(modelid, x, y, z, rX, rY, rZ, DrawDistance);
	}
	
	virtual void AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		::AttachObjectToVehicle(id_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	virtual void AttachToObject(int objectid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation) const {
		::AttachObjectToObject(id_, objectid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, SyncRotation);
	}
	virtual void AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		::AttachObjectToPlayer(id_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	void SetPos(float x, float y, float z) const
		{ ::SetObjectPos(id_, x, y, z); } 
	virtual void GetPos(float *x, float *y, float *z) const
		{ ::GetObjectPos(id_, x, y, z); } 
	virtual void GetPos(float &x, float &y, float &z) const
		{ ::GetObjectPos(id_, &x, &y, &z); } 
	virtual void SetRot(float rotX, float rotY, float rotZ) const
		{ ::SetObjectRot(id_, rotX, rotY, rotZ); }
	virtual void GetRot(float *rotX, float *rotY, float *rotZ) const
		{ ::GetObjectRot(id_, rotX, rotY, rotZ); }
	virtual void GetRot(float &rotX, float &rotY, float &rotZ) const
		{ ::GetObjectRot(id_, &rotX, &rotY, &rotZ); }
	virtual bool IsValid() const 
		{ return ::IsValidObject(id_); }
	virtual void Destroy() const
		{ ::DestroyObject(id_); }
	virtual int Move(float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ) const
		{ return ::MoveObject(id_, X, Y, Z, Speed, RotX, RotY, RotZ); }
	virtual void Stop() const
		{ ::StopObject(id_); }
	virtual bool IsMoving() const 
		{ return ::IsObjectMoving(id_); }

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
	static PlayerObject Create(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance) {
		return PlayerObject(playerid, ::CreatePlayerObject(playerid, modelid, x, y, z, rX, rY, rZ, DrawDistance));
	}
	
	virtual void AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		::AttachPlayerObjectToPlayer(playerid_, objectid_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	virtual void SetPos(float x, float y, float z) const
		{ ::SetPlayerObjectPos(playerid_, objectid_, x, y, z); } 
	virtual void GetPos(float *x, float *y, float *z) const
		{ ::GetPlayerObjectPos(playerid_, objectid_, x, y, z); } 
	virtual void GetPos(float &x, float &y, float &z) const
		{ ::GetPlayerObjectPos(playerid_, objectid_, &x, &y, &z); } 
	virtual void SetRot(float rotX, float rotY, float rotZ) const
		{ ::SetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ); }
	virtual void GetRot(float *rotX, float *rotY, float *rotZ) const
		{ ::GetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ); }
	virtual void GetRot(float &rotX, float &rotY, float &rotZ) const
		{ ::GetPlayerObjectRot(playerid_, objectid_, &rotX, &rotY, &rotZ); }
	virtual bool IsValid() const 
		{ return ::IsValidPlayerObject(playerid_, objectid_); }
	virtual void Destroy() const
		{ ::DestroyPlayerObject(playerid_, objectid_); }
	virtual int Move(float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ) const
		{ return ::MovePlayerObject(playerid_, objectid_, X, Y, Z, Speed, RotX, RotY, RotZ); }
	virtual void Stop() const
		{ ::StopPlayerObject(playerid_, objectid_); }
	virtual bool IsMoving() const 
		{ return ::IsPlayerObjectMoving(playerid_, objectid_); }

private:
	const int playerid_;
	const int objectid_;
};

#endif /* __cplusplus

#endif /* !SAMPGDK_OBJECTS_H */
