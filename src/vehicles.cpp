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

#include <sampgdk/vehicles.h>

#include "fakeamx.h"
#include "natives.h"

namespace sampgdk {

SAMPGDK_EXPORT int SAMPGDK_CALL CreateVehicle(int vehicletype, float x, float y, float z, float rotation, 
    int color1, int color2, long respawn_delay)
{
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("CreateVehicle");
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

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyVehicle(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("DestroyVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsVehicleStreamedIn(int vehicleid, int forplayerid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("IsVehicleStreamedIn");
    cell params[] = {
        2 * 4,
        vehicleid,
        forplayerid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehiclePos(int vehicleid, float &x, float &y, float &z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehiclePos");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        vehicleid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.GetAsFloat();
    y = y_.GetAsFloat();
    z = z_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehiclePos(int vehicleid, float x, float y, float z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehiclePos");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleZAngle(int vehicleid, float &z_angle) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleZAngle");
    FakeAmxHeapObject z_angle_;
    cell params[] = {
        2 * 4,
        vehicleid,
        z_angle_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    z_angle = z_angle_.GetAsFloat();
    return ret;

}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleRotationQuat(int vehicleid, float &w, float &x, float &y, float &z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleRotationQuat");
    FakeAmxHeapObject w_;
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        5 * 4,
        vehicleid,
        w_.address(),
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    w = w_.GetAsFloat();
    x = x_.GetAsFloat();
    y = y_.GetAsFloat();
    z = z_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT float SAMPGDK_CALL GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleDistanceFromPoint");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    cell ret = native(&::fakeAmx, params);
    return amx_ctof(ret);
}


SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleZAngle(int vehicleid, float z_angle) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("IsVehicleStreamedIn");
    cell params[] = {
        2 * 4,
        vehicleid,
        amx_ftoc(z_angle)
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleParamsForPlayer");
    cell params[] = {
        4 * 4,
        vehicleid,
        playerid,
        objective,
        doorslocked
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL ManualVehicleEngineAndLights() {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("ManualVehicleEngineAndLights");
    native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, 
    bool bonnet, bool boot, bool objective) 
{
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleParamsEx");
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

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleParamsEx(int vehicleid, bool &engine, bool &lights, bool &alarm, bool &doors, 
    bool &bonnet, bool &boot, bool &objective) 
{
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleParamsEx");
    FakeAmxHeapObject engine_;
    FakeAmxHeapObject lights_;
    FakeAmxHeapObject alarm_;
    FakeAmxHeapObject doors_;
    FakeAmxHeapObject bonnet_;
    FakeAmxHeapObject boot_;
    FakeAmxHeapObject objective_;
    cell params[] = {
        8 * 4,
        vehicleid,
        engine_.address(),
        lights_.address(),
        alarm_.address(),
        doors_.address(),
        bonnet_.address(),
        boot_.address(),
        objective_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    engine = engine_.Get() != 0;
    lights = lights_.Get() != 0;
    alarm  = alarm_.Get() != 0;
    doors  = doors_.Get() != 0;
    bonnet = bonnet_.Get() != 0;
    engine = boot_.Get() != 0;
    engine = objective_.Get() != 0;
    return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleToRespawn(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleToRespawn");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL LinkVehicleToInterior(int vehicleid, int interiorid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("LinkVehicleToInterior");
    cell params[] = {
        2 * 4,
        vehicleid,
        interiorid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AddVehicleComponent(int vehicleid, int componentid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("AddVehicleComponent");
    cell params[] = {
        2 * 4,
        vehicleid,
        componentid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RemoveVehicleComponent(int vehicleid, int componentid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("RemoveVehicleComponent");
    cell params[] = {
        2 * 4,
        vehicleid,
        componentid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ChangeVehicleColor(int vehicleid, int color1, int color2) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("ChangeVehicleColor");
    cell params[] = {
        3 * 4,
        vehicleid,
        color1,
        color2
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ChangeVehiclePaintjob(int vehicleid, int paintjobid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("ChangeVehiclePaintjob");
    cell params[] = {
        2 * 4,
        vehicleid,
        paintjobid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleHealth(int vehicleid, float health) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleHealth");
    cell params[] = {
        2 * 4,
        vehicleid,
        amx_ftoc(health)
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleHealth(int vehicleid, float &health) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleHealth");
    FakeAmxHeapObject health_;
    cell params[] = {
        2 * 4,
        vehicleid,
        health_.address()
    };
    bool ret =native(&::fakeAmx, params) != 0;
    health = health_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachTrailerToVehicle(int trailerid, int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("AttachTrailerToVehicle");
    cell params[] = {
        2 * 4,
        trailerid,
        vehicleid
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL DetachTrailerFromVehicle(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("DetachTrailerFromVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsTrailerAttachedToVehicle(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("IsTrailerAttachedToVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleTrailer(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleTrailer");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleNumberPlate(int vehicleid, const char *numberplate) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleNumberPlate");
    FakeAmxHeapObject numberplate_(numberplate);
    cell params[] = {
        2 * 4,
        vehicleid,
        numberplate_.address()
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleModel(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleModel");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleComponentInSlot(int vehicleid, int slot) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleComponentInSlot");
    cell params[] = {
        2 * 4,
        vehicleid,
        slot
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleComponentType(int component) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleComponentType");
    cell params[] = {
        1 * 4,
        component
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RepairVehicle(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("RepairVehicle");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleVelocity(int vehicleid, float &x, float &y, float &z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleVelocity");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        vehicleid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.GetAsFloat();
    y = y_.GetAsFloat();
    z = z_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleVelocity(int vehicleid, float x, float y, float z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleVelocity");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleAngularVelocity(int vehicleid, float x, float y, float z) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleAngularVelocity");
    cell params[] = {
        4 * 4,
        vehicleid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleDamageStatus(int vehicleid, long &panels, long &doors, long &lights, long &tires) {
    static AMX_NATIVE native =NativeManager::GetInstance()->GetNative("GetVehicleDamageStatus");
    FakeAmxHeapObject panels_;
    FakeAmxHeapObject doors_;
    FakeAmxHeapObject lights_;
    FakeAmxHeapObject tires_;
    cell params[] = {
        5 * 4,
        vehicleid,
        panels_.address(),
        doors_.address(),
        lights_.address(),
        tires_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    panels = panels_.Get();
    doors  = doors_.Get();
    lights = lights_.Get();
    tires  = tires_.Get();
    return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL UpdateVehicleDamageStatus(int vehicleid, long panels, long doors, long lights, long tires) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("UpdateVehicleDamageStatus");
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

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleVirtualWorld(int vehicleid, int worldid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("SetVehicleVirtualWorld");
    cell params[] = {
        2 * 4,
        vehicleid,
        worldid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleVirtualWorld(int vehicleid) {
    static AMX_NATIVE native = NativeManager::GetInstance()->GetNative("GetVehicleVirtualWorld");
    cell params[] = {
        1 * 4,
        vehicleid
    };
    return native(&::fakeAmx, params) != 0;
}

} // namespace sampgdk

