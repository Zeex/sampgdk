// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <string>

#ifdef _WIN32 
    #include <malloc.h>
#endif

#include <sampgdk/amxplugin.h>
#include <sampgdk/eventhandler.h>
#include <sampgdk/wrapper.h>

#include "callbacks.h"

using sampgdk::EventHandler;

static cell GetCellFromStack(AMX *amx, int index) {
    AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
    unsigned char *data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
    return *reinterpret_cast<cell*>(data + amx->stk + sizeof(cell)*index);
}

static std::string GetStringFromStack(AMX *amx, int index) {
    cell *physAddr;
    amx_GetAddr(amx, GetCellFromStack(amx, index), &physAddr);
    int length = 0;
    amx_StrLen(physAddr, &length);
    return std::string(physAddr, physAddr + length);
}

static cell AMXAPI OnGameModeInit(AMX *amx) {
    EventHandler *cur = EventHandler::GetFirstEventHandler();

    while (cur != 0) {
        cur->OnGameModeInit();
        cur = cur->GetNext();
    }

    return 1;
}

static cell AMXAPI OnGameModeExit(AMX *amx) {
    EventHandler *cur = EventHandler::GetFirstEventHandler();

    while (cur != 0) {
        cur->OnGameModeExit();
        cur = cur->GetNext();
    }

    return 1;
}

static cell AMXAPI OnPlayerConnect(AMX *amx) {
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

static cell AMXAPI OnPlayerDisconnect(AMX *amx) {
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

static cell AMXAPI OnPlayerSpawn(AMX *amx) {
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

static cell AMXAPI OnPlayerDeath(AMX *amx) {
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

static cell AMXAPI OnVehicleSpawn(AMX *amx) {
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

static cell AMXAPI OnVehicleDeath(AMX *amx) {
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

static cell AMXAPI OnPlayerText(AMX *amx) {
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

static cell AMXAPI OnPlayerCommandText(AMX *amx) {
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

static cell AMXAPI OnPlayerRequestClass(AMX *amx) {
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

static cell AMXAPI OnPlayerEnterVehicle(AMX *amx) {
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

static cell AMXAPI OnPlayerExitVehicle(AMX *amx) {
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

static cell AMXAPI OnPlayerStateChange(AMX *amx) {
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

static cell AMXAPI OnPlayerEnterCheckpoint(AMX *amx) {
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

static cell AMXAPI OnPlayerLeaveCheckpoint(AMX *amx) {
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

static cell AMXAPI OnPlayerEnterRaceCheckpoint(AMX *amx) {
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

static cell AMXAPI OnPlayerLeaveRaceCheckpoint(AMX *amx) {
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

static cell AMXAPI OnRconCommand(AMX *amx) {
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

static cell AMXAPI OnPlayerRequestSpawn(AMX *amx) {
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

static cell AMXAPI OnObjectMoved(AMX *amx) {
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

static cell AMXAPI OnPlayerObjectMoved(AMX *amx) {
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

static cell AMXAPI OnPlayerPickUpPickup(AMX *amx) {
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

static cell AMXAPI OnVehicleMod(AMX *amx) {
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

static cell AMXAPI OnEnterExitModShop(AMX *amx) {
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

static cell AMXAPI OnVehiclePaintjob(AMX *amx) {
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

static cell AMXAPI OnVehicleRespray(AMX *amx) {
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

static cell AMXAPI OnVehicleDamageStatusUpdate(AMX *amx) {
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

static cell AMXAPI OnUnoccupiedVehicleUpdate(AMX *amx) {
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

static cell AMXAPI OnPlayerSelectedMenuRow(AMX *amx) {
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

static cell AMXAPI OnPlayerExitedMenu(AMX *amx) {
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

static cell AMXAPI OnPlayerInteriorChange(AMX *amx) {
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

static cell AMXAPI OnPlayerKeyStateChange(AMX *amx) {
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

static cell AMXAPI OnRconLoginAttempt(AMX *amx) {
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

static cell AMXAPI OnPlayerUpdate(AMX *amx) {
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

static cell AMXAPI OnPlayerStreamIn(AMX *amx) {
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

static cell AMXAPI OnPlayerStreamOut(AMX *amx) {
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

static cell AMXAPI OnVehicleStreamIn(AMX *amx) {
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

static cell AMXAPI OnVehicleStreamOut(AMX *amx) {
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

static cell AMXAPI OnDialogResponse(AMX *amx) {
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

static cell AMXAPI OnPlayerClickPlayer(AMX *amx) {
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

namespace sampgdk { 

void HookSampCallbacks() {
    using sampgdk::Wrapper;

    Wrapper::GetInstance()->SetPublicHook("OnGameModeInit", PublicHook(OnGameModeInit, 0));
    Wrapper::GetInstance()->SetPublicHook("OnGameModeExit", PublicHook(OnGameModeExit, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerConnect", PublicHook(OnPlayerConnect, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerDisconnect", PublicHook(OnPlayerDisconnect, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerSpawn", PublicHook(OnPlayerSpawn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerDeath", PublicHook(OnPlayerDeath, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleSpawn", PublicHook(OnVehicleSpawn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleDeath", PublicHook(OnVehicleDeath, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerText", PublicHook(OnPlayerText, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerCommandText", PublicHook(OnPlayerCommandText, 1));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerRequestClass", PublicHook(OnPlayerRequestClass, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerEnterVehicle", PublicHook(OnPlayerEnterVehicle, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerExitVehicle", PublicHook(OnPlayerExitVehicle, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerStateChange", PublicHook(OnPlayerStateChange, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerEnterCheckpoint", PublicHook(OnPlayerEnterCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerLeaveCheckpoint", PublicHook(OnPlayerLeaveCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerEnterRaceCheckpoint", PublicHook(OnPlayerEnterRaceCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerLeaveRaceCheckpoint", PublicHook(OnPlayerLeaveRaceCheckpoint, 0));
    Wrapper::GetInstance()->SetPublicHook("OnRconCommand", PublicHook(OnRconCommand, 1));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerRequestSpawn", PublicHook(OnPlayerRequestSpawn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnObjectMoved", PublicHook(OnObjectMoved, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerObjectMoved", PublicHook(OnPlayerObjectMoved, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerPickUpPickup", PublicHook(OnPlayerPickUpPickup, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleMod", PublicHook(OnVehicleMod, 0));
    Wrapper::GetInstance()->SetPublicHook("OnEnterExitModShop", PublicHook(OnEnterExitModShop, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehiclePaintjob", PublicHook(OnVehiclePaintjob, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleRespray", PublicHook(OnVehicleRespray, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleDamageStatusUpdate", PublicHook(OnVehicleDamageStatusUpdate, 0));
    Wrapper::GetInstance()->SetPublicHook("OnUnoccupiedVehicleUpdate", PublicHook(OnUnoccupiedVehicleUpdate, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerSelectedMenuRow", PublicHook(OnPlayerSelectedMenuRow, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerExitedMenu", PublicHook(OnPlayerExitedMenu, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerInteriorChange", PublicHook(OnPlayerInteriorChange, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerKeyStateChange", PublicHook(OnPlayerKeyStateChange, 0));
    Wrapper::GetInstance()->SetPublicHook("OnRconLoginAttempt", PublicHook(OnRconLoginAttempt, 1)); // TODO: the 1 is just a guess, need a test
    Wrapper::GetInstance()->SetPublicHook("OnPlayerUpdate", PublicHook(OnPlayerUpdate, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerStreamIn", PublicHook(OnPlayerStreamIn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerStreamOut", PublicHook(OnPlayerStreamOut, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleStreamIn", PublicHook(OnVehicleStreamIn, 0));
    Wrapper::GetInstance()->SetPublicHook("OnVehicleStreamOut", PublicHook(OnVehicleStreamOut, 0));
    Wrapper::GetInstance()->SetPublicHook("OnDialogResponse", PublicHook(OnDialogResponse, 0));
    Wrapper::GetInstance()->SetPublicHook("OnPlayerClickPlayer", PublicHook(OnPlayerClickPlayer, 0));
}

} // namespace sampgdk 

