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

#ifndef SAMP_OBJECTS_H
#define SAMP_OBJECTS_H

namespace sampgdk {

int CreateObject(int modelid, float X, float Y, float Z, float rX, float rY, float rZ, float DrawDistance = 0.0);
bool AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ);
void SetObjectPos(int objectid, float X, float Y, float Z);
bool GetObjectPos(int objectid, float &X, float &Y, float &Z);
void SetObjectRot(int objectid, float RotX, float RotY, float RotZ);
bool GetObjectRot(int objectid, float &RotX, float &RotY, float &RotZ);
bool IsValidObject(int objectid);
void DestroyObject(int objectid);
int MoveObject(int objectid, float X, float Y, float Z, float Speed);
bool StopObject(int objectid);
int CreatePlayerObject(int playerid, int modelid, float X, float Y, float Z, float rX, float rY, float rZ, float DrawDistance = 0.0);
void SetPlayerObjectPos(int playerid, int objectid, float X, float Y, float Z);
bool GetPlayerObjectPos(int playerid, int objectid, float &X, float &Y, float &Z);
void SetPlayerObjectRot(int playerid, int objectid, float RotX, float RotY, float RotZ);
bool GetPlayerObjectRot(int playerid, int objectid, float &RotX, float &RotY, float &RotZ);
bool IsValidPlayerObject(int playerid, int objectid);
void DestroyPlayerObject(int playerid, int objectid);
int MovePlayerObject(int playerid, int objectid, float X, float Y, float Z, float Speed);
bool StopPlayerObject(int playerid, int objectid);
void AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);
void AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ);

} // namespace sampgdk

#endif

