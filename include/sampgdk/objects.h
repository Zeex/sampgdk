// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#ifndef SAMPGDK_OBJECTS_H
#define SAMPGDK_OBJECTS_H

#include <sampgdk/export.h>

namespace sampgdk {

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float &x, float &y, float &z);
SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float &rotX, float &rotY, float &rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL DestroyObject(int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float x, float y, float z, float Speed);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0);
SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float &x, float &y, float &z);
SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float &rotX, float &rotY, float &rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);

} // namespace sampgdk

#endif

