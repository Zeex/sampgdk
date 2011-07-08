#include "jump.h"
#include "plugin.h"
#include "samp.h"

#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>

#ifdef _MSC_VER
#pragma 
#endif

extern void *pAMXFunctions;

static uint32_t amx_Register_addr;
static unsigned char amx_Register_code[5];

static int my_amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, size_t number) {
    // Restore old amx_Register's code so we can invoke it
    memcpy(reinterpret_cast<void*>(::amx_Register_addr), ::amx_Register_code, 5);

    // Store natives in our global container
    for (size_t i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
        SAMPWrapper::GetInstance().SetNative(nativelist[i].name, nativelist[i].func);
    }

    // Call the original function
    int retVal = amx_Register(amx, nativelist, number);

    // Set jump again to catch further calls
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), my_amx_Register, ::amx_Register_code);

    return retVal;
}

static AMX_HEADER fakeAmxHeader = {
    0, // size
    AMX_MAGIC, // magic
    MIN_FILE_VERSION, // file_version
    MIN_AMX_VERSION, // amx_version
    0, // flags
    0, // defsize
    0, // cod
    -reinterpret_cast<int32_t>(&fakeAmxHeader), // dat
    0, // hea 
    0, // stp
    0, // cip
    0, // publics
    0, // natives
    0, // libraries
    0, // pubvars
    0, // tags
    0, // nametable
};

static AMX fakeAmx = {
    reinterpret_cast<unsigned char*>(&fakeAmxHeader), // base
    0, // data
    amx_Callback, // callback
    0, // debug hook
    0, // cip
    0, // frm
    0, // hea
    0, // hlw
    0, // stk
    std::numeric_limits<int32_t>::max(), // stp
    0, // flags
    0, // usertags
    0, // userdata
    AMX_ERR_NONE, // error
    0, // paramcount 
    0, // pri
    0, // alt
    0, // reset_stk
    0, // reset_hea
    0, // sysreq_d
};

static std::runtime_error NoSuchNative(const std::string &nativeName) {
    return std::runtime_error("No such native function: " + nativeName);
}

SAMPWrapper::SAMPWrapper() {}

SAMPWrapper &SAMPWrapper::GetInstance() {
    static SAMPWrapper w;
    return w;
}

void SAMPWrapper::Initialize(void **ppPluginData) {
    pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

    ::amx_Register_addr = reinterpret_cast<uint32_t>(
        (static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_Register]);
    // Replace first 5 bytes of amx_Register's code with "JMP my_amx_Register"
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), my_amx_Register, ::amx_Register_code);
}

void SAMPWrapper::SetNative(const std::string &name, AMX_NATIVE native) {
    if (!name.empty()) {
        natives_[name] = native;
    }
}
    
AMX_NATIVE SAMPWrapper::GetNative(const std::string &name) const {
    auto it = natives_.find(name);
    if (it != natives_.end()) {
        return it->second;
    } 
    return 0;
}

// All natives share the same code
#define BEGIN_NATIVE \
    static AMX_NATIVE _native = SAMPWrapper::GetInstance().GetNative(__FUNCTION__);\
    if (_native != 0) {

#define END_NATIVE \
        return _native(&::fakeAmx, params);\
    } else {\
        throw NoSuchNative(__FUNCTION__);\
    }\

// Returns params[0] for n parameters
#define PARAMS(n) ((n) * sizeof(cell))

#ifdef _MSC_VER
    #pragma warning(push)
    // forcing value to bool 'true' or 'false' (performance warning)
    #pragma warning(disable: 4800)
#endif

bool SendClientMessage(int playerid, long color, const std::string &message) {
    BEGIN_NATIVE
        cellstring message_(message.begin(), message.end());
        cell params[] = {
            PARAMS(3),
            playerid,
            color,
            reinterpret_cast<cell>(message_.c_str())
        };
    END_NATIVE
}

bool SendClientMessageToAll(long color, const std::string &message) {
    BEGIN_NATIVE
        cellstring message_(message.begin(), message.end());
        cell params[] = {
            PARAMS(2),
            color,
            reinterpret_cast<cell>(message_.c_str())
        };
    END_NATIVE
}

bool SendPlayerMessageToPlayer(int playerid, int senderid, const std::string &message) {
    BEGIN_NATIVE
        cellstring message_(message.begin(), message.end());
        cell params[] = {
            PARAMS(3),
            playerid,
            senderid,
            reinterpret_cast<cell>(message_.c_str())
        };
    END_NATIVE
}

bool SendPlayerMessageToAll(int senderid, const std::string &message) {
    BEGIN_NATIVE
        cellstring message_(message.begin(), message.end());
        cell params[] = {
            PARAMS(2),
            senderid,
            reinterpret_cast<cell>(message_.c_str())
        };
    END_NATIVE
}

bool SendDeathMessage(int killer, int killee, int weapon) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(3),
            killer,
            killee,
            weapon
        };
    END_NATIVE
}

bool GameTextForAll(const std::string &text, long time, int style) {
    BEGIN_NATIVE
        cellstring text_(text.begin(), text.end());
        cell params[] = {
            PARAMS(3),
            reinterpret_cast<cell>(text_.c_str()),
            time,
            style
        };
    END_NATIVE
}

bool GameTextForPlayer(int playerid, const std::string &text, long time, int style) {
    BEGIN_NATIVE
        cellstring text_(text.begin(), text.end());
        cell params[] = {
            PARAMS(4),
            playerid,
            reinterpret_cast<cell>(text_.c_str()),
            time,
            style
        };
    END_NATIVE
}

long GetTickCount() {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(0)
        };
    END_NATIVE
}

int GetMaxPlayers() {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(0)
        };
    END_NATIVE
}

bool SetGameModeText(const std::string &text) {
    BEGIN_NATIVE
        cellstring text_(text.begin(), text.end());
        cell params[] = {
            PARAMS(1), 
            reinterpret_cast<cell>(text_.c_str())
        };
    END_NATIVE
}

bool SetTeamCount(int count) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(1), 
            count
        };
    END_NATIVE
}

bool AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) 
{
    BEGIN_NATIVE
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
    END_NATIVE
}

bool AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
    BEGIN_NATIVE
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
    END_NATIVE
}

bool AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2)
{
    BEGIN_NATIVE
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
    END_NATIVE
}

bool AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2, long respawn_delay) 
{
    BEGIN_NATIVE
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
    END_NATIVE
}

bool AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(6), 
            model,
            type,
            amx_ftoc(x),
            amx_ftoc(y),
            amx_ftoc(z),
            virtualworld
        };
    END_NATIVE
}

bool CreatePickup(int model, int type, float x, float y, float z, long virtualworld) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(6), 
            model,
            type,
            amx_ftoc(x),
            amx_ftoc(y),
            amx_ftoc(z),
            virtualworld
        };
    END_NATIVE
}

bool DestroyPickup(int pickup) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(1),
            pickup
        };
    END_NATIVE
}

bool ShowNameTags(int show) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(1),
            show
        };
    END_NATIVE
}

bool ShowPlayerMarkers(int mode) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(1),
            mode
        };
    END_NATIVE
}

bool GameModeExit() {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(0)
        };
    END_NATIVE
}

bool SetWorldTime(int hour) {
    BEGIN_NATIVE
        cell params[] = {
            PARAMS(1),
            hour
        };
    END_NATIVE
}

#ifdef _MSC_VER
    #pragma warning(pop)
#endif