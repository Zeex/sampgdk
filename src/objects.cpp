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

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#include "fakeamx.h"
#include "wrapper.h"

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("CreateObject");
	cell params[] = {
		8 * 4,
		modelid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ),
		amx_ftoc(DrawDistance)
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, 
	float frotX, float frotY, float frotZ)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AttachObjectToVehicle");
	cell params[] = {
		8 * 4,
		objectid,
		vehicleid,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(frotX),
		amx_ftoc(frotY),
		amx_ftoc(frotZ)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToObject(int objectid, int attachtoid, float OffsetX, float OffsetY, float OffsetZ, 
	float RotX, float RotY, float RotZ, bool SyncRotation)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AttachObjectToObject");
	cell params[] = {
		9 * 4,
		objectid,
		attachtoid,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ),
		amx_ftoc(RotX),
		amx_ftoc(RotY),
		amx_ftoc(RotZ),
		SyncRotation
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, 
	float rX, float rY, float rZ)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AttachObjectToPlayer");
	cell params[] = {
		8 * 4,
		objectid,
		playerid,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, 
	float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AttachPlayerObjectToPlayer");
	cell params[] = {
		9 * 4,
		objectplayer,
		objectid,
		attachplayer,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetObjectPos");
	cell params[] = {
		4 * 4,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float &x, float &y, float &z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetObjectPos");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		4 * 4,
		objectid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	x = x_.GetAsFloat();
	y = y_.GetAsFloat();
	z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetObjectRot");
	cell params[] = {
		4 * 4,
		objectid,
		amx_ftoc(rotX),
		amx_ftoc(rotY),
		amx_ftoc(rotZ)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float &rotX, float &rotY, float &rotZ) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetObjectRot");
	FakeAmxHeapObject rotX_;
	FakeAmxHeapObject rotY_;
	FakeAmxHeapObject rotZ_;
	cell params[] = {
		4 * 4,
		objectid,
		rotX_.address(),
		rotY_.address(),
		rotZ_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	rotX = rotX_.GetAsFloat();
	rotY = rotY_.GetAsFloat();
	rotZ = rotZ_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsValidObject");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL DestroyObject(int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DestroyObject");
	cell params[] = {
		1 * 4,
		objectid
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float X, float Y, float Z, float Speed, 
	float RotX, float RotY, float RotZ)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("MoveObject");
	cell params[] = {
		8 * 4,
		objectid,
		amx_ftoc(X),
		amx_ftoc(Y),
		amx_ftoc(Z),
		amx_ftoc(Speed),
		amx_ftoc(RotX),
		amx_ftoc(RotY),
		amx_ftoc(RotZ)
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("StopObject");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsObjectMoving(int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsObjectMoving");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::GetInstance().CallNative(native, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z, 
	float rX, float rY, float rZ, float DrawDistance)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("CreatePlayerObject");
	cell params[] = {
		9 * 4,
		playerid,
		modelid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ),
		amx_ftoc(DrawDistance)
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerObjectPos");
	cell params[] = {
		5 * 4,
		playerid,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float &x, float &y, float &z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerObjectPos");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		5 * 4,
		playerid,
		objectid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	x = x_.GetAsFloat();
	y = y_.GetAsFloat();
	z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerObjectRot");
	cell params[] = {
		5 * 4,
		playerid,
		objectid,
		amx_ftoc(rotX),
		amx_ftoc(rotY),
		amx_ftoc(rotZ)
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float &rotX, float &rotY, float &rotZ) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerObjectRot");
	FakeAmxHeapObject rotX_;
	FakeAmxHeapObject rotY_;
	FakeAmxHeapObject rotZ_;
	cell params[] = {
		5 * 4,
		playerid,
		objectid,
		rotX_.address(),
		rotY_.address(),
		rotZ_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	rotX = rotX_.GetAsFloat();
	rotY = rotY_.GetAsFloat();
	rotZ = rotZ_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsValidPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DestroyPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

int MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, 
	float RotX, float RotY, float RotZ)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("MovePlayerObject");
	cell params[] = {
		9 * 4,
		playerid,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(Speed),
		amx_ftoc(RotX),
		amx_ftoc(RotY),
		amx_ftoc(RotZ)
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("StopPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerObjectMoving(int playerid, int objectid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerObjectMoving");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::GetInstance().CallNative(native, params) != 0;
}
