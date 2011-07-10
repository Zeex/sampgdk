#ifndef SAMP_OBJECTS_H
#define SAMP_OBJECTS_H

namespace samp {

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

} // namespace samp

#endif