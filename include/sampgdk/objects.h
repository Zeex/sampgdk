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

#ifndef SAMPGDK_OBJECTS_H
#define SAMPGDK_OBJECTS_H

#include <sampgdk/config.h>

namespace sampgdk {

int CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0);
void AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
void AttachObjectToObject(int objectid, int attachtoid, float OffsetX, float OffsetY, float OffsetZ, float RotX, float RotY, float RotZ, bool SyncRotation = true);
void AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
void AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
void SetObjectPos(int objectid, float x, float y, float z);
bool GetObjectPos(int objectid, float &x, float &y, float &z);
void SetObjectRot(int objectid, float rotX, float rotY, float rotZ);
bool GetObjectRot(int objectid, float &rotX, float &rotY, float &rotZ);
bool IsValidObject(int objectid);
void DestroyObject(int objectid);
int MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX = -1000.0, float RotY = -1000.0, float RotZ = -1000.0);
bool StopObject(int objectid);
bool IsObjectMoving(int objectid);
int CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0);
void SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z);
bool GetPlayerObjectPos(int playerid, int objectid, float &x, float &y, float &z);
void SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ);
bool GetPlayerObjectRot(int playerid, int objectid, float &rotX, float &rotY, float &rotZ);
bool IsValidPlayerObject(int playerid, int objectid);
void DestroyPlayerObject(int playerid, int objectid);
int MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX = -1000.0, float RotY = -1000.0, float RotZ = -1000.0);
bool StopPlayerObject(int playerid, int objectid);
bool IsPlayerObjectMoving(int playerid, int objectid);

} // namespace sampgdk

#endif

