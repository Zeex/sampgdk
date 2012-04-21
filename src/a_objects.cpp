// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/export.h>
#include <sampgdk/amx/amx.h>

#include "fakeamx.h"
#include "natives.h"

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CreateObject");
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ,
	float frotX, float frotY, float frotZ)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AttachObjectToVehicle");
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
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToObject(int objectid, int attachtoid, float OffsetX, float OffsetY, float OffsetZ,
	float RotX, float RotY, float RotZ, bool SyncRotation)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AttachObjectToObject");
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
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ,
	float rX, float rY, float rZ)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AttachObjectToPlayer");
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
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetObjectPos");
	cell params[] = {
		4 * 4,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float *x, float *y, float *z) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetObjectPos");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetObjectRot");
	cell params[] = {
		4 * 4,
		objectid,
		amx_ftoc(rotX),
		amx_ftoc(rotY),
		amx_ftoc(rotZ)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float *rotX, float *rotY, float *rotZ) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetObjectRot");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*rotX = rotX_.GetAsFloat();
	*rotY = rotY_.GetAsFloat();
	*rotZ = rotZ_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsValidObject");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyObject(int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DestroyObject");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float X, float Y, float Z, float Speed,
	float RotX, float RotY, float RotZ)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("MoveObject");
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("StopObject");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsObjectMoving(int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsObjectMoving");
	cell params[] = {
		1 * 4,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL EditObject(int playerid, int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("EditObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL EditPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("EditPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SelectObject(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SelectObject");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL CancelEdit(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CancelEdit");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z,
	float rX, float rY, float rZ, float DrawDistance)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CreatePlayerObject");
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer,
	float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AttachPlayerObjectToPlayer");
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
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, 
	float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ) 
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AttachPlayerObjectToVehicle");
	cell params[] = {
		9 * 4,
		playerid,
		objectid,
		vehicleid,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(fRotX),
		amx_ftoc(fRotY),
		amx_ftoc(RotZ)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetPlayerObjectPos");
	cell params[] = {
		5 * 4,
		playerid,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float *x, float *y, float *z) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetPlayerObjectPos");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetPlayerObjectRot");
	cell params[] = {
		5 * 4,
		playerid,
		objectid,
		amx_ftoc(rotX),
		amx_ftoc(rotY),
		amx_ftoc(rotZ)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float *rotX, float *rotY, float *rotZ) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetPlayerObjectRot");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*rotX = rotX_.GetAsFloat();
	*rotY = rotY_.GetAsFloat();
	*rotZ = rotZ_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsValidPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DestroyPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed,
	float RotX, float RotY, float RotZ)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("MovePlayerObject");
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("StopPlayerObject");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerObjectMoving(int playerid, int objectid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsPlayerObjectMoving");
	cell params[] = {
		2 * 4,
		playerid,
		objectid
	};
	return FakeAmx::CallNative(native, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectMaterial(int objectid, int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetObjectMaterial");
	FakeAmxHeapObject txdname_(txdname);
	FakeAmxHeapObject texturename_(texturename);
	cell params[] = {
		6 * 4,
		objectid,
		materialindex,
		modelid,
		txdname_.address(),
		texturename_.address(),
		materialcolor
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetPlayerObjectMaterial");
	FakeAmxHeapObject txdname_(txdname);
	FakeAmxHeapObject texturename_(texturename);
	cell params[] = {
		7 * 4,
		playerid,
		objectid,
		materialindex,
		modelid,
		txdname_.address(),
		texturename_.address(),
		materialcolor
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetObjectMaterialText(int objectid, const char *text, int materialindex, int materialsize, const char *fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetObjectMaterialText");
	FakeAmxHeapObject text_(text);
	FakeAmxHeapObject fontface_(fontface);
	cell params[] = {
		10 * 4,
		objectid,
		text_.address(),
		materialindex,
		materialsize,
		fontface_.address(),
		fontsize,
		bold,
		fontcolor,
		backcolor,
		textalignment
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerObjectMaterialText(int playerid, int objectid, const char *text, int materialindex, int materialsize, const char *fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetPlayerObjectMaterialText");
	FakeAmxHeapObject text_(text);
	FakeAmxHeapObject fontface_(fontface);
	cell params[] = {
		11 * 4,
		playerid,
		objectid,
		text_.address(),
		materialindex,
		materialsize,
		fontface_.address(),
		fontsize,
		bold,
		fontcolor,
		backcolor,
		textalignment
	};
	return FakeAmx::CallNativeBool(native, params);
}