#ifndef SAMP_VEHICLES_H
#define SAMP_VEHICLES_H

#include <string>

namespace samp {

#define CARMODTYPE_SPOILER        0
#define CARMODTYPE_HOOD           1
#define CARMODTYPE_ROOF           2
#define CARMODTYPE_SIDESKIRT      3
#define CARMODTYPE_LAMPS          4
#define CARMODTYPE_NITRO          5
#define CARMODTYPE_EXHAUST        6
#define CARMODTYPE_WHEELS         7
#define CARMODTYPE_STEREO         8
#define CARMODTYPE_HYDRAULICS     9
#define CARMODTYPE_FRONT_BUMPER   10
#define CARMODTYPE_REAR_BUMPER    11
#define CARMODTYPE_VENT_RIGHT     12
#define CARMODTYPE_VENT_LEFT      13

#define VEHICLE_PARAMS_UNSET      -1
#define VEHICLE_PARAMS_OFF         0
#define VEHICLE_PARAMS_ON          1

// Vehicle
int CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, long respawn_delay);
bool DestroyVehicle(int vehicleid);
bool IsVehicleStreamedIn(int vehicleid, int forplayerid);
bool GetVehiclePos(int vehicleid, float &x, float &y, float &z);
bool SetVehiclePos(int vehicleid, float x, float y, float z);
bool GetVehicleZAngle(int vehicleid, float &z_angle);
bool GetVehicleRotationQuat(int vehicleid, float &w, float &x, float &y, float &z);
bool SetVehicleZAngle(int vehicleid, float z_angle);
bool SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked);
void ManualVehicleEngineAndLights();
bool SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective);
bool GetVehicleParamsEx(int vehicleid, bool &engine, bool &lights, bool &alarm, bool &doors, bool &bonnet, bool &boot, bool &objective);
bool SetVehicleToRespawn(int vehicleid);
bool LinkVehicleToInterior(int vehicleid, int interiorid);
bool AddVehicleComponent(int vehicleid, int componentid);
bool RemoveVehicleComponent(int vehicleid, int componentid);
bool ChangeVehicleColor(int vehicleid, int color1, int color2);
bool ChangeVehiclePaintjob(int vehicleid, int paintjobid);
bool SetVehicleHealth(int vehicleid, float health);
bool GetVehicleHealth(int vehicleid, float &health);
void AttachTrailerToVehicle(int trailerid, int vehicleid);
void DetachTrailerFromVehicle(int vehicleid);
bool IsTrailerAttachedToVehicle(int vehicleid);
int GetVehicleTrailer(int vehicleid);
bool SetVehicleNumberPlate(int vehicleid, const std::string &numberplate);
int GetVehicleModel(int vehicleid);
int GetVehicleComponentInSlot(int vehicleid, int slot); // There is 1 slot for each CARMODTYPE_*
int GetVehicleComponentType(int component); // Find CARMODTYPE_* for component id
bool RepairVehicle(int vehicleid); // Repairs the damage model and resets the health
bool GetVehicleVelocity(int vehicleid, float &X, float &Y, float &Z);
bool SetVehicleVelocity(int vehicleid, float X, float Y, float Z);
bool SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z);
bool GetVehicleDamageStatus(int vehicleid, long &panels, long &doors, long &lights, long &tires);
bool UpdateVehicleDamageStatus(int vehicleid, long panels, long doors, long lights, long tires);

// Virtual Worlds
bool SetVehicleVirtualWorld(int vehicleid, int worldid);
bool GetVehicleVirtualWorld(int vehicleid);

} // namespace samp

#endif