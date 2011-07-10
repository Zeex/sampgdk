#include "wrapper.h"
#include "internal/fakeamx.h"

using samp::internal::fakeAmx;

namespace samp {

int CreateVehicle(int vehicletype, float x, float y, float z, float rotation, 
    int color1, int color2, long respawn_delay)
{
    static auto native = Wrapper::GetInstance()->GetNative("CreateVehicle");
    cell params[] = {
        8 * 4,
        vehicletype,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(rotation),
        color1,
        color2,
        respawn_delay
    };
    return native(&::fakeAmx, params);
}

bool DestroyVehicle(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("DestroyVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsVehicleStreamedIn(int vehicleid, int forplayerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsVehicleStreamedIn");
    cell params[] = {
        2 * 4,
        vehicleid,
        forplayerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehiclePos(int vehicleid, float &x, float &y, float &z) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehiclePos");
    cell params[] = {
        4 * 4,
        vehicleid,
        reinterpret_cast<cell>(&x),
        reinterpret_cast<cell>(&y),
        reinterpret_cast<cell>(&z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehiclePos(int vehicleid, float x, float y, float z) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehiclePos");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleZAngle(int vehicleid, float &z_angle) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleZAngle");
    cell params[] = {
        2 * 4,
        vehicleid,
        reinterpret_cast<cell>(&z_angle)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleRotationQuat(int vehicleid, float &w, float &x, float &y, float &z) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleRotationQuat");
    cell params[] = {
        5 * 4,
        vehicleid,
        reinterpret_cast<cell>(&w),
        reinterpret_cast<cell>(&x),
        reinterpret_cast<cell>(&y),
        reinterpret_cast<cell>(&z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleZAngle(int vehicleid, float z_angle) {
    static auto native = Wrapper::GetInstance()->GetNative("IsVehicleStreamedIn");
    cell params[] = {
        2 * 4,
        vehicleid,
        amx_ftoc(z_angle)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked);
void ManualVehicleEngineAndLights();

bool SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, 
    bool bonnet, bool boot, bool objective) 
{
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleParamsEx");
    cell params[] = {
        8 * 4,
        vehicleid,
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleParamsEx(int vehicleid, bool &engine, bool &lights, bool &alarm, bool &doors, 
    bool &bonnet, bool &boot, bool &objective) 
{
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleParamsEx");
    cell params[] = {
        8 * 4,
        vehicleid,
        reinterpret_cast<cell>(&engine),
        reinterpret_cast<cell>(&lights),
        reinterpret_cast<cell>(&alarm),
        reinterpret_cast<cell>(&doors),
        reinterpret_cast<cell>(&bonnet),
        reinterpret_cast<cell>(&boot),
        reinterpret_cast<cell>(&objective)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleToRespawn(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleToRespawn");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

bool LinkVehicleToInterior(int vehicleid, int interiorid) {
    static auto native = Wrapper::GetInstance()->GetNative("LinkVehicleToInterior");
    cell params[] = {
        2 * 4,
        vehicleid,
        interiorid
    };
    return native(&::fakeAmx, params) != 0;
}

bool AddVehicleComponent(int vehicleid, int componentid) {
    static auto native = Wrapper::GetInstance()->GetNative("AddVehicleComponent");
    cell params[] = {
        2 * 4,
        vehicleid,
        componentid
    };
    return native(&::fakeAmx, params) != 0;
}

bool RemoveVehicleComponent(int vehicleid, int componentid) {
    static auto native = Wrapper::GetInstance()->GetNative("RemoveVehicleComponent");
    cell params[] = {
        2 * 4,
        vehicleid,
        componentid
    };
    return native(&::fakeAmx, params) != 0;
}

bool ChangeVehicleColor(int vehicleid, int color1, int color2) {
    static auto native = Wrapper::GetInstance()->GetNative("ChangeVehicleColor");
    cell params[] = {
        3 * 4,
        vehicleid,
        color1,
        color2
    };
    return native(&::fakeAmx, params) != 0;
}

bool ChangeVehiclePaintjob(int vehicleid, int paintjobid) {
    static auto native = Wrapper::GetInstance()->GetNative("ChangeVehiclePaintjob");
    cell params[] = {
        2 * 4,
        vehicleid,
        paintjobid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleHealth(int vehicleid, float health) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleHealth");
    cell params[] = {
        2 * 4,
        vehicleid,
        amx_ftoc(health)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleHealth(int vehicleid, float &health) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleHealth");
    cell params[] = {
        2 * 4,
        vehicleid,
        reinterpret_cast<cell>(&health)
    };
    return native(&::fakeAmx, params) != 0;
}

void AttachTrailerToVehicle(int trailerid, int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("AttachTrailerToVehicle");
    cell params[] = {
        2 * 4,
        trailerid,
        vehicleid
    };
    native(&::fakeAmx, params);
}

void DetachTrailerFromVehicle(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("DetachTrailerFromVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    native(&::fakeAmx, params);
}

bool IsTrailerAttachedToVehicle(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsTrailerAttachedToVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetVehicleTrailer(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleTrailer");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params);
}

bool SetVehicleNumberPlate(int vehicleid, const std::string &numberplate) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleNumberPlate");
    cstring numberplate_(numberplate.begin(), numberplate.end());
    cell params[] = {
        2 * 4,
        vehicleid,
        reinterpret_cast<cell>(numberplate_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

int GetVehicleModel(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleModel");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params);
}

int GetVehicleComponentInSlot(int vehicleid, int slot) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleComponentInSlot");
    cell params[] = {
        2 * 4,
        vehicleid,
        slot
    };
    return native(&::fakeAmx, params);
}

int GetVehicleComponentType(int component) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleComponentType");
    cell params[] = {
        1 * 4,
        component
    };
    return native(&::fakeAmx, params);
}

bool RepairVehicle(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("RepairVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleVelocity(int vehicleid, float &X, float &Y, float &Z) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleVelocity");
    cell params[] = {
        4 * 4,
        vehicleid,
        reinterpret_cast<cell>(&X),
        reinterpret_cast<cell>(&Y),
        reinterpret_cast<cell>(&Z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleVelocity(int vehicleid, float X, float Y, float Z) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleVelocity");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleAngularVelocity");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleDamageStatus(int vehicleid, long &panels, long &doors, long &lights, long &tires) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleDamageStatus");
    cell params[] = {
        5 * 4,
        vehicleid,
        reinterpret_cast<cell>(&panels),
        reinterpret_cast<cell>(&doors),
        reinterpret_cast<cell>(&lights),
        reinterpret_cast<cell>(&tires)
    };
    return native(&::fakeAmx, params) != 0;
}

bool UpdateVehicleDamageStatus(int vehicleid, long panels, long doors, long lights, long tires) {
    static auto native = Wrapper::GetInstance()->GetNative("UpdateVehicleDamageStatus");
    cell params[] = {
        5 * 4,
        vehicleid,
        amx_ftoc(panels),
        amx_ftoc(doors),
        amx_ftoc(lights),
        amx_ftoc(tires)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetVehicleVirtualWorld(int vehicleid, int worldid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetVehicleVirtualWorld");
    cell params[] = {
        2 * 4,
        vehicleid,
        worldid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetVehicleVirtualWorld(int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetVehicleVirtualWorld");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

} // namespace samp