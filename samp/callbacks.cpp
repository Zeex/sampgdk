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

#if defined WIN32 || defined _WIN32
    #include <malloc.h>
#endif

#include "callbacks.h"
#include "eventhandler.h"
#include "wrapper.h"

#include "plugin/amx/amx.h"

static cell GetCellFromStack(AMX *amx, int index) {
    AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
    unsigned char *data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
    return *reinterpret_cast<cell*>(data + amx->stk + sizeof(cell)*index);
}

static std::string GetStringFromStack(AMX *amx, int index) {
    cell amxAddr = GetCellFromStack(amx, index);
    char *str;
    amx_StrParam(amx, amxAddr, str);
    return std::string(str);
}

namespace samp { 

void Callbacks::Initialize() {
    using samp::Wrapper;

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

cell Callbacks::OnGameModeInit(AMX *amx) {
    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        cur->OnGameModeInit();
        cur = cur->GetNext();
    }
    return 1;
}

cell Callbacks::OnGameModeExit(AMX *amx) {
    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        cur->OnGameModeExit();
        cur = cur->GetNext();
    }
    return 1;
}

cell Callbacks::OnPlayerConnect(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerConnect(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerDisconnect(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int reason = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerDisconnect(playerid, reason)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerSpawn(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerSpawn(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerDeath(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int killerid = GetCellFromStack(amx, 1);
    int reason = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerDeath(playerid, killerid, reason)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleSpawn(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleSpawn(vehicleid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleDeath(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int killerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleDeath(vehicleid, killerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerText(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    std::string text = GetStringFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerText(playerid, text)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerCommandText(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    std::string cmdtext = GetStringFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerCommandText(playerid, cmdtext)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 0;
}

cell Callbacks::OnPlayerRequestClass(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int classid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerRequestClass(playerid, classid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerEnterVehicle(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    bool ispassenger = GetCellFromStack(amx, 2) != 0;

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerExitVehicle(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerExitVehicle(playerid, vehicleid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerStateChange(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int newstate = GetCellFromStack(amx, 1);
    int oldstate = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerStateChange(playerid, newstate, oldstate)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerEnterCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerEnterCheckpoint(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerLeaveCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerLeaveCheckpoint(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerEnterRaceCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerEnterRaceCheckpoint(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerLeaveRaceCheckpoint(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerLeaveRaceCheckpoint(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnRconCommand(AMX *amx) {
    std::string cmd = GetStringFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnRconCommand(cmd)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 0;
}

cell Callbacks::OnPlayerRequestSpawn(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerRequestSpawn(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnObjectMoved(AMX *amx) {
    int objectid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnObjectMoved(objectid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerObjectMoved(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int objectid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerObjectMoved(playerid, objectid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerPickUpPickup(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int pickupid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerPickUpPickup(playerid, pickupid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleMod(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int componentid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleMod(playerid, vehicleid, componentid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnEnterExitModShop(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    bool enterexit = GetCellFromStack(amx, 1) != 0;
    int interiorid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnEnterExitModShop(playerid, enterexit, interiorid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehiclePaintjob(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int paintjobid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehiclePaintjob(playerid, vehicleid, paintjobid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleRespray(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int vehicleid = GetCellFromStack(amx, 1);
    int color1 = GetCellFromStack(amx, 2);
    int color2 = GetCellFromStack(amx, 3);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleRespray(playerid, vehicleid, color1, color2)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleDamageStatusUpdate(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int playerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleDamageStatusUpdate(vehicleid, playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerSelectedMenuRow(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int row = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerSelectedMenuRow(playerid, row)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerExitedMenu(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerExitedMenu(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerInteriorChange(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int newinteriorid = GetCellFromStack(amx, 1);
    int oldinteriorid = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerKeyStateChange(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int newkeys = GetCellFromStack(amx, 1);
    int oldkeys = GetCellFromStack(amx, 2);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerKeyStateChange(playerid, newkeys, oldkeys)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnRconLoginAttempt(AMX *amx) {
    std::string ip = GetStringFromStack(amx, 0);
    std::string password = GetStringFromStack(amx, 1);
    bool success = GetCellFromStack(amx, 2) != 0;

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnRconLoginAttempt(ip, password, success)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerUpdate(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerUpdate(playerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerStreamIn(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerStreamIn(playerid, forplayerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerStreamOut(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerStreamOut(playerid, forplayerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleStreamIn(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleStreamIn(vehicleid, forplayerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnVehicleStreamOut(AMX *amx) {
    int vehicleid = GetCellFromStack(amx, 0);
    int forplayerid = GetCellFromStack(amx, 1);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnVehicleStreamOut(vehicleid, forplayerid)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnDialogResponse(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int dialogid = GetCellFromStack(amx, 1);
    bool response = GetCellFromStack(amx, 2) != 0;
    int listitem = GetCellFromStack(amx, 3);
    std::string inputtext = GetStringFromStack(amx, 4);

    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnDialogResponse(playerid, dialogid, response, listitem, inputtext)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

cell Callbacks::OnPlayerClickPlayer(AMX *amx) {
    int playerid = GetCellFromStack(amx, 0);
    int clickedplayerid = GetCellFromStack(amx, 1);
    int source = GetCellFromStack(amx, 2);
    
    EventHandler *cur = EventHandler::GetFirstEventHandler();
    while (cur != 0) {
        if (!cur->OnPlayerClickPlayer(playerid, clickedplayerid, source)) {
            break;
        }
        cur = cur->GetNext();
    }

    return 1;
}

} // namespace samp 
