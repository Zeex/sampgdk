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

SAMPGDK_EXPORT int SAMPGDK_CALL CreateVehicle(int vehicletype, float x, float y, float z, float rotation,
	int color1, int color2, int respawn_delay)
{
	static AMX_NATIVE native = Natives::GetNativeWarn("CreateVehicle");
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyVehicle(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("DestroyVehicle");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsVehicleStreamedIn(int vehicleid, int forplayerid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("IsVehicleStreamedIn");
	cell params[] = {
		2 * 4,
		vehicleid,
		forplayerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehiclePos(int vehicleid, float *x, float *y, float *z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehiclePos");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehiclePos(int vehicleid, float x, float y, float z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehiclePos");
	cell params[] = {
		4 * 4,
		vehicleid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleZAngle(int vehicleid, float *z_angle) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleZAngle");
	FakeAmxHeapObject z_angle_;
	cell params[] = {
		2 * 4,
		vehicleid,
		z_angle_.address()
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	*z_angle = z_angle_.GetAsFloat();
	return ret;

}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleRotationQuat(int vehicleid, float *w, float *x, float *y, float *z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleRotationQuat");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*w = w_.GetAsFloat();
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT float SAMPGDK_CALL GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleDistanceFromPoint");
	cell params[] = {
		4 * 4,
		vehicleid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	cell ret = FakeAmx::CallNative(native, params);
	return amx_ctof(ret);
}


SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleZAngle(int vehicleid, float z_angle) {
	static AMX_NATIVE native = Natives::GetNativeWarn("IsVehicleStreamedIn");
	cell params[] = {
		2 * 4,
		vehicleid,
		amx_ftoc(z_angle)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleParamsForPlayer");
	cell params[] = {
		4 * 4,
		vehicleid,
		playerid,
		objective,
		doorslocked
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ManualVehicleEngineAndLights() {
	static AMX_NATIVE native = Natives::GetNativeWarn("ManualVehicleEngineAndLights");
	return FakeAmx::CallNativeBool(native, 0);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleParamsEx(int vehicleid, bool engine, int lights, int alarm, int doors,
	int bonnet, int boot, int objective)
{
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleParamsEx");
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
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleParamsEx(int vehicleid, int *engine, int *lights, int *alarm, int *doors,
	int *bonnet, int *boot, int *objective)
{
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleParamsEx");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*engine = engine_.Get();
	*lights = lights_.Get();
	*alarm  = alarm_.Get();
	*doors  = doors_.Get();
	*bonnet = bonnet_.Get();
	*engine = boot_.Get();
	*engine = objective_.Get();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleToRespawn(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleToRespawn");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL LinkVehicleToInterior(int vehicleid, int interiorid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("LinkVehicleToInterior");
	cell params[] = {
		2 * 4,
		vehicleid,
		interiorid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AddVehicleComponent(int vehicleid, int componentid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("AddVehicleComponent");
	cell params[] = {
		2 * 4,
		vehicleid,
		componentid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RemoveVehicleComponent(int vehicleid, int componentid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("RemoveVehicleComponent");
	cell params[] = {
		2 * 4,
		vehicleid,
		componentid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ChangeVehicleColor(int vehicleid, int color1, int color2) {
	static AMX_NATIVE native = Natives::GetNativeWarn("ChangeVehicleColor");
	cell params[] = {
		3 * 4,
		vehicleid,
		color1,
		color2
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ChangeVehiclePaintjob(int vehicleid, int paintjobid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("ChangeVehiclePaintjob");
	cell params[] = {
		2 * 4,
		vehicleid,
		paintjobid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleHealth(int vehicleid, float health) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleHealth");
	cell params[] = {
		2 * 4,
		vehicleid,
		amx_ftoc(health)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleHealth(int vehicleid, float *health) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleHealth");
	FakeAmxHeapObject health_;
	cell params[] = {
		2 * 4,
		vehicleid,
		health_.address()
	};
	bool ret =FakeAmx::CallNativeBool(native, params);
	*health = health_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachTrailerToVehicle(int trailerid, int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("AttachTrailerToVehicle");
	cell params[] = {
		2 * 4,
		trailerid,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DetachTrailerFromVehicle(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("DetachTrailerFromVehicle");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsTrailerAttachedToVehicle(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("IsTrailerAttachedToVehicle");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleTrailer(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleTrailer");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleNumberPlate(int vehicleid, const char *numberplate) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleNumberPlate");
	FakeAmxHeapObject numberplate_(numberplate);
	cell params[] = {
		2 * 4,
		vehicleid,
		numberplate_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleModel(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleModel");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleComponentInSlot(int vehicleid, int slot) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleComponentInSlot");
	cell params[] = {
		2 * 4,
		vehicleid,
		slot
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetVehicleComponentType(int component) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleComponentType");
	cell params[] = {
		1 * 4,
		component
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RepairVehicle(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("RepairVehicle");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleVelocity(int vehicleid, float *x, float *y, float *z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleVelocity");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleVelocity(int vehicleid, float x, float y, float z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleVelocity");
	cell params[] = {
		4 * 4,
		vehicleid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleAngularVelocity(int vehicleid, float x, float y, float z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleAngularVelocity");
	cell params[] = {
		4 * 4,
		vehicleid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleDamageStatus(int vehicleid, int *panels, int *doors, int *lights, int *tires) {
	static AMX_NATIVE native =Natives::GetNativeWarn("GetVehicleDamageStatus");
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
	bool ret = FakeAmx::CallNativeBool(native, params);
	*panels = panels_.Get();
	*doors  = doors_.Get();
	*lights = lights_.Get();
	*tires  = tires_.Get();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires) {
	static AMX_NATIVE native = Natives::GetNativeWarn("UpdateVehicleDamageStatus");
	cell params[] = {
		5 * 4,
		vehicleid,
		amx_ftoc(panels),
		amx_ftoc(doors),
		amx_ftoc(lights),
		amx_ftoc(tires)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetVehicleVirtualWorld(int vehicleid, int worldid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("SetVehicleVirtualWorld");
	cell params[] = {
		2 * 4,
		vehicleid,
		worldid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleVirtualWorld(int vehicleid) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleVirtualWorld");
	cell params[] = {
		1 * 4,
		vehicleid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetVehicleModelInfo(int model, int infotype, float *x, float *y, float *z) {
	static AMX_NATIVE native = Natives::GetNativeWarn("GetVehicleModelInfo");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		5 * 4,
		model,
		infotype,
		x_.address(),
		y_.address(),
		z_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
}