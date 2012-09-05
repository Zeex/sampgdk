/* Copyright (C) 2011-2012 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_A_SAMP_H
#define SAMPGDK_A_SAMP_H

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/plugin.h>

typedef void (SAMPGDK_CALL *TimerCallback)(int timerid, void *param);

#include <sampgdk/generated/a_samp.h>

#ifdef __cplusplus

#include <cstddef>
#include <string>

template<std::size_t N> inline bool GetNetworkStats(char (&retstr)[N]) {
	return GetNetworkStats(retstr, N);
}
template<std::size_t N> inline bool GetPlayerNetworkStats(int playerid, char (&retstr)[N]) {
	return GetPlayerNetworkStats(playerid, retstr, N);
}
template<std::size_t N> inline bool GetPlayerVersion(int playerid, char (&version)[N]) {
	return GetPlayerVersion(playerid, version, N);
}
template<std::size_t N> inline bool GetWeaponName(int weaponid, char (&name)[N]) {
	return GetWeaponName(weaponid, name, N);
}

class Menu {
public:
	Menu(int menuid) : id_(menuid) {}
	virtual ~Menu() {}

	int GetId() const { return id_; }
	operator int() const { return id_; }	

	static Menu Create(const char *title, int columns, float x, float y, float col1width, float col2width = 0.0) 
		{ return ::CreateMenu(title, columns, x, y, col1width, col2width); }
	static Menu Create(const std::string &title, int columns, float x, float y, float col1width, float col2width) 
		{ return ::CreateMenu(title.c_str(), columns, x, y, col1width, col2width); }

	bool Destroy() const
		{ return ::DestroyMenu(id_); }
	int AddItem(int column, const char *menutext) const
		{ return ::AddMenuItem(id_, column, menutext); }
	int AddItem(int column, const std::string &menutext) const
		{ return ::AddMenuItem(id_, column, menutext.c_str()); }
	bool SetColumnHeader(int column, const char *columnheader) const
		{ return ::SetMenuColumnHeader(id_, column, columnheader); }
	bool SetColumnHeader(int column, const std::string &columnheader) const
		{ return ::SetMenuColumnHeader(id_, column, columnheader.c_str()); }
	bool ShowForPlayer(int playerid) const
		{ return ::ShowMenuForPlayer(id_, playerid); }
	bool HideForPlayer(int playerid) const
		{ return ::HideMenuForPlayer(id_, playerid); }
	bool IsValid() const
		{ return ::IsValidMenu(id_); }
	bool Disable() const
		{ return ::DisableMenu(id_); }
	bool DisableRow(int row) const
		{ return ::DisableMenuRow(id_, row); }

private:
	const int id_;
};

class TextDraw {
public:
	TextDraw(int text) : id_(text) {}
	virtual ~TextDraw() {}

	int GetId() const { return id_; }
	operator int() const { return id_; }

	static TextDraw Create(float x, float y, const char *text) 
		{ return ::TextDrawCreate(x, y, text); }
	static TextDraw Create(float x, float y, const std::string &text) 
		{ return ::TextDrawCreate(x, y, text.c_str()); }

	bool Destroy() const 
		{ return ::TextDrawDestroy(id_); }
	bool SetLetterSize(float x, float y) const
		{ return ::TextDrawLetterSize(id_, x, y); }
	bool SetTextSize(float x, float y) const 
		{ return ::TextDrawTextSize(id_, x, y); }
	bool SetAlignment(int alignment) const 
		{ return ::TextDrawAlignment(id_, alignment); }
	bool SetColor(int color) const 
		{ return ::TextDrawColor(id_, color); }
	bool SetBackgroundColor(int color) const 
		{ return ::TextDrawBackgroundColor(id_, color); }
	bool UseBox(bool use) const 
		{ return ::TextDrawUseBox(id_, use); }
	bool SetBoxColor(int color) const 
		{ return ::TextDrawBoxColor(id_, color); }
	bool SetShadow(int size) const 
		{ return ::TextDrawSetShadow(id_, size); }
	bool SetOutline(int size) const 
		{ return ::TextDrawSetOutline(id_, size); }
	bool SetFont(int font) const 
		{ return ::TextDrawFont(id_, font); }
	bool SetProportional(bool set) const 
		{ return ::TextDrawSetProportional(id_, set); }
	bool SetString(const char *string) const
		{ return ::TextDrawSetString(id_, string); }
	bool SetString(const std::string &string) const
		{ return ::TextDrawSetString(id_, string.c_str()); }
	bool SetSelectable(bool set) const
		{ return ::TextDrawSetSelectable(id_, set); }
	bool ShowForPlayer(int playerid) const 
		{ return ::TextDrawShowForPlayer(playerid, id_); }
	bool HideForPlayer(int playerid) const 
		{ return ::TextDrawHideForPlayer(playerid, id_); }
	bool ShowForAll() const 
		{ return ::TextDrawShowForAll(id_); }
	bool HideForAll() const
		{ return ::TextDrawHideForAll(id_); }

private:
	const int id_;
};

class GangZone {
public:
	GangZone(int zone) : id_(zone) {}
	virtual ~GangZone() {}

	int GetId() const { return id_; }
	operator int() const { return id_; }

	static GangZone Create(float minx, float miny, float maxx, float maxy) 
		{ return ::GangZoneCreate(minx, miny, maxx, maxy); }

	bool Destroy() const
		{ return ::GangZoneDestroy(id_); }
	bool ShowForPlayer(int playerid, int color) const
		{ return ::GangZoneShowForPlayer(playerid, id_, color); }
	bool ShowForAll(int color) const
		{ return ::GangZoneShowForAll(id_, color); }
	bool HideForPlayer(int playerid) const
		{ return ::GangZoneHideForPlayer(playerid, id_); }
	bool HideForAll() const
		{ return ::GangZoneHideForAll(id_); }
	bool FlashForPlayer(int playerid, int flashcolor) const
		{ return ::GangZoneFlashForPlayer(playerid, id_, flashcolor); }
	bool FlashForAll(int flashcolor) const
		{ return ::GangZoneFlashForAll(id_, flashcolor); }
	bool StopFlashForPlayer(int playerid) const
		{ return ::GangZoneStopFlashForPlayer(playerid, id_); }
	bool StopFlashForAll() const
		{ return ::GangZoneStopFlashForAll(id_); }

private:
	const int id_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_SAMP_H */
