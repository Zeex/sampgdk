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

using sampgdk::EventHandler;

#define DEFINE_EVENT_LONG(event, handler, br) \
	static cell SAMPGDK_CALL handler(AMX *amx); \
    static volatile SampCallback event(#handler, handler, br); \
	static cell SAMPGDK_CALL handler(AMX *amx)

#define DEFINE_EVENT(event, br) \
    DEFINE_EVENT_LONG(event, On##event, br)

struct SampCallback {
    SampCallback(const char *name, sampgdk::Wrapper::PublicHandler handler, cell badReturn) {
        sampgdk::Wrapper::GetInstance()->SetPublicHook(name, handler, badReturn);
    }
};

static cell GetCellFromStack(AMX *amx, int index) {
    AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
    unsigned char *data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
    return *reinterpret_cast<cell*>(data + amx->stk + sizeof(cell)*index);
}

static float GetFloatFromStack(AMX *amx, int index) {
    cell c = GetCellFromStack(amx, index);
    return amx_ctof(c);
}

static std::string GetStringFromStack(AMX *amx, int index) {
    cell *physAddr;
    amx_GetAddr(amx, GetCellFromStack(amx, index), &physAddr);
    int length = 0;
    amx_StrLen(physAddr, &length);
    return std::string(physAddr, physAddr + length);
}

DEFINE_EVENT(GameModeInit, 0) {
    EventHandler *cur = EventHandler::GetFirstEventHandler();

    while (cur != 0) {
        cur->OnGameModeInit();
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(GameModeExit, 0) {
    EventHandler *cur = EventHandler::GetFirstEventHandler();

    while (cur != 0) {
        cur->OnGameModeExit();
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerConnect, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerConnect(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerDisconnect, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int reason = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerDisconnect(playerid, reason)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerSpawn, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerSpawn(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerDeath, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int killerid = GetCellFromStack(amx, 1);
    int reason = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerDeath(playerid, killerid, reason)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleSpawn, 0) {
    int vehicleid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleSpawn(vehicleid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleDeath, 0) {
    int vehicleid = GetCellFromStack(amx, 0);
    int killerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleDeath(vehicleid, killerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerText, 0) {
    int playerid = GetCellFromStack(amx, 0);
    std::string text = GetStringFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerText(playerid, text.c_str())) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerCommandText, 1) {
    int playerid = GetCellFromStack(amx, 0);
    std::string cmdtext = GetStringFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (cur->OnPlayerCommandText(playerid, cmdtext.c_str())) {
            return 1;
        }
        cur = cur->GetNext();
    }

    return 0;
}

DEFINE_EVENT(PlayerRequestClass, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int classid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerRequestClass(playerid, classid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerEnterVehicle, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    bool ispassenger = GetCellFromStack(amx, 2) != 0;

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerExitVehicle, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerExitVehicle(playerid, vehicleid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerStateChange, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int newstate = GetCellFromStack(amx, 1);
    int oldstate = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerStateChange(playerid, newstate, oldstate)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerEnterCheckpoint, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerEnterCheckpoint(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerLeaveCheckpoint, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerLeaveCheckpoint(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerEnterRaceCheckpoint, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerEnterRaceCheckpoint(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerLeaveRaceCheckpoint, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerLeaveRaceCheckpoint(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(RconCommand, 1) {
    std::string cmd = GetStringFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (cur->OnRconCommand(cmd.c_str())) {
            return 1;
        }
        cur = cur->GetNext();
    }

    return 0;
}

DEFINE_EVENT(PlayerRequestSpawn, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerRequestSpawn(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(ObjectMoved, 0) {
    int objectid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnObjectMoved(objectid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerObjectMoved, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int objectid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerObjectMoved(playerid, objectid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerPickUpPickup, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int pickupid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerPickUpPickup(playerid, pickupid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleMod, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int componentid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleMod(playerid, vehicleid, componentid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(EnterExitModShop, 0) {
    int playerid = GetCellFromStack(amx, 0);
    bool enterexit = GetCellFromStack(amx, 1) != 0;
    int interiorid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnEnterExitModShop(playerid, enterexit, interiorid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehiclePaintjob, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int paintjobid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehiclePaintjob(playerid, vehicleid, paintjobid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleRespray, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int color1 = GetCellFromStack(amx, 2);
    int color2 = GetCellFromStack(amx, 3);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleRespray(playerid, vehicleid, color1, color2)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleDamageStatusUpdate, 0) {
    int vehicleid = GetCellFromStack(amx, 0);
    int playerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleDamageStatusUpdate(vehicleid, playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(UnoccupiedVehicleUpdate, 0) {
    int vehicleid = GetCellFromStack(amx, 0);
    int playerid = GetCellFromStack(amx, 1);
    int passenger_seat = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerSelectedMenuRow, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int row = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerSelectedMenuRow(playerid, row)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerExitedMenu, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerExitedMenu(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerInteriorChange, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int newinteriorid = GetCellFromStack(amx, 1);
    int oldinteriorid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerKeyStateChange, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int newkeys = GetCellFromStack(amx, 1);
    int oldkeys = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerKeyStateChange(playerid, newkeys, oldkeys)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(RconLoginAttempt, 1) {
    std::string ip = GetStringFromStack(amx, 0);
    std::string password = GetStringFromStack(amx, 1);
    bool success = GetCellFromStack(amx, 2) != 0;

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (cur->OnRconLoginAttempt(ip.c_str(), password.c_str(), success)) {
            return 1;
        }
        cur = cur->GetNext();
    }

    return 0;
}

DEFINE_EVENT(PlayerUpdate, 0) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerUpdate(playerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerStreamIn, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerStreamIn(playerid, forplayerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerStreamOut, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerStreamOut(playerid, forplayerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleStreamIn, 0) {
    int vehicleid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleStreamIn(vehicleid, forplayerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(VehicleStreamOut, 0) {
    int vehicleid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleStreamOut(vehicleid, forplayerid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(DialogResponse, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int dialogid = GetCellFromStack(amx, 1);
    bool response = GetCellFromStack(amx, 2) != 0;
    int listitem = GetCellFromStack(amx, 3);
    std::string inputtext = GetStringFromStack(amx, 4);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnDialogResponse(playerid, dialogid, response, listitem, inputtext.c_str())) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerClickPlayer, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int clickedplayerid = GetCellFromStack(amx, 1);
    int source = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerClickPlayer(playerid, clickedplayerid, source)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerTakeDamage, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int issuerid = GetCellFromStack(amx, 1);
    float amount = GetFloatFromStack(amx, 2);
    int weaponid = GetCellFromStack(amx, 3);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerTakeDamage(playerid, issuerid, amount, weaponid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}

DEFINE_EVENT(PlayerGiveDamage, 0) {
    int playerid = GetCellFromStack(amx, 0);
    int damagedid = GetCellFromStack(amx, 1);
    float amount = GetFloatFromStack(amx, 2);
    int weaponid = GetCellFromStack(amx, 3);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerGiveDamage(playerid, damagedid, amount, weaponid)) {
            return 0;
        }
        cur = cur->GetNext();
    }

    return 1;
}
