#ifndef SAMP_SAMP_H
#define SAMP_SAMP_H

#include <string>

// This header includes all other headers
#include "eventhandler.h"
#include "logprintf.h"
#include "objects.h"
#include "players.h"
#include "vehicles.h"
#include "wrapper.h"
#include "plugin/plugin.h"

namespace samp {

// Limits and internal constants
#define MAX_PLAYER_NAME            (24)
#define MAX_PLAYERS                (500)
#define MAX_VEHICLES               (2000)
#define INVALID_PLAYER_ID          (0xFFFF)
#define INVALID_VEHICLE_ID         (0xFFFF)
#define NO_TEAM                    (255)
#define MAX_OBJECTS                (400)
#define INVALID_OBJECT_ID          (0xFFFF)
#define MAX_GANG_ZONES             (1024)
#define MAX_TEXT_DRAWS             (2048)
#define MAX_MENUS                  (128)
#define MAX_3DTEXT_GLOBAL          (1024)
#define MAX_3DTEXT_PLAYER          (1024)
#define MAX_PICKUPS                (2048)
#define INVALID_MENU               (0xFF)
#define INVALID_TEXT_DRAW          (0xFFFF)
#define INVALID_GANG_ZONE          (-1)
#define INVALID_3DTEXT_ID          (0xFFFF)

// Util
bool SendClientMessage(int playerid, long color, const std::string &message);
void SendClientMessageToAll(long color, const std::string &message);
bool SendPlayerMessageToPlayer(int playerid, int senderid, const std::string &message);
bool SendPlayerMessageToAll(int senderid, const std::string &message);
bool SendDeathMessage(int killer, int killee, int weapon);
bool GameTextForAll(const std::string &text, long time, int style);
bool GameTextForPlayer(int playerid, const std::string &text, long time, int style);
long GetTickCount();
int GetMaxPlayers();

// Game
void SetGameModeText(const std::string &text);
void SetTeamCount(long count);
int AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
int AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
int AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2);
int AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay);
int AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld = 0);
int CreatePickup(int model, int type, float x, float y, float z, long virtualworld = 0);
bool DestroyPickup(int pickup);
void ShowNameTags(bool show);
void ShowPlayerMarkers(bool mode);
void GameModeExit();
bool SetWorldTime(short hour);
std::string GetWeaponName(int weaponid);
void EnableTirePopping(bool enable);
void AllowInteriorWeapons(bool allow);
void SetWeather(int weatherid);
void SetGravity(float gravity);
void AllowAdminTeleport(bool allow);
void SetDeathDropAmount(long amount);
void CreateExplosion(float x, float y, float z, short type, float radius);
void EnableZoneNames(bool enable);
void UsePlayerPedAnims();        // Will cause the players to use CJ running/walking animations
void DisableInteriorEnterExits();  // will disable all interior enter/exits in the game.
void SetNameTagDrawDistance(float distance); // Distance at which nametags will start rendering on the client.
void DisableNameTagLOS(); // Disables the nametag Line-Of-Sight checking
void LimitGlobalChatRadius(float chat_radius);
void LimitPlayerMarkerRadius(float marker_radius);

// Npc
bool ConnectNPC(const std::string &name, const std::string &script);
bool IsPlayerNPC(int playerid);

// Admin
bool IsPlayerAdmin(int playerid);
bool Kick(int playerid);
bool Ban(int playerid);
bool BanEx(int playerid, const std::string &reason);
void SendRconCommand(const std::string &command);
std::string GetServerVarAsString(const std::string &varname);
int GetServerVarAsInt(const std::string &varname);
bool GetServerVarAsBool(const std::string &varname);

// Menu
int CreateMenu(const std::string &title, int columns, float x, float y, float col1width, float col2width = 0.0f);
bool DestroyMenu(int menuid);
int AddMenuItem(int menuid, int column, const std::string &menutext);
bool SetMenuColumnHeader(int menuid, int column, const std::string &columnheader);
bool ShowMenuForPlayer(int menuid, int playerid);
bool HideMenuForPlayer(int menuid, int playerid);
bool IsValidMenu(int menuid);
bool DisableMenu(int menuid);
bool DisableMenuRow(int menuid, int row);
int GetPlayerMenu(int playerid);

// Text Draw
int TextDrawCreate(float x, float y, const std::string &text);
bool TextDrawDestroy(int text);
bool TextDrawLetterSize(int text, float x, float y);
bool TextDrawTextSize(int text, float x, float y);
bool TextDrawAlignment(int text, int alignment);
bool TextDrawColor(int text, long color);
bool TextDrawUseBox(int text, bool use);
bool TextDrawBoxColor(int text, long color);
bool TextDrawSetShadow(int text, int size);
bool TextDrawSetOutline(int text, int size);
bool TextDrawBackgroundColor(int text, long color);
bool TextDrawFont(int text, int font);
bool TextDrawSetProportional(int text, bool set);
bool TextDrawShowForPlayer(int playerid, int text);
bool TextDrawHideForPlayer(int playerid, int text);
bool TextDrawShowForAll(int text);
bool TextDrawHideForAll(int text);
bool TextDrawSetString(int text, const std::string &string);

// Gang Zones
int GangZoneCreate(float minx, float miny, float maxx, float maxy);
bool GangZoneDestroy(int zone);
bool GangZoneShowForPlayer(int playerid, int zone, long color);
bool GangZoneShowForAll(int zone, long color);
bool GangZoneHideForPlayer(int playerid, int zone);
bool GangZoneHideForAll(int zone);
bool GangZoneFlashForPlayer(int playerid, int zone, long flashcolor);
bool GangZoneFlashForAll(int zone, long flashcolor);
bool GangZoneStopFlashForPlayer(int playerid, int zone);
bool GangZoneStopFlashForAll(int zone);

// Global 3D Text Labels
int Create3DTextLabel(const std::string &text, long color, float x, float y, float z, float DrawDistance, long virtualworld, bool testLOS = false);
bool Delete3DTextLabel(int id);
bool Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ);
bool Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ);
bool Update3DTextLabelText(int id, long color, const std::string &text);

// Per-player 3D Text Labels
int CreatePlayer3DTextLabel(int playerid, const std::string &text, long color, float x, float y, float z, float DrawDistance, int attachedplayer = INVALID_PLAYER_ID, int attachedvehicle = INVALID_VEHICLE_ID, bool testLOS = false);
bool DeletePlayer3DTextLabel(int playerid, int id);
bool UpdatePlayer3DTextLabelText(int playerid, int id, long color, const std::string &text);

// Player GUI Dialog
#define DIALOG_STYLE_MSGBOX    (0)
#define DIALOG_STYLE_INPUT     (1)
#define DIALOG_STYLE_LIST      (2)

bool ShowPlayerDialog(int playerid, int dialogid, int style, const std::string &caption, const std::string &info, const std::string &button1, const std::string &button2);

// States
#define PLAYER_STATE_NONE                        (0)
#define PLAYER_STATE_ONFOOT                      (1)
#define PLAYER_STATE_DRIVER                      (2)
#define PLAYER_STATE_PASSENGER                   (3)
#define PLAYER_STATE_EXIT_VEHICLE                (4) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER        (5) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER     (6) // (used internally)
#define PLAYER_STATE_WASTED                      (7)
#define PLAYER_STATE_SPAWNED                     (8)
#define PLAYER_STATE_SPECTATING                  (9)

// Marker modes used by ShowPlayerMarkers()
#define PLAYER_MARKERS_MODE_OFF                  (0)
#define PLAYER_MARKERS_MODE_GLOBAL               (1)
#define PLAYER_MARKERS_MODE_STREAMED             (2)

// Weapons
#define WEAPON_BRASSKNUCKLE                (1)
#define WEAPON_GOLFCLUB                    (2)
#define WEAPON_NITESTICK                   (3)
#define WEAPON_KNIFE                       (4)
#define WEAPON_BAT                         (5)
#define WEAPON_SHOVEL                      (6)
#define WEAPON_POOLSTICK                   (7)
#define WEAPON_KATANA                      (8)
#define WEAPON_CHAINSAW                    (9)
#define WEAPON_DILDO                       (10)
#define WEAPON_DILDO2                      (11)
#define WEAPON_VIBRATOR                    (12)
#define WEAPON_VIBRATOR2                   (13)
#define WEAPON_FLOWER                      (14)
#define WEAPON_CANE                        (15)
#define WEAPON_GRENADE                     (16)
#define WEAPON_TEARGAS                     (17)
#define WEAPON_MOLTOV                      (18)
#define WEAPON_COLT45                      (22)
#define WEAPON_SILENCED                    (23)
#define WEAPON_DEAGLE                      (24)
#define WEAPON_SHOTGUN                     (25)
#define WEAPON_SAWEDOFF                    (26)
#define WEAPON_SHOTGSPA                    (27)
#define WEAPON_UZI                         (28)
#define WEAPON_MP5                         (29)
#define WEAPON_AK47                        (30)
#define WEAPON_M4                          (31)
#define WEAPON_TEC9                        (32)
#define WEAPON_RIFLE                       (33)
#define WEAPON_SNIPER                      (34)
#define WEAPON_ROCKETLAUNCHER              (35)
#define WEAPON_HEATSEEKER                  (36)
#define WEAPON_FLAMETHROWER                (37)
#define WEAPON_MINIGUN                     (38)
#define WEAPON_SATCHEL                     (39)
#define WEAPON_BOMB                        (40)
#define WEAPON_SPRAYCAN                    (41)
#define WEAPON_FIREEXTINGUISHER            (42)
#define WEAPON_CAMERA                      (43)
#define WEAPON_PARACHUTE                   (46)
#define WEAPON_VEHICLE                     (49)
#define WEAPON_DROWN                       (53)
#define WEAPON_COLLISION                   (54)

// Keys
#define KEY_ACTION                (1)
#define KEY_CROUCH                (2)
#define KEY_FIRE                  (4)
#define KEY_SPRINT                (8)
#define KEY_SECONDARY_ATTACK      (16)
#define KEY_JUMP                  (32)
#define KEY_LOOK_RIGHT            (64)
#define KEY_HANDBRAKE             (128)
#define KEY_LOOK_LEFT             (256)
#define KEY_SUBMISSION            (512)
#define KEY_LOOK_BEHIND           (512)
#define KEY_WALK                  (1024)
#define KEY_ANALOG_UP             (2048)
#define KEY_ANALOG_DOWN           (4096)
#define KEY_ANALOG_LEFT           (8192)
#define KEY_ANALOG_RIGHT          (16384)

#define KEY_UP                    (-128)
#define KEY_DOWN                  (128)
#define KEY_LEFT                  (-128)
#define KEY_RIGHT                 (128)

#define CLICK_SOURCE_SCOREBOARD   (0)

} // namespace samp

#endif