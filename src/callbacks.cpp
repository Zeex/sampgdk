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

#include <string>

#include <sampgdk/amxplugin.h>
#include <sampgdk/eventhandler.h>
#include <sampgdk/wrapper.h>

template<typename T> struct StackArg {
	// MSVc 2008 required a Get implementation
	static T Get(AMX *amx, int index) {
		return T(); 
	}
};

template<> struct StackArg<cell> {
	static cell Get(AMX *amx, int index) {
		AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
		unsigned char *data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
		return *reinterpret_cast<cell*>(data + amx->stk + sizeof(cell)*index);
	}
};

template<> struct StackArg<bool> {
	static bool Get(AMX *amx, int index) {
		return StackArg<cell>::Get(amx, index) != 0;
	}
};

template<> struct StackArg<std::string> {
	static std::string Get(AMX *amx, int index) {
		cell *physAddr;
		amx_GetAddr(amx, StackArg<cell>::Get(amx, index), &physAddr);
		int length = 0;
		amx_StrLen(physAddr, &length);
		return std::string(physAddr, physAddr + length);
	}
};

template<> struct StackArg<float> {
	static float Get(AMX *amx, int index) {
		cell c = StackArg<cell>::Get(amx, index);
		return amx_ctof(c);
	}
};

struct Event {
	Event(const char *name, sampgdk::Wrapper::PublicHandler handler, cell badReturn) {
		sampgdk::Wrapper::GetInstance().SetPublicHook(name, handler, badReturn);
	}
};

#define EVENT_BEGIN(event_, on_event_, badRet_)\
	static cell SAMPGDK_CALL on_event_(AMX *amx);\
	static volatile Event event_(#on_event_, on_event_, badRet_);\
	static cell SAMPGDK_CALL on_event_(AMX *amx) {\
		sampgdk::EventHandler *eh_ = sampgdk::EventHandler::GetFirstEventHandler();\
		while (eh_ != 0) {

#define EVENT_END(badRet_)\
			eh_ = eh_->GetNext();\
		}\
		return cell(!badRet_);\
	}
		
#define ARG(type_, index_)\
	StackArg<type_>::Get(amx, index_)

#define EVENT_0_(event_, on_event_, badRet_)\
	EVENT_BEGIN(event_, on_event_, badRet_)\
	eh_->on_event_();\
	EVENT_END(badRet_);

#define EVENT_1_(event_, on_event_, badRet_, t1_)\
	EVENT_BEGIN(event_, on_event_, badRet_)\
	eh_->on_event_(ARG(t1_, 0));\
	EVENT_END(badRet_);

#define EVENT_2_(event_, on_event_, badRet_, t1_, t2_)\
	EVENT_BEGIN(event_, on_event_, badRet_)\
	eh_->on_event_(ARG(t1_, 0), ARG(t2_, 1));\
	EVENT_END(badRet_);

#define EVENT_3_(event_, on_event_, badRet_, t1_, t2_, t3_)\
	EVENT_BEGIN(event_, on_event_, badRet_)\
	eh_->on_event_(ARG(t1_, 0), ARG(t2_, 1), ARG(t3_, 2));\
	EVENT_END(badRet_);

#define EVENT_4_(event_, on_event_, badRet_, t1_, t2_, t3_, t4_)\
	EVENT_BEGIN(event_, on_event_, badRet_)\
	eh_->on_event_(ARG(t1_, 0), ARG(t2_, 1), ARG(t3_, 2), ARG(t4_, 3));\
	EVENT_END(badRet_);

#define EVENT_5_(event_, on_event_, badRet_, t1_, t2_, t3_, t4_, t5_)\
	EVENT_BEGIN(event_, on_event_, badRet_)\
	eh_->on_event_(ARG(t1_, 0), ARG(t2_, 1), ARG(t3_, 2), ARG(t4_, 3), ARG(t5_, 4));\
	EVENT_END(badRet_);

#define EVENT_0(event_, badRet_) EVENT_0_(event_, On##event_, badRet_)
#define EVENT_1(event_, badRet_, t1_) EVENT_1_(event_, On##event_, badRet_, t1_)
#define EVENT_2(event_, badRet_, t1_, t2_) EVENT_2_(event_, On##event_, badRet_, t1_, t2_)
#define EVENT_3(event_, badRet_, t1_, t2_, t3_) EVENT_3_(event_, On##event_, badRet_, t1_, t2_, t3_)
#define EVENT_4(event_, badRet_, t1_, t2_, t3_, t4_) EVENT_4_(event_, On##event_, badRet_, t1_, t2_, t3_, t4_)
#define EVENT_5(event_, badRet_, t1_, t2_, t3_, t4_, t5_) EVENT_5_(event_, On##event_, badRet_, t1_, t2_, t3_, t4_, t5_)

EVENT_0(GameModeInit, 0);
EVENT_0(GameModeExit, 0);
EVENT_1(PlayerConnect, 0, int);
EVENT_2(PlayerDisconnect, 0, int, int);
EVENT_1(PlayerSpawn, 0, int);
EVENT_3(PlayerDeath, 0, int, int, int);
EVENT_1(VehicleSpawn, 0, int);
EVENT_2(VehicleDeath, 0, int, int);
EVENT_2(PlayerText, 0, int, std::string);
EVENT_2(PlayerCommandText, 1, int, std::string);
EVENT_2(PlayerRequestClass, 0, int, int);
EVENT_3(PlayerEnterVehicle, 0, int, int, bool);
EVENT_2(PlayerExitVehicle, 0, int, int);
EVENT_3(PlayerStateChange, 0, int, int, int);
EVENT_1(PlayerEnterCheckpoint, 0, int);
EVENT_1(PlayerLeaveCheckpoint, 0, int);
EVENT_1(PlayerEnterRaceCheckpoint, 0, int);
EVENT_1(PlayerLeaveRaceCheckpoint, 0, int);
EVENT_1(RconCommand, 1, std::string);
EVENT_1(PlayerRequestSpawn, 0, int);
EVENT_1(ObjectMoved, 0, int);
EVENT_2(PlayerObjectMoved, 0, int, int);
EVENT_2(PlayerPickUpPickup, 0, int, int);
EVENT_3(VehicleMod, 0, int, int, int);
EVENT_3(EnterExitModShop, 0, int, bool, int);
EVENT_3(VehiclePaintjob, 0, int, int, int);
EVENT_4(VehicleRespray, 0, int, int, int, int);
EVENT_2(VehicleDamageStatusUpdate, 0, int, int);
EVENT_3(UnoccupiedVehicleUpdate, 0, int, int, int);
EVENT_2(PlayerSelectedMenuRow, 0, int, int);
EVENT_1(PlayerExitedMenu, 0, int);
EVENT_3(PlayerInteriorChange, 0, int, int, int);
EVENT_3(PlayerKeyStateChange, 0, int, int, int);
EVENT_3(RconLoginAttempt, 1, std::string, std::string, bool);
EVENT_1(PlayerUpdate, 0, int);
EVENT_2(PlayerStreamIn, 0, int, int);
EVENT_2(PlayerStreamOut, 0, int, int);
EVENT_2(VehicleStreamIn, 0, int, int);
EVENT_2(VehicleStreamOut, 0, int, int);
EVENT_5(DialogResponse, 0, int, int, bool, int, std::string);
EVENT_3(PlayerClickPlayer, 0, int, int, int);
EVENT_4(PlayerTakeDamage, 0, int, int, float, int);
EVENT_4(PlayerGiveDamage, 0, int, int, float, int);
