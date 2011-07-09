#ifndef SAMP_SAMP_H
#define SAMP_SAMP_H

#include <string>

#include "plugin/amx/amx.h"

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

// Player GUI Dialog
#define DIALOG_STYLE_MSGBOX    (0)
#define DIALOG_STYLE_INPUT     (1)
#define DIALOG_STYLE_LIST      (2)

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

bool SendClientMessage(int playerid, long color, const std::string &message);
bool SendClientMessageToAll(long color, const std::string &message);
bool SendPlayerMessageToPlayer(int playerid, int senderid, const std::string &message);
bool SendPlayerMessageToAll(int senderid, const std::string &message);
bool SendDeathMessage(int killer, int killee, int weapon);
bool GameTextForAll(const std::string &text, long time, int style);
bool GameTextForPlayer(int playerid, const std::string &text, long time, int style);

long GetTickCount();
int GetMaxPlayers();

bool SetGameModeText(const std::string &text);
bool SetTeamCount(int count);
bool AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
bool AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
bool AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2);
bool AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2, long respawn_delay);
bool AddStaticPickup(int model, int type, float X, float Y, float Z, long virtualworld = 0);
bool CreatePickup(int model, int type, float X, float Y, float Z, long virtualworld = 0);
bool DestroyPickup(int pickup);
bool ShowNameTags(int show);
bool ShowPlayerMarkers(int mode);
bool GameModeExit();
bool SetWorldTime(int hour);

#if 0
native GetWeaponName(weaponid, const weapon[], len);
native EnableTirePopping(enable);
native AllowInteriorWeapons(allow);
native SetWeather(weatherid);
native SetGravity(float gravity);
native AllowAdminTeleport(allow);
native SetDeathDropAmount(amount);
native CreateExplosion(float X, float Y, float Z, type, float Radius);
native EnableZoneNames(enable);
native UsePlayerPedAnims();        // Will cause the players to use CJ running/walking animations
native DisableInteriorEnterExits();  // will disable all interior enter/exits in the game.
native SetNameTagDrawDistance(float distance); // Distance at which nametags will start rendering on the client.
native DisableNameTagLOS(); // Disables the nametag Line-Of-Sight checking
native LimitGlobalChatRadius(float chat_radius);
native LimitPlayerMarkerRadius(float marker_radius);

// Npc
native ConnectNPC(name[], script[]);
native IsPlayerNPC(playerid);

// Admin
native IsPlayerAdmin(playerid);
native Kick(playerid);
native Ban(playerid);
native BanEx(playerid, const reason[]);
native SendRconCommand(command[]);
native GetServerVarAsString(const varname[], buffer[], len);
native GetServerVarAsInt(const varname[]);
native GetServerVarAsBool(const varname[]);

// Menu
native Menu:CreateMenu(const title[], columns, float x, float y, float col1width, float col2width = 0.0);
native DestroyMenu(Menu:menuid);
native AddMenuItem(Menu:menuid, column, const menutext[]);
native SetMenuColumnHeader(Menu:menuid, column, const columnheader[]);
native ShowMenuForPlayer(Menu:menuid, playerid);
native HideMenuForPlayer(Menu:menuid, playerid);
native IsValidMenu(Menu:menuid);
native DisableMenu(Menu:menuid);
native DisableMenuRow(Menu:menuid, row);
native Menu:GetPlayerMenu(playerid);

// Text Draw
native Text:TextDrawCreate(float x, float y, text[]);
native TextDrawDestroy(Text:text);
native TextDrawLetterSize(Text:text, float x, float y);
native TextDrawTextSize(Text:text, float x, float y);
native TextDrawAlignment(Text:text, alignment);
native TextDrawColor(Text:text, color);
native TextDrawUseBox(Text:text, use);
native TextDrawBoxColor(Text:text, color);
native TextDrawSetShadow(Text:text, size);
native TextDrawSetOutline(Text:text, size);
native TextDrawBackgroundColor(Text:text, color);
native TextDrawFont(Text:text, font);
native TextDrawSetProportional(Text:text, set);
native TextDrawShowForPlayer(playerid, Text:text);
native TextDrawHideForPlayer(playerid, Text:text);
native TextDrawShowForAll(Text:text);
native TextDrawHideForAll(Text:text);
native TextDrawSetString(Text:text, string[]);

// Gang Zones
native GangZoneCreate(float minx, float miny, float maxx, float maxy);
native GangZoneDestroy(zone);
native GangZoneShowForPlayer(playerid, zone, color);
native GangZoneShowForAll(zone, color);
native GangZoneHideForPlayer(playerid, zone);
native GangZoneHideForAll(zone);
native GangZoneFlashForPlayer(playerid, zone, flashcolor);
native GangZoneFlashForAll(zone, flashcolor);
native GangZoneStopFlashForPlayer(playerid, zone);
native GangZoneStopFlashForAll(zone);

// Global 3D Text Labels
native Text3D:Create3DTextLabel(text[], color, float X, float Y, float Z, float DrawDistance, virtualworld, testLOS=0);
native Delete3DTextLabel(Text3D:id);
native Attach3DTextLabelToPlayer(Text3D:id, playerid, float OffsetX, float OffsetY, float OffsetZ);
native Attach3DTextLabelToVehicle(Text3D:id, vehicleid, float OffsetX, float OffsetY, float OffsetZ);
native Update3DTextLabelText(Text3D:id, color, text[]);

// Per-player 3D Text Labels
native PlayerText3D:CreatePlayer3DTextLabel(playerid, text[], color, float X, float Y, float Z, float DrawDistance, attachedplayer=INVALID_PLAYER_ID, attachedvehicle=INVALID_VEHICLE_ID, testLOS=0);
native DeletePlayer3DTextLabel(playerid, PlayerText3D:id);
native UpdatePlayer3DTextLabelText(playerid, PlayerText3D:id, color, text[]);
#endif

} // namespace samp

#endif