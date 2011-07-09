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

void SendClientMessageToAll(long color, const std::string &message) {
    static auto native = Wrapper::GetInstance()->GetNative("SendClientMessageToAll");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        PARAMS(2),
        color,
        reinterpret_cast<cell>(message_.c_str())
    };
    native(&::fakeAmx, params);
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

void SetGameModeText(const std::string &text) {
    static auto native = Wrapper::GetInstance()->GetNative("SetGameModeText");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        PARAMS(1), 
        reinterpret_cast<cell>(text_.c_str())
    };
    native(&::fakeAmx, params);
}

void SetTeamCount(int count) {
    static auto native = Wrapper::GetInstance()->GetNative("SetTeamCount");
    cell params[] = {
        PARAMS(1), 
        count
    };
    native(&::fakeAmx, params);
}

int AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
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

int AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
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

int AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
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

int AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
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

int AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld) {
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

int CreatePickup(int model, int type, float x, float y, float z, long virtualworld) {
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

void ShowNameTags(int show) {
    static auto native = Wrapper::GetInstance()->GetNative("ShowNameTags");
    cell params[] = {
        PARAMS(1),
        show
    };
    native(&::fakeAmx, params);
}

void ShowPlayerMarkers(int mode) {
    static auto native = Wrapper::GetInstance()->GetNative("ShowPlayerMarkers");
    cell params[] = {
        PARAMS(1),
        mode
    };
    native(&::fakeAmx, params);
}

void GameModeExit() {
    static auto native = Wrapper::GetInstance()->GetNative("GameModeExit");
    cell params[] = {
        PARAMS(0)
    };
    native(&::fakeAmx, params);
}

bool SetWorldTime(int hour) {
    static auto native = Wrapper::GetInstance()->GetNative("SetWorldTime");
    cell params[] = {
        PARAMS(1),
        hour
    };
    return native(&::fakeAmx, params);
}

std::string GetWeaponName(int weaponid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetWeaponName");
    cstring name_(50, '\0'); // TODO: make max. length unlimited
    cell params[] = {
        PARAMS(3),
        weaponid,
        reinterpret_cast<cell>(name_.data()),
        name_.length()
    };
    native(&::fakeAmx, params);
    return std::string(name_.begin(), name_.end());
}

void EnableTirePopping(bool enable) {
    static auto native = Wrapper::GetInstance()->GetNative("EnableTirePopping");
    cell params[] = {
        PARAMS(1),
        enable
    };
    native(&::fakeAmx, params);
}

void AllowInteriorWeapons(bool allow) {
    static auto native = Wrapper::GetInstance()->GetNative("AllowInteriorWeapons");
    cell params[] = {
        PARAMS(1),
        allow
    };
    native(&::fakeAmx, params);
}

void SetWeather(int weatherid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetWeather");
    cell params[] = {
        PARAMS(1),
        weatherid
    };
    native(&::fakeAmx, params);
}

void SetGravity(float gravity) {
    static auto native = Wrapper::GetInstance()->GetNative("SetGravity");
    cell params[] = {
        PARAMS(1),
        amx_ftoc(gravity)
    };
    native(&::fakeAmx, params);
}

void AllowAdminTeleport(bool allow) {
    static auto native = Wrapper::GetInstance()->GetNative("AllowAdminTeleport");
    cell params[] = {
        PARAMS(1),
        allow
    };
    native(&::fakeAmx, params);
}

void SetDeathDropAmount(long amount) {
    static auto native = Wrapper::GetInstance()->GetNative("SetDeathDropAmount");
    cell params[] = {
        PARAMS(1),
        amount
    };
    native(&::fakeAmx, params);
}

void CreateExplosion(float x, float y, float z, short type, float radius) {
    static auto native = Wrapper::GetInstance()->GetNative("CreateExplosion");
    cell params[] = {
        PARAMS(5), 
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        type,
        amx_ftoc(radius)
    };
    native(&::fakeAmx, params);
}

void EnableZoneNames(bool enable) {
    static auto native = Wrapper::GetInstance()->GetNative("EnableZoneNames");
    cell params[] = {
        PARAMS(1),
        enable
    };
    native(&::fakeAmx, params);
}

void UsePlayerPedAnims() {
    static auto native = Wrapper::GetInstance()->GetNative("UsePlayerPedAnims");
    native(&::fakeAmx, 0);
}

void DisableInteriorEnterExits() {
    static auto native = Wrapper::GetInstance()->GetNative("DisableInteriorEnterExits");
    native(&::fakeAmx, 0);
}

void SetNameTagDrawDistance(float distance) {
    static auto native = Wrapper::GetInstance()->GetNative("SetNameTagDrawDistance");
    cell params[] = {
        PARAMS(1),
        amx_ftoc(distance)
    };
    native(&::fakeAmx, params);
}

void DisableNameTagLOS() {
    static auto native = Wrapper::GetInstance()->GetNative("DisableNameTagLOS");
    native(&::fakeAmx, 0);
}

void LimitGlobalChatRadius(float chat_radius) {
    static auto native = Wrapper::GetInstance()->GetNative("LimitGlobalChatRadius");
    cell params[] = {
        PARAMS(1),
        amx_ftoc(chat_radius)
    };
    native(&::fakeAmx, params);
}

void LimitPlayerMarkerRadius(float marker_radius) {
    static auto native = Wrapper::GetInstance()->GetNative("LimitPlayerMarkerRadius");
    cell params[] = {
        PARAMS(1),
        amx_ftoc(marker_radius)
    };
    native(&::fakeAmx, params);
}

bool ConnectNPC(const std::string &name, const std::string &script) {
    static auto native = Wrapper::GetInstance()->GetNative("ConnectNPC");
    cstring name_(name.begin(), name.end());
    cstring script_(script.begin(), script.end());
    cell params[] = {
        PARAMS(2),
        reinterpret_cast<cell>(name_.c_str()),
        reinterpret_cast<cell>(script_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool IsPlayerNPC(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerNPC");
    cell params[] = {
        PARAMS(1),
        playerid
    };
    return native(&::fakeAmx, params);
}

bool IsPlayerAdmin(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerAdmin");
    cell params[] = {
        PARAMS(1),
        playerid
    };
    return native(&::fakeAmx, params);
}

bool Kick(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("Kick");
    cell params[] = {
        PARAMS(1),
        playerid
    };
    return native(&::fakeAmx, params);
}

bool Ban(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("Ban");
    cell params[] = {
        PARAMS(1),
        playerid
    };
    return native(&::fakeAmx, params);
}

bool BanEx(int playerid, const std::string &reason) {
    static auto native = Wrapper::GetInstance()->GetNative("BanEx");
    cell params[] = {
        PARAMS(1),
        playerid
    };
    return native(&::fakeAmx, params);
}

void SendRconCommand(const std::string &command) {
    static auto native = Wrapper::GetInstance()->GetNative("SendRconCommand");
    cstring command_(command.begin(), command.end());
    cell params[] = {
        PARAMS(1),
        reinterpret_cast<cell>(command_.c_str()),
    };
    native(&::fakeAmx, params);
}

std::string GetServerVarAsString(const std::string &varname) {
    static auto native = Wrapper::GetInstance()->GetNative("GetServerVarAsString");
    cstring varname_(varname.begin(), varname.end());
    cstring var_(128, '\0'); // TODO: make max. length unlimited
    cell params[] = {
        PARAMS(3),
        reinterpret_cast<cell>(varname_.c_str()),
        reinterpret_cast<cell>(var_.data()),
        var_.length()
    };
    native(&::fakeAmx, params);
    return std::string(var_.begin(), var_.end());
}

int GetServerVarAsInt(const std::string &varname) {
    static auto native = Wrapper::GetInstance()->GetNative("GetServerVarAsInt");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        PARAMS(1),
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool GetServerVarAsBool(const std::string &varname) {
    static auto native = Wrapper::GetInstance()->GetNative("GetServerVarAsBool");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        PARAMS(1),
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

} // namespace samp