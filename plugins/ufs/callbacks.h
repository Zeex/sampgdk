#ifndef UFS_CALLBACKS_H
#define UFS_CALLBACKS_H

namespace ufs {

class Script;

template<typename T1 = void,
         typename T2 = void,
         typename T3 = void,
         typename T4 = void,
         typename T5 = void,
         typename Unused = void>
class Callback {};

template<typename T1>
class Callback<T1, void, void, void, void, void> {
 public:
  typedef bool (*FuncPtr)(Script *s, T1 x1);
  Callback(FuncPtr func, T1 x1):
    func_(func), x1_(x1)
  {}
  bool operator()(Script *s) const {
    return func_(s, x1_);
  }
 private:
  FuncPtr func_;
  T1 x1_;
};

template<typename T1, typename T2>
class Callback<T1, T2, void, void, void, void> {
 public:
  typedef bool (*FuncPtr)(Script *s, T1 x1, T2 x2);
  Callback(FuncPtr func, T1 x1, T2 x2):
    func_(func), x1_(x1), x2_(x2)
  {}
  bool operator()(Script *s) const {
    return func_(s, x1_, x2_);
  }
 private:
  FuncPtr func_;
  T1 x1_;
  T2 x2_;
};

template<typename T1, typename T2, typename T3>
class Callback<T1, T2, T3, void, void, void> {
 public:
  typedef bool (*FuncPtr)(Script *s, T1 x1, T2 x2, T3 x3);
  Callback(FuncPtr func, T1 x1, T2 x2, T3 x3):
    func_(func), x1_(x1), x2_(x2), x3_(x3)
  {}
  bool operator()(Script *s) const {
    return func_(s, x1_, x2_, x3_);
  }
 private:
  FuncPtr func_;
  T1 x1_;
  T2 x2_;
  T3 x3_;
};

template<typename T1, typename T2, typename T3, typename T4>
class Callback<T1, T2, T3, T4, void, void> {
 public:
  typedef bool (*FuncPtr)(Script *s, T1 x1, T2 x2, T3 x3, T4 x4);
  Callback(FuncPtr func, T1 x1, T2 x2, T3 x3, T4 x4):
    func_(func), x1_(x1), x2_(x2), x3_(x3), x4_(x4)
  {}
  bool operator()(Script *s) const {
    return func_(s, x1_, x2_, x3_, x4_);
  }
 private:
  FuncPtr func_;
  T1 x1_;
  T2 x2_;
  T3 x3_;
  T4 x4_;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
class Callback<T1, T2, T3, T4, T5, void> {
 public:
  typedef bool (*FuncPtr)(Script *s, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5);
  Callback(FuncPtr func, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5):
    func_(func), x1_(x1), x2_(x2), x3_(x3), x4_(x4), x5_(x5)
  {}
  bool operator()(Script *s) const {
    return func_(s, x1_, x2_, x3_, x4_, x5_);
  }
private:
  FuncPtr func_;
  T1 x1_;
  T2 x2_;
  T3 x3_;
  T4 x4_;
  T5 x5_;
};

template<typename F, typename T1>
Callback<T1, void, void, void, void, void>
MakeCallback(const F &f, T1 x1) {
  return Callback<T1, void, void, void, void, void>(f, x1);
}

template<typename F, typename T1, typename T2>
Callback<T1, T2, void, void, void, void>
MakeCallback(const F &f, T1 x1, T2 x2) {
  return Callback<T1, T2, void, void, void, void>(f, x1, x2);
}

template<typename F, typename T1, typename T2, typename T3>
Callback<T1, T2, T3, void, void, void>
MakeCallback(const F &f, T1 x1, T2 x2, T3 x3) {
  return Callback<T1, T2, T3, void, void, void>(f, x1, x2, x3);
}

template<typename F, typename T1, typename T2, typename T3, typename T4>
Callback<T1, T2, T3, T4, void, void>
MakeCallback(const F &f, T1 x1, T2 x2, T3 x3, T4 x4) {
  return Callback<T1, T2, T3, T4, void, void>(f, x1, x2, x3, x4);
}

template<typename F, typename T1, typename T2, typename T3, typename T4, typename T5>
Callback<T1, T2, T3, T4, T5, void>
MakeCallback(const F &f, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5) {
  return Callback<T1, T2, T3, T4, T5, void>(f, x1, x2, x3, x4, x5);
}

namespace callbacks {

bool OnGameModeInit(Script *s);
bool OnGameModeExit(Script *s);
bool OnPlayerConnect(Script *s, int playerid);
bool OnPlayerDisconnect(Script *s, int playerid, int reason);
bool OnPlayerSpawn(Script *s, int playerid);
bool OnPlayerDeath(Script *s, int playerid, int killerid, int reason);
bool OnVehicleSpawn(Script *s, int vehicleid);
bool OnVehicleDeath(Script *s, int vehicleid, int killerid);
bool OnPlayerText(Script *s, int playerid, const char text[]);
bool OnPlayerCommandText(Script *s, int playerid, const char cmdtext[]);
bool OnPlayerRequestClass(Script *s, int playerid, int classid);
bool OnPlayerEnterVehicle(Script *s, int playerid, int vehicleid, int ispassenger);
bool OnPlayerExitVehicle(Script *s, int playerid, int vehicleid);
bool OnPlayerStateChange(Script *s, int playerid, int newstate, int oldstate);
bool OnPlayerEnterCheckpoint(Script *s, int playerid);
bool OnPlayerLeaveCheckpoint(Script *s, int playerid);
bool OnPlayerEnterRaceCheckpoint(Script *s, int playerid);
bool OnPlayerLeaveRaceCheckpoint(Script *s, int playerid);
bool OnRconCommand(Script *s, const char cmd[]);
bool OnPlayerRequestSpawn(Script *s, int playerid);
bool OnObjectMoved(Script *s, int objectid);
bool OnPlayerObjectMoved(Script *s, int playerid, int objectid);
bool OnPlayerPickUpPickup(Script *s, int playerid, int pickupid);
bool OnVehicleMod(Script *s, int playerid, int vehicleid, int componentid);
bool OnEnterExitModShop(Script *s, int playerid, int enterexit, int interiorid);
bool OnVehiclePaintjob(Script *s, int playerid, int vehicleid, int paintjobid);
bool OnVehicleRespray(Script *s, int playerid, int vehicleid, int color1, int color2);
bool OnVehicleDamageStatusUpdate(Script *s, int vehicleid, int playerid);
bool OnUnoccupiedVehicleUpdate(Script *s, int vehicleid, int playerid, int passenger_seat);
bool OnPlayerSelectedMenuRow(Script *s, int playerid, int row);
bool OnPlayerExitedMenu(Script *s, int playerid);
bool OnPlayerInteriorChange(Script *s, int playerid, int newinteriorid, int oldinteriorid);
bool OnPlayerKeyStateChange(Script *s, int playerid, int newkeys, int oldkeys);
bool OnRconLoginAttempt(Script *s, const char ip[], const char password[], int success);
bool OnPlayerUpdate(Script *s, int playerid);
bool OnPlayerStreamIn(Script *s, int playerid, int forplayerid);
bool OnPlayerStreamOut(Script *s, int playerid, int forplayerid);
bool OnVehicleStreamIn(Script *s, int vehicleid, int forplayerid);
bool OnVehicleStreamOut(Script *s, int vehicleid, int forplayerid);
bool OnDialogResponse(Script *s, int playerid, int dialogid, int response, int listitem, const char inputtext[]);
bool OnPlayerTakeDamage(Script *s, int playerid, int issuerid, float amount, int weaponid);
bool OnPlayerGiveDamage(Script *s, int playerid, int damagedid, float amount, int weaponid);
bool OnPlayerClickMap(Script *s, int playerid, float fX, float fY, float fZ);

} // namespace callbacks
} // namespace ufs

#endif // UFS_CALLBACKS_H
