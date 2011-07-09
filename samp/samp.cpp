#include "fakeamx.h"
#include "jump.h"
#include "samp.h"
#include "wrapper.h"

#define PARAMS(n) ((n) * sizeof(cell))

#ifdef _MSC_VER
    #pragma warning(push)
    // forcing value to bool 'true' or 'false' (performance warning)
    #pragma warning(disable: 4800)
#endif

namespace samp {

bool SendClientMessage(int playerid, long color, const std::string &message) {
    static auto native = Wrapper::GetInstance()->GetNative("SendClientMessage");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        PARAMS(3),
        playerid,
        color,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SendClientMessageToAll(long color, const std::string &message) {
    static auto native = Wrapper::GetInstance()->GetNative("SendClientMessageToAll");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        PARAMS(2),
        color,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SendPlayerMessageToPlayer(int playerid, int senderid, const std::string &message) {
    static auto native = Wrapper::GetInstance()->GetNative("SendPlayerMessageToPlayer");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        PARAMS(3),
        playerid,
        senderid,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SendPlayerMessageToAll(int senderid, const std::string &message) {
    static auto native = Wrapper::GetInstance()->GetNative("SendPlayerMessageToAll");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        PARAMS(2),
        senderid,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SendDeathMessage(int killer, int killee, int weapon) {
    static auto native = Wrapper::GetInstance()->GetNative("SendDeathMessage");
    cell params[] = {
        PARAMS(3),
        killer,
        killee,
        weapon
    };
    return native(&::fakeAmx, params);
}

bool GameTextForAll(const std::string &text, long time, int style) {
    static auto native = Wrapper::GetInstance()->GetNative("GameTextForAll");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        PARAMS(3),
        reinterpret_cast<cell>(text_.c_str()),
        time,
        style
    };
    return native(&::fakeAmx, params);
}

bool GameTextForPlayer(int playerid, const std::string &text, long time, int style) {
    static auto native = Wrapper::GetInstance()->GetNative("GameTextForPlayer");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        PARAMS(4),
        playerid,
        reinterpret_cast<cell>(text_.c_str()),
        time,
        style
    };
    return native(&::fakeAmx, params);
}

long GetTickCount() {
    static auto native = Wrapper::GetInstance()->GetNative("GetTickCount");
    return native(&::fakeAmx, 0);
}

int GetMaxPlayers() {
    static auto native = Wrapper::GetInstance()->GetNative("GetMaxPlayers");
    return native(&::fakeAmx, 0);
}

bool SetGameModeText(const std::string &text) {
    static auto native = Wrapper::GetInstance()->GetNative("SetGameModeText");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        PARAMS(1), 
        reinterpret_cast<cell>(text_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SetTeamCount(int count) {
    static auto native = Wrapper::GetInstance()->GetNative("SetTeamCount");
    cell params[] = {
        PARAMS(1), 
        count
    };
    return native(&::fakeAmx, params);
}

bool AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) 
{
    static auto native = Wrapper::GetInstance()->GetNative("AddPlayerClass");
    cell params[] = {
        PARAMS(11), 
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        weapon1,
        weapon1_ammo,
        weapon2,
        weapon2_ammo,
        weapon3,
        weapon3_ammo
    };
    return native(&::fakeAmx, params);
}

bool AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
    static auto native = Wrapper::GetInstance()->GetNative("AddPlayerClassEx");
    cell params[] = {
        PARAMS(12), 
        teamid,
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        weapon1,
        weapon1_ammo,
        weapon2,
        weapon2_ammo,
        weapon3,
        weapon3_ammo
    };
    return native(&::fakeAmx, params);
}

bool AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2)
{
    static auto native = Wrapper::GetInstance()->GetNative("AddStaticVehicle");
    cell params[] = {
        PARAMS(7), 
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        color1,
        color2
    };
    return native(&::fakeAmx, params);
}

bool AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2, long respawn_delay) 
{
    static auto native = Wrapper::GetInstance()->GetNative("AddStaticVehicleEx");
    cell params[] = {
        PARAMS(8), 
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        color1,
        color2,
        respawn_delay
    };
    return native(&::fakeAmx, params);
}

bool AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld) {
    static auto native = Wrapper::GetInstance()->GetNative("AddStaticPickup");
    cell params[] = {
        PARAMS(6), 
        model,
        type,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        virtualworld
    };
    return native(&::fakeAmx, params);
}

bool CreatePickup(int model, int type, float x, float y, float z, long virtualworld) {
    static auto native = Wrapper::GetInstance()->GetNative("CreatePickup");
    cell params[] = {
        PARAMS(6), 
        model,
        type,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        virtualworld
    };
    return native(&::fakeAmx, params);
}

bool DestroyPickup(int pickup) {
    static auto native = Wrapper::GetInstance()->GetNative("DestroyPickup");
    cell params[] = {
        PARAMS(1),
        pickup
    };
    return native(&::fakeAmx, params);
}

bool ShowNameTags(int show) {
    static auto native = Wrapper::GetInstance()->GetNative("ShowNameTags");
    cell params[] = {
        PARAMS(1),
        show
    };
    return native(&::fakeAmx, params);
}

bool ShowPlayerMarkers(int mode) {
    static auto native = Wrapper::GetInstance()->GetNative("ShowPlayerMarkers");
    cell params[] = {
        PARAMS(1),
        mode
    };
    return native(&::fakeAmx, params);
}

bool GameModeExit() {
    static auto native = Wrapper::GetInstance()->GetNative("GameModeExit");
    cell params[] = {
        PARAMS(0)
    };
    return native(&::fakeAmx, params);
}

bool SetWorldTime(int hour) {
    static auto native = Wrapper::GetInstance()->GetNative("SetWorldTime");
    cell params[] = {
        PARAMS(1),
        hour
    };
    return native(&::fakeAmx, params);
}

} // namespace samp