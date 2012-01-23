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

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToObject(int objectid, int attachtoid, float OffsetX, float OffsetY, float OffsetZ, float RotX, float RotY, float RotZ, bool SyncRotation);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
SAMPGDK_EXPORT void SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float *x, float *y, float *z);
SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float *rotX, float *rotY, float *rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL DestroyObject(int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsObjectMoving(int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance);
SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float *x, float *y, float *z);
SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float *rotX, float *rotY, float *rotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT void SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT int SAMPGDK_CALL MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerObjectMoving(int playerid, int objectid);

#endif /* !SAMPGDK_OBJECTS_H */
