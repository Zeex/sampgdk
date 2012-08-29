#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#define COLOR_GREY    0xAFAFAFAA
#define COLOR_GREEN   0x33AA33AA
#define COLOR_RED     0xAA3333AA
#define COLOR_YELLOW  0xFFFF00AA
#define COLOR_WHITE   0xFFFFFFAA

#define PocketMoney   50000 // Amount player recieves on spawn.

typedef void (*logprintf_t)(const char *format, ...);

static logprintf_t logprintf;

int CashScoreOld;
int iSpawnSet[MAX_PLAYERS];

float gRandomPlayerSpawns[][3] = {
	{1958.3783f,1343.1572f,15.3746f},
	{2199.6531f,1393.3678f,10.8203f},
	{2483.5977f,1222.0825f,10.8203f},
	{2637.2712f,1129.2743f,11.1797f},
	{2000.0106f,1521.1111f,17.0625f},
	{2024.8190f,1917.9425f,12.3386f},
	{2261.9048f,2035.9547f,10.8203f},
	{2262.0986f,2398.6572f,10.8203f},
	{2244.2566f,2523.7280f,10.8203f},
	{2335.3228f,2786.4478f,10.8203f},
	{2150.0186f,2734.2297f,11.1763f},
	{2158.0811f,2797.5488f,10.8203f},
	{1969.8301f,2722.8564f,10.8203f},
	{1652.0555f,2709.4072f,10.8265f},
	{1564.0052f,2756.9463f,10.8203f},
	{1271.5452f,2554.0227f,10.8203f},
	{1441.5894f,2567.9099f,10.8203f},
	{1480.6473f,2213.5718f,11.0234f},
	{1400.5906f,2225.6960f,11.0234f},
	{1598.8419f,2221.5676f,11.0625f},
	{1318.7759f,1251.3580f,10.8203f},
	{1558.0731f,1007.8292f,10.8125f},
	{-857.0551f,1536.6832f,22.5870f},
	{817.3494f,856.5039f,12.7891f},
	{116.9315f,1110.1823f,13.6094f},
	{-18.8529f,1176.0159f,19.5634f},
	{-315.0575f,1774.0636f,43.6406f},
	{1705.2347f,1025.6808f,10.8203f}
};

float gCopPlayerSpawns[][3] = {
	{2297.1064f,2452.0115f,10.8203f},
	{2297.0452f,2468.6743f,10.8203f}
};

int gActivePlayers[MAX_PLAYERS];
int gLastGaveCash[MAX_PLAYERS];

static void SAMPGDK_CALL MoneyGrubScoreUpdate(int timerid, void *param)
{
	int CashScore;
	char name[MAX_PLAYER_NAME];
	char string[128];
	for(int i=0; i<MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i))
		{
			GetPlayerName(i, name, MAX_PLAYER_NAME);
   			CashScore = GetPlayerMoney(i);
			SetPlayerScore(i, CashScore);
			if (CashScore > CashScoreOld)
			{
				CashScoreOld = CashScore;
				sprintf(string, "$$$ %s is now in the lead $$$", name);
				SendClientMessageToAll(COLOR_YELLOW, string);
			}
		}
	}
}

static void SendPlayerFormattedText(int playerid, const char str[], int define)
{
	char tmpbuf[128];
	sprintf(tmpbuf, str, define);
	SendClientMessage(playerid, 0xFF004040, tmpbuf);
}

static void SendAllFormattedText(int playerid, const char str[], int define)
{
	char tmpbuf[128];
	sprintf(tmpbuf, str, define);
	SendClientMessageToAll(0xFFFF00AA, tmpbuf);
}

static void SetPlayerRandomSpawn(int playerid)
{
	if (iSpawnSet[playerid] == 1)
	{
		int r = rand() % arraysize(gCopPlayerSpawns);
		SetPlayerPos(playerid, gCopPlayerSpawns[r][0], gCopPlayerSpawns[r][1], gCopPlayerSpawns[r][2]); // Warp the player
		SetPlayerFacingAngle(playerid, 270.0f);
	}
	else if (iSpawnSet[playerid] == 0)
	{
		int r = rand() % arraysize(gRandomPlayerSpawns);
		SetPlayerPos(playerid, gRandomPlayerSpawns[r][0], gRandomPlayerSpawns[r][1], gRandomPlayerSpawns[r][2]); // Warp the player
	}
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	GameTextForPlayer(playerid,"~w~SA-MP: ~r~Las Venturas ~g~MoneyGrub", 5000, 5);
	SendPlayerFormattedText(playerid, "Welcome to Las Venturas MoneyGrub, For help type /help.", 0);
	gActivePlayers[playerid]++;
	gLastGaveCash[playerid] = GetTickCount();
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	gActivePlayers[playerid]--;
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext)
{
	char string[128];
	int playermoney;
	char sendername[MAX_PLAYER_NAME];
	char giveplayer[MAX_PLAYER_NAME];
	char *cmd;
	int giveplayerid, moneys;

	// FIXME: const_cast isn't really a good solution
	cmd = strtok(const_cast<char*>(cmdtext), " ");

	if(strcmp(cmd, "/help") == 0) {
		SendPlayerFormattedText(playerid,"Las Venturas Deathmatch: Money Grub Coded By Jax and the SA-MP Team.",0);
		SendPlayerFormattedText(playerid,"Type: /objective : to find out what to do in this gamemode.",0);
		SendPlayerFormattedText(playerid,"Type: /givecash [playerid] [money-amount] to send money to other players.",0);
		SendPlayerFormattedText(playerid,"Type: /tips : to see some tips from the creator of the gamemode.", 0);
		return true;
	}

	if(strcmp(cmd, "/objective") == 0) {
		SendPlayerFormattedText(playerid,"This gamemode is faily open, there's no specific win / endgame conditions to meet.",0);
		SendPlayerFormattedText(playerid,"In LVDM:Money Grub, when you kill a player, you will receive whatever money they have.",0);
		SendPlayerFormattedText(playerid,"Consequently, if you have lots of money, and you die, your killer gets your cash.",0);
		SendPlayerFormattedText(playerid,"However, you're not forced to kill players for money, you can always gamble in the", 0);
		SendPlayerFormattedText(playerid,"Casino's.", 0);
		return true;
	}
	if(strcmp(cmd, "/tips") == 0) {
		SendPlayerFormattedText(playerid,"Spawning with just a desert eagle might sound lame, however the idea of this",0);
		SendPlayerFormattedText(playerid,"gamemode is to get some cash, get better guns, then go after whoever has the",0);
		SendPlayerFormattedText(playerid,"most cash. Once you've got the most cash, the idea is to stay alive(with the",0);
		SendPlayerFormattedText(playerid,"cash intact)until the game ends, simple right?", 0);
		return true;
	}

 	if(strcmp(cmd, "/givecash") == 0) {
		cmd = strtok(NULL, " ");

		if(cmd == 0 || !strlen(cmd)) {
			SendClientMessage(playerid, COLOR_WHITE, "USAGE: /givecash [playerid] [amount]");
			return true;
		}
		giveplayerid = atoi(cmd);

		cmd = strtok(NULL, " ");
		if(cmd == 0 || !strlen(cmd)) {
			SendClientMessage(playerid, COLOR_WHITE, "USAGE: /givecash [playerid] [amount]");
			return true;
		}
 		moneys = atoi(cmd);

		if (IsPlayerConnected(giveplayerid)) {
			GetPlayerName(giveplayerid, giveplayer, MAX_PLAYER_NAME);
			GetPlayerName(playerid, sendername, MAX_PLAYER_NAME);
			playermoney = GetPlayerMoney(playerid);
			if (moneys > 0 && playermoney >= moneys) {
				GivePlayerMoney(playerid, (0 - moneys));
				GivePlayerMoney(giveplayerid, moneys);
				sprintf(string, "You have sent %s(player: %d), $%d.", giveplayer,giveplayerid, moneys);
				SendClientMessage(playerid, COLOR_YELLOW, string);
				sprintf(string, "You have recieved $%d from %s(player: %d).", moneys, sendername, playerid);
				SendClientMessage(giveplayerid, COLOR_YELLOW, string);
				logprintf("%s(playerid:%d) has transfered %d to %s(playerid:%d)",sendername, playerid, moneys, giveplayer, giveplayerid);
			}
			else {
				SendClientMessage(playerid, COLOR_YELLOW, "Invalid transaction amount.");
			}
		}
		else {
			sprintf(string, "%d is not an active player.", giveplayerid);
			SendClientMessage(playerid, COLOR_YELLOW, string);
		}
		return true;
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	GivePlayerMoney(playerid, PocketMoney);
	SetPlayerInterior(playerid,0);
	SetPlayerRandomSpawn(playerid);
	TogglePlayerClock(playerid,1);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason)
{
	int playercash;
	if(killerid == INVALID_PLAYER_ID) {
		SendDeathMessage(INVALID_PLAYER_ID,playerid,reason);
		ResetPlayerMoney(playerid);
	} else {
		SendDeathMessage(killerid,playerid,reason);
		SetPlayerScore(killerid,GetPlayerScore(killerid)+1);
		playercash = GetPlayerMoney(playerid);
		if (playercash > 0)  {
			GivePlayerMoney(killerid, playercash);
			ResetPlayerMoney(playerid);
		}
	}
 	return true;
}

static void SetupPlayerForClassSelection(int playerid)
{
 	SetPlayerInterior(playerid,14);
	SetPlayerPos(playerid,258.4893f,-41.4008f,1002.0234f);
	SetPlayerFacingAngle(playerid, 270.0f);
	SetPlayerCameraPos(playerid,256.0815f,-43.0475f,1004.0234f);
	SetPlayerCameraLookAt(playerid,258.4893f,-41.4008f,1002.0234f,CAMERA_CUT);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	iSpawnSet[playerid] = 0;
	SetupPlayerForClassSelection(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	logprintf("\n----------------------------------");
	logprintf("  Running LVDM ~MoneyGrub\n");
	logprintf("		 Coded By");
	logprintf("			Jax");
	logprintf("----------------------------------\n");

	SetGameModeText("Ventura's DM~MG");

	// Initialize random number generator
	srand((unsigned int)time(NULL));

	ShowPlayerMarkers(1);
	ShowNameTags(1);
	EnableStuntBonusForAll(0);

	// Player Class's
	AddPlayerClass(0,1958.3783f,1343.1572f,15.3746f,270.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(266,1958.3783f,1343.1572f,15.3746f,270.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(267,1958.3783f,1343.1572f,15.3746f,270.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(268,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(269,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(270,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(271,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(272,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);

	AddPlayerClass(280,1958.3783f,1343.1572f,15.3746f,270.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(281,1958.3783f,1343.1572f,15.3746f,270.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(282,1958.3783f,1343.1572f,15.3746f,270.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(283,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(284,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(285,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(286,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(287,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);

	AddPlayerClass(254,1958.3783f,1343.1572f,15.3746f,0.0f,0,0,24,300,-1,-1);
	AddPlayerClass(255,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(256,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(257,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(258,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(259,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(260,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(261,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(262,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(263,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(264,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(274,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(275,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(276,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);

	AddPlayerClass(1,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(2,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(290,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(291,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(292,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(293,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(294,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(295,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(296,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(297,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(298,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(299,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);

	AddPlayerClass(277,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(278,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(279,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(288,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(47,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(48,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(49,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(50,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(51,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(52,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(53,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(54,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(55,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(56,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(57,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(58,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(59,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(60,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(61,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(62,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(63,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(64,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(66,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(67,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(68,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(69,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(70,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(71,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(72,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(73,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(75,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(76,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(78,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(79,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(80,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(81,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(82,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(83,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(84,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(85,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(87,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(88,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(89,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(91,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(92,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(93,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(95,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(96,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(97,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(98,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(99,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(100,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(101,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(102,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(103,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(104,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(105,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(106,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(107,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(108,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(109,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(110,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(111,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(112,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(113,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(114,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(115,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(116,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(117,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(118,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(120,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(121,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(122,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(123,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(124,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(125,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(126,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(127,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(128,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(129,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(131,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(133,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(134,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(135,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(136,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(137,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(138,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(139,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(140,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(141,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(142,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(143,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(144,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(145,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(146,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(147,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(148,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(150,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(151,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(152,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(153,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(154,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(155,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(156,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(157,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(158,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(159,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(160,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(161,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(162,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(163,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(164,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(165,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(166,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(167,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(168,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(169,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(170,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(171,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(172,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(173,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(174,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(175,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(176,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(177,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(178,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(179,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(180,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(181,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(182,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(183,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(184,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(185,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(186,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(187,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(188,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(189,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(190,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(191,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(192,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(193,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(194,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(195,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(196,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(197,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(198,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(199,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(200,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(201,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(202,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(203,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(204,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(205,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(206,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(207,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(209,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(210,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(211,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(212,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(213,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(214,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(215,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(216,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(217,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(218,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(219,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(220,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(221,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(222,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(223,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(224,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(225,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(226,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(227,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(228,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(229,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(230,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(231,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(232,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(233,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(234,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(235,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(236,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(237,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(238,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(239,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(240,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(241,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(242,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(243,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(244,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(245,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(246,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(247,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(248,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(249,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(250,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(251,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);
	AddPlayerClass(253,1958.3783f,1343.1572f,15.3746f,269.1425f,0,0,24,300,-1,-1);

	// Car Spawns

	AddStaticVehicle(451,2040.0520f,1319.2799f,10.3779f,183.2439f,16,16);
	AddStaticVehicle(429,2040.5247f,1359.2783f,10.3516f,177.1306f,13,13);
	AddStaticVehicle(421,2110.4102f,1398.3672f,10.7552f,359.5964f,13,13);
	AddStaticVehicle(411,2074.9624f,1479.2120f,10.3990f,359.6861f,64,64);
	AddStaticVehicle(477,2075.6038f,1666.9750f,10.4252f,359.7507f,94,94);
	AddStaticVehicle(541,2119.5845f,1938.5969f,10.2967f,181.9064f,22,22);
	AddStaticVehicle(541,1843.7881f,1216.0122f,10.4556f,270.8793f,60,1);
	AddStaticVehicle(402,1944.1003f,1344.7717f,8.9411f,0.8168f,30,30);
	AddStaticVehicle(402,1679.2278f,1316.6287f,10.6520f,180.4150f,90,90);
	AddStaticVehicle(415,1685.4872f,1751.9667f,10.5990f,268.1183f,25,1);
	AddStaticVehicle(411,2034.5016f,1912.5874f,11.9048f,0.2909f,123,1);
	AddStaticVehicle(411,2172.1682f,1988.8643f,10.5474f,89.9151f,116,1);
	AddStaticVehicle(429,2245.5759f,2042.4166f,10.5000f,270.7350f,14,14);
	AddStaticVehicle(477,2361.1538f,1993.9761f,10.4260f,178.3929f,101,1);
	AddStaticVehicle(550,2221.9946f,1998.7787f,9.6815f,92.6188f,53,53);
	AddStaticVehicle(558,2243.3833f,1952.4221f,14.9761f,359.4796f,116,1);
	AddStaticVehicle(587,2276.7085f,1938.7263f,31.5046f,359.2321f,40,1);
	AddStaticVehicle(587,2602.7769f,1853.0667f,10.5468f,91.4813f,43,1);
	AddStaticVehicle(603,2610.7600f,1694.2588f,10.6585f,89.3303f,69,1);
	AddStaticVehicle(587,2635.2419f,1075.7726f,10.5472f,89.9571f,53,1);
	AddStaticVehicle(437,2577.2354f,1038.8063f,10.4777f,181.7069f,35,1);
	AddStaticVehicle(535,2039.1257f,1545.0879f,10.3481f,359.6690f,123,1);
	AddStaticVehicle(535,2009.8782f,2411.7524f,10.5828f,178.9618f,66,1);
	AddStaticVehicle(429,2010.0841f,2489.5510f,10.5003f,268.7720f,1,2);
	AddStaticVehicle(415,2076.4033f,2468.7947f,10.5923f,359.9186f,36,1);
	AddStaticVehicle(487,2093.2754f,2414.9421f,74.7556f,89.0247f,26,57);
	AddStaticVehicle(506,2352.9026f,2577.9768f,10.5201f,0.4091f,7,7);
	AddStaticVehicle(506,2166.6963f,2741.0413f,10.5245f,89.7816f,52,52);
	AddStaticVehicle(411,1960.9989f,2754.9072f,10.5473f,200.4316f,112,1);
	AddStaticVehicle(429,1919.5863f,2760.7595f,10.5079f,100.0753f,2,1);
	AddStaticVehicle(415,1673.8038f,2693.8044f,10.5912f,359.7903f,40,1);
	AddStaticVehicle(402,1591.0482f,2746.3982f,10.6519f,172.5125f,30,30);
	AddStaticVehicle(603,1580.4537f,2838.2886f,10.6614f,181.4573f,75,77);
	AddStaticVehicle(550,1555.2734f,2750.5261f,10.6388f,91.7773f,62,62);
	AddStaticVehicle(535,1455.9305f,2878.5288f,10.5837f,181.0987f,118,1);
	AddStaticVehicle(477,1537.8425f,2578.0525f,10.5662f,0.0650f,121,1);
	AddStaticVehicle(451,1433.1594f,2607.3762f,10.3781f,88.0013f,16,16);
	AddStaticVehicle(603,2223.5898f,1288.1464f,10.5104f,182.0297f,18,1);
	AddStaticVehicle(558,2451.6707f,1207.1179f,10.4510f,179.8960f,24,1);
	AddStaticVehicle(550,2461.7253f,1357.9705f,10.6389f,180.2927f,62,62);
	AddStaticVehicle(558,2461.8162f,1629.2268f,10.4496f,181.4625f,117,1);
	AddStaticVehicle(477,2395.7554f,1658.9591f,10.5740f,359.7374f,0,1);
	AddStaticVehicle(404,1553.3696f,1020.2884f,10.5532f,270.6825f,119,50);
	AddStaticVehicle(400,1380.8304f,1159.1782f,10.9128f,355.7117f,123,1);
	AddStaticVehicle(418,1383.4630f,1035.0420f,10.9131f,91.2515f,117,227);
	AddStaticVehicle(404,1445.4526f,974.2831f,10.5534f,1.6213f,109,100);
	AddStaticVehicle(400,1704.2365f,940.1490f,10.9127f,91.9048f,113,1);
	AddStaticVehicle(404,1658.5463f,1028.5432f,10.5533f,359.8419f,101,101);
	AddStaticVehicle(581,1677.6628f,1040.1930f,10.4136f,178.7038f,58,1);
	AddStaticVehicle(581,1383.6959f,1042.2114f,10.4121f,85.7269f,66,1);
	AddStaticVehicle(581,1064.2332f,1215.4158f,10.4157f,177.2942f,72,1);
	AddStaticVehicle(581,1111.4536f,1788.3893f,10.4158f,92.4627f,72,1);
	AddStaticVehicle(522,953.2818f,1806.1392f,8.2188f,235.0706f,3,8);
	AddStaticVehicle(522,995.5328f,1886.6055f,10.5359f,90.1048f,3,8);
	AddStaticVehicle(521,993.7083f,2267.4133f,11.0315f,1.5610f,75,13);
	AddStaticVehicle(535,1439.5662f,1999.9822f,10.5843f,0.4194f,66,1);
	AddStaticVehicle(522,1430.2354f,1999.0144f,10.3896f,352.0951f,6,25);
	AddStaticVehicle(522,2156.3540f,2188.6572f,10.2414f,22.6504f,6,25);
	AddStaticVehicle(598,2277.6846f,2477.1096f,10.5652f,180.1090f,0,1);
	AddStaticVehicle(598,2268.9888f,2443.1697f,10.5662f,181.8062f,0,1);
	AddStaticVehicle(598,2256.2891f,2458.5110f,10.5680f,358.7335f,0,1);
	AddStaticVehicle(598,2251.6921f,2477.0205f,10.5671f,179.5244f,0,1);
	AddStaticVehicle(523,2294.7305f,2441.2651f,10.3860f,9.3764f,0,0);
	AddStaticVehicle(523,2290.7268f,2441.3323f,10.3944f,16.4594f,0,0);
	AddStaticVehicle(523,2295.5503f,2455.9656f,2.8444f,272.6913f,0,0);
	AddStaticVehicle(522,2476.7900f,2532.2222f,21.4416f,0.5081f,8,82);
	AddStaticVehicle(522,2580.5320f,2267.9595f,10.3917f,271.2372f,8,82);
	AddStaticVehicle(522,2814.4331f,2364.6641f,10.3907f,89.6752f,36,105);
	AddStaticVehicle(535,2827.4143f,2345.6953f,10.5768f,270.0668f,97,1);
	AddStaticVehicle(521,1670.1089f,1297.8322f,10.3864f,359.4936f,87,118);
	AddStaticVehicle(487,1614.7153f,1548.7513f,11.2749f,347.1516f,58,8);
	AddStaticVehicle(487,1647.7902f,1538.9934f,11.2433f,51.8071f,0,8);
	AddStaticVehicle(487,1608.3851f,1630.7268f,11.2840f,174.5517f,58,8);
	AddStaticVehicle(476,1283.0006f,1324.8849f,9.5332f,275.0468f,7,6); //11.5332f
	AddStaticVehicle(476,1283.5107f,1361.3171f,9.5382f,271.1684f,1,6); //11.5382f
	AddStaticVehicle(476,1283.6847f,1386.5137f,11.5300f,272.1003f,89,91);
	AddStaticVehicle(476,1288.0499f,1403.6605f,11.5295f,243.5028f,119,117);
	AddStaticVehicle(415,1319.1038f,1279.1791f,10.5931f,0.9661f,62,1);
	AddStaticVehicle(521,1710.5763f,1805.9275f,10.3911f,176.5028f,92,3);
	AddStaticVehicle(521,2805.1650f,2027.0028f,10.3920f,357.5978f,92,3);
	AddStaticVehicle(535,2822.3628f,2240.3594f,10.5812f,89.7540f,123,1);
	AddStaticVehicle(521,2876.8013f,2326.8418f,10.3914f,267.8946f,115,118);
	AddStaticVehicle(429,2842.0554f,2637.0105f,10.5000f,182.2949f,1,3);
	AddStaticVehicle(549,2494.4214f,2813.9348f,10.5172f,316.9462f,72,39);
	AddStaticVehicle(549,2327.6484f,2787.7327f,10.5174f,179.5639f,75,39);
	AddStaticVehicle(549,2142.6970f,2806.6758f,10.5176f,89.8970f,79,39);
	AddStaticVehicle(521,2139.7012f,2799.2114f,10.3917f,229.6327f,25,118);
	AddStaticVehicle(521,2104.9446f,2658.1331f,10.3834f,82.2700f,36,0);
	AddStaticVehicle(521,1914.2322f,2148.2590f,10.3906f,267.7297f,36,0);
	AddStaticVehicle(549,1904.7527f,2157.4312f,10.5175f,183.7728f,83,36);
	AddStaticVehicle(549,1532.6139f,2258.0173f,10.5176f,359.1516f,84,36);
	AddStaticVehicle(521,1534.3204f,2202.8970f,10.3644f,4.9108f,118,118);
	AddStaticVehicle(549,1613.1553f,2200.2664f,10.5176f,89.6204f,89,35);
	AddStaticVehicle(400,1552.1292f,2341.7854f,10.9126f,274.0815f,101,1);
	AddStaticVehicle(404,1637.6285f,2329.8774f,10.5538f,89.6408f,101,101);
	AddStaticVehicle(400,1357.4165f,2259.7158f,10.9126f,269.5567f,62,1);
	AddStaticVehicle(411,1281.7458f,2571.6719f,10.5472f,270.6128f,106,1);
	AddStaticVehicle(522,1305.5295f,2528.3076f,10.3955f,88.7249f,3,8);
	AddStaticVehicle(521,993.9020f,2159.4194f,10.3905f,88.8805f,74,74);
	AddStaticVehicle(415,1512.7134f,787.6931f,10.5921f,359.5796f,75,1);
	AddStaticVehicle(522,2299.5872f,1469.7910f,10.3815f,258.4984f,3,8);
	AddStaticVehicle(522,2133.6428f,1012.8537f,10.3789f,87.1290f,3,8);

	//Monday 13th Additions ~ Jax
	AddStaticVehicle(415,2266.7336f,648.4756f,11.0053f,177.8517f,0,1); //
	AddStaticVehicle(461,2404.6636f,647.9255f,10.7919f,183.7688f,53,1); //
	AddStaticVehicle(506,2628.1047f,746.8704f,10.5246f,352.7574f,3,3); //
	AddStaticVehicle(549,2817.6445f,928.3469f,10.4470f,359.5235f,72,39); //
	// --- uncommented
	AddStaticVehicle(562,1919.8829f,947.1886f,10.4715f,359.4453f,11,1); //
	AddStaticVehicle(562,1881.6346f,1006.7653f,10.4783f,86.9967f,11,1); //
	AddStaticVehicle(562,2038.1044f,1006.4022f,10.4040f,179.2641f,11,1); //
	AddStaticVehicle(562,2038.1614f,1014.8566f,10.4057f,179.8665f,11,1); //
	AddStaticVehicle(562,2038.0966f,1026.7987f,10.4040f,180.6107f,11,1); //
	// --- uncommented end

	//Uber haxed
	AddStaticVehicle(422,9.1065f,1165.5066f,19.5855f,2.1281f,101,25); //
	AddStaticVehicle(463,19.8059f,1163.7103f,19.1504f,346.3326f,11,11); //
	AddStaticVehicle(463,12.5740f,1232.2848f,18.8822f,121.8670f,22,22); //
	//AddStaticVehicle(434,-110.8473f,1133.7113f,19.7091f,359.7000f,2,2); //hotknife
	AddStaticVehicle(586,69.4633f,1217.0189f,18.3304f,158.9345f,10,1); //
	AddStaticVehicle(586,-199.4185f,1223.0405f,19.2624f,176.7001f,25,1); //
	//AddStaticVehicle(605,-340.2598f,1177.4846f,19.5565f,182.6176f,43,8); // SMASHED UP CAR
	AddStaticVehicle(476,325.4121f,2538.5999f,17.5184f,181.2964f,71,77); //
	AddStaticVehicle(476,291.0975f,2540.0410f,17.5276f,182.7206f,7,6); //
	AddStaticVehicle(576,384.2365f,2602.1763f,16.0926f,192.4858f,72,1); //
	AddStaticVehicle(586,423.8012f,2541.6870f,15.9708f,338.2426f,10,1); //
	AddStaticVehicle(586,-244.0047f,2724.5439f,62.2077f,51.5825f,10,1); //
	AddStaticVehicle(586,-311.1414f,2659.4329f,62.4513f,310.9601f,27,1); //

	//uber haxed x 50
	//AddStaticVehicle(406,547.4633f,843.0204f,-39.8406f,285.2948f,1,1); // DUMPER
	//AddStaticVehicle(406,625.1979f,828.9873f,-41.4497f,71.3360f,1,1); // DUMPER
	//AddStaticVehicle(486,680.7997f,919.0510f,-40.4735f,105.9145f,1,1); // DOZER
	//AddStaticVehicle(486,674.3994f,927.7518f,-40.6087f,128.6116f,1,1); // DOZER
	AddStaticVehicle(543,596.8064f,866.2578f,-43.2617f,186.8359f,67,8); //
	AddStaticVehicle(543,835.0838f,836.8370f,11.8739f,14.8920f,8,90); //
	AddStaticVehicle(549,843.1893f,838.8093f,12.5177f,18.2348f,79,39); //
	//AddStaticVehicle(605,319.3803f,740.2404f,6.7814f,271.2593f,8,90); // SMASHED UP CAR
	AddStaticVehicle(400,-235.9767f,1045.8623f,19.8158f,180.0806f,75,1); //
	AddStaticVehicle(599,-211.5940f,998.9857f,19.8437f,265.4935f,0,1); //
	AddStaticVehicle(422,-304.0620f,1024.1111f,19.5714f,94.1812f,96,25); //
	AddStaticVehicle(588,-290.2229f,1317.0276f,54.1871f,81.7529f,1,1); //
	//AddStaticVehicle(424,-330.2399f,1514.3022f,75.1388f,179.1514f,2,2); //BF INJECT
	AddStaticVehicle(451,-290.3145f,1567.1534f,75.0654f,133.1694f,61,61); //
	AddStaticVehicle(470,280.4914f,1945.6143f,17.6317f,310.3278f,43,0); //
	AddStaticVehicle(470,272.2862f,1949.4713f,17.6367f,285.9714f,43,0); //
	AddStaticVehicle(470,271.6122f,1961.2386f,17.6373f,251.9081f,43,0); //
	AddStaticVehicle(470,279.8705f,1966.2362f,17.6436f,228.4709f,43,0); //
	//AddStaticVehicle(548,292.2317f,1923.6440f,19.2898f,235.3379f,1,1); // CARGOBOB
	AddStaticVehicle(433,277.6437f,1985.7559f,18.0772f,270.4079f,43,0); //
	AddStaticVehicle(433,277.4477f,1994.8329f,18.0773f,267.7378f,43,0); //
	//AddStaticVehicle(432,275.9634f,2024.3629f,17.6516f,270.6823f,43,0); // Tank (can cause scary shit to go down)
	AddStaticVehicle(568,-441.3438f,2215.7026f,42.2489f,191.7953f,41,29); //
	AddStaticVehicle(568,-422.2956f,2225.2612f,42.2465f,0.0616f,41,29); //
	AddStaticVehicle(568,-371.7973f,2234.5527f,42.3497f,285.9481f,41,29); //
	AddStaticVehicle(568,-360.1159f,2203.4272f,42.3039f,113.6446f,41,29); //
	AddStaticVehicle(468,-660.7385f,2315.2642f,138.3866f,358.7643f,6,6); //
	AddStaticVehicle(460,-1029.2648f,2237.2217f,42.2679f,260.5732f,1,3); //

	//Uber haxed x 100

	// --- uncommented
	AddStaticVehicle(419,95.0568f,1056.5530f,13.4068f,192.1461f,13,76); //
	AddStaticVehicle(429,114.7416f,1048.3517f,13.2890f,174.9752f,1,2); //
	//AddStaticVehicle(466,124.2480f,1075.1835f,13.3512f,174.5334f,78,76); // exceeds model limit
	AddStaticVehicle(411,-290.0065f,1759.4958f,42.4154f,89.7571f,116,1); //
	// --- uncommented end
	AddStaticVehicle(522,-302.5649f,1777.7349f,42.2514f,238.5039f,6,25); //
	AddStaticVehicle(522,-302.9650f,1776.1152f,42.2588f,239.9874f,8,82); //
	AddStaticVehicle(533,-301.0404f,1750.8517f,42.3966f,268.7585f,75,1); //
	AddStaticVehicle(535,-866.1774f,1557.2700f,23.8319f,269.3263f,31,1); //
	AddStaticVehicle(550,-799.3062f,1518.1556f,26.7488f,88.5295f,53,53); //
	AddStaticVehicle(521,-749.9730f,1589.8435f,26.5311f,125.6508f,92,3); //
	AddStaticVehicle(522,-867.8612f,1544.5282f,22.5419f,296.0923f,3,3); //
	AddStaticVehicle(554,-904.2978f,1553.8269f,25.9229f,266.6985f,34,30); //
	AddStaticVehicle(521,-944.2642f,1424.1603f,29.6783f,148.5582f,92,3); //
	// Exceeds model limit, cars need model adjustments
	// --- uncommented
	AddStaticVehicle(429,-237.7157f,2594.8804f,62.3828f,178.6802f,1,2); //
	//AddStaticVehicle(431,-160.5815f,2693.7185f,62.2031f,89.4133f,47,74); //
	AddStaticVehicle(463,-196.3012f,2774.4395f,61.4775f,303.8402f,22,22); //
	//AddStaticVehicle(483,-204.1827f,2608.7368f,62.6956f,179.9914f,1,5); //
	//AddStaticVehicle(490,-295.4756f,2674.9141f,62.7434f,359.3378f,0,0); //
	//AddStaticVehicle(500,-301.5293f,2687.6013f,62.7723f,87.9509f,28,119); //
	//AddStaticVehicle(500,-301.6699f,2680.3293f,62.7393f,89.7925f,13,119); //
	AddStaticVehicle(519,-1341.1079f,-254.3787f,15.0701f,321.6338f,1,1); //
	AddStaticVehicle(519,-1371.1775f,-232.3967f,15.0676f,315.6091f,1,1); //
	//AddStaticVehicle(552,-1396.2028f,-196.8298f,13.8434f,286.2720f,56,56); //
	//AddStaticVehicle(552,-1312.4509f,-284.4692f,13.8417f,354.3546f,56,56); //
	//AddStaticVehicle(552,-1393.5995f,-521.0770f,13.8441f,187.1324f,56,56); //
	//AddStaticVehicle(513,-1355.6632f,-488.9562f,14.7157f,191.2547f,48,18); //
	//AddStaticVehicle(513,-1374.4580f,-499.1462f,14.7482f,220.4057f,54,34); //
	//AddStaticVehicle(553,-1197.8773f,-489.6715f,15.4841f,0.4029f,91,87); //
	//AddStaticVehicle(553,1852.9989f,-2385.4009f,14.8827f,200.0707f,102,119); //
	//AddStaticVehicle(583,1879.9594f,-2349.1919f,13.0875f,11.0992f,1,1); //
	//AddStaticVehicle(583,1620.9697f,-2431.0752f,13.0951f,126.3341f,1,1); //
	//AddStaticVehicle(583,1545.1564f,-2409.2114f,13.0953f,23.5581f,1,1); //
	//AddStaticVehicle(583,1656.3702f,-2651.7913f,13.0874f,352.7619f,1,1); //
	AddStaticVehicle(519,1642.9850f,-2425.2063f,14.4744f,159.8745f,1,1); //
	AddStaticVehicle(519,1734.1311f,-2426.7563f,14.4734f,172.2036f,1,1); //
	// --- uncommented end

	AddStaticVehicle(415,-680.9882f,955.4495f,11.9032f,84.2754f,36,1); //
	AddStaticVehicle(460,-816.3951f,2222.7375f,43.0045f,268.1861f,1,3); //
	AddStaticVehicle(460,-94.6885f,455.4018f,1.5719f,250.5473f,1,3); //
	AddStaticVehicle(460,1624.5901f,565.8568f,1.7817f,200.5292f,1,3); //
	AddStaticVehicle(460,1639.3567f,572.2720f,1.5311f,206.6160f,1,3); //
	AddStaticVehicle(460,2293.4219f,517.5514f,1.7537f,270.7889f,1,3); //
	AddStaticVehicle(460,2354.4690f,518.5284f,1.7450f,270.2214f,1,3); //
	AddStaticVehicle(460,772.4293f,2912.5579f,1.0753f,69.6706f,1,3); //

	// 22/4 UPDATE
	AddStaticVehicle(560,2133.0769f,1019.2366f,10.5259f,90.5265f,9,39); //
	AddStaticVehicle(560,2142.4023f,1408.5675f,10.5258f,0.3660f,17,1); //
	AddStaticVehicle(560,2196.3340f,1856.8469f,10.5257f,179.8070f,21,1); //
	AddStaticVehicle(560,2103.4146f,2069.1514f,10.5249f,270.1451f,33,0); //
	AddStaticVehicle(560,2361.8042f,2210.9951f,10.3848f,178.7366f,37,0); //
	AddStaticVehicle(560,-1993.2465f,241.5329f,34.8774f,310.0117f,41,29); //
	AddStaticVehicle(559,-1989.3235f,270.1447f,34.8321f,88.6822f,58,8); //
	AddStaticVehicle(559,-1946.2416f,273.2482f,35.1302f,126.4200f,60,1); //
	AddStaticVehicle(558,-1956.8257f,271.4941f,35.0984f,71.7499f,24,1); //
	AddStaticVehicle(562,-1952.8894f,258.8604f,40.7082f,51.7172f,17,1); //
	AddStaticVehicle(411,-1949.8689f,266.5759f,40.7776f,216.4882f,112,1); //
	AddStaticVehicle(429,-1988.0347f,305.4242f,34.8553f,87.0725f,2,1); //
	AddStaticVehicle(559,-1657.6660f,1213.6195f,6.9062f,282.6953f,13,8); //
	AddStaticVehicle(560,-1658.3722f,1213.2236f,13.3806f,37.9052f,52,39); //
	AddStaticVehicle(558,-1660.8994f,1210.7589f,20.7875f,317.6098f,36,1); //
	AddStaticVehicle(550,-1645.2401f,1303.9883f,6.8482f,133.6013f,7,7); //
	AddStaticVehicle(460,-1333.1960f,903.7660f,1.5568f,0.5095f,46,32); //

	// 25/4 UPDATE
	AddStaticVehicle(411,113.8611f,1068.6182f,13.3395f,177.1330f,116,1); //
	AddStaticVehicle(429,159.5199f,1185.1160f,14.7324f,85.5769f,1,2); //
	AddStaticVehicle(411,612.4678f,1694.4126f,6.7192f,302.5539f,75,1); //
	AddStaticVehicle(522,661.7609f,1720.9894f,6.5641f,19.1231f,6,25); //
	AddStaticVehicle(522,660.0554f,1719.1187f,6.5642f,12.7699f,8,82); //
	AddStaticVehicle(567,711.4207f,1947.5208f,5.4056f,179.3810f,90,96); //
	AddStaticVehicle(567,1031.8435f,1920.3726f,11.3369f,89.4978f,97,96); //
	AddStaticVehicle(567,1112.3754f,1747.8737f,10.6923f,270.9278f,102,114); //
	AddStaticVehicle(567,1641.6802f,1299.2113f,10.6869f,271.4891f,97,96); //
	AddStaticVehicle(567,2135.8757f,1408.4512f,10.6867f,180.4562f,90,96); //
	AddStaticVehicle(567,2262.2639f,1469.2202f,14.9177f,91.1919f,99,81); //
	AddStaticVehicle(567,2461.7380f,1345.5385f,10.6975f,0.9317f,114,1); //
	AddStaticVehicle(567,2804.4365f,1332.5348f,10.6283f,271.7682f,88,64); //
	AddStaticVehicle(560,2805.1685f,1361.4004f,10.4548f,270.2340f,17,1); //
	AddStaticVehicle(506,2853.5378f,1361.4677f,10.5149f,269.6648f,7,7); //
	AddStaticVehicle(567,2633.9832f,2205.7061f,10.6868f,180.0076f,93,64); //
	AddStaticVehicle(567,2119.9751f,2049.3127f,10.5423f,180.1963f,93,64); //
	AddStaticVehicle(567,2785.0261f,-1835.0374f,9.6874f,226.9852f,93,64); //
	AddStaticVehicle(567,2787.8975f,-1876.2583f,9.6966f,0.5804f,99,81); //
	AddStaticVehicle(411,2771.2993f,-1841.5620f,9.4870f,20.7678f,116,1); //
	AddStaticVehicle(420,1713.9319f,1467.8354f,10.5219f,342.8006f,6,1); // taxi

	AddStaticPickup(371, 15, 1710.3359f,1614.3585f,10.1191f, 0); //para
	AddStaticPickup(371, 15, 1964.4523f,1917.0341f,130.9375f, 0); //para
	AddStaticPickup(371, 15, 2055.7258f,2395.8589f,150.4766f, 0); //para
	AddStaticPickup(371, 15, 2265.0120f,1672.3837f,94.9219f, 0); //para
	AddStaticPickup(371, 15, 2265.9739f,1623.4060f,94.9219f, 0); //para

	SetTimer(1000, true, MoneyGrubScoreUpdate, NULL);

	return true;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData) {
	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	sampgdk_initialize_plugin(ppPluginData);
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	return;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
	sampgdk_process_timers();
}
