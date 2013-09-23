#include <cassert>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>
#include "ufs.h"

namespace {

class UFSPlugin: public ThisPlugin {
 public:
  enum LoadState {
    DontLoad,
    LoadNow,
    Loaded,
    Unloaded
  };

  UFSPlugin(): load_state_(DontLoad) {}

  void LoadAsync() {
    load_state_ = LoadNow;
  }

  bool Load(void **ppData) {
    return Plugin::Load(ppData) >= 0;
  }

  void Unload() {
    UnloadStuff();
    Plugin::Unload();
  }

  int AmxLoad(AMX *amx) {
    normal_scripts_.push_back(amx);
    ufs::UFS::Instance().ForEachPlugin(
      std::bind2nd(std::mem_fun(&ufs::Plugin::AmxLoad), amx));
    return AMX_ERR_NONE;
  }

  int AmxUnload(AMX *amx) {
    ufs::UFS::Instance().ForEachPlugin(
      std::bind2nd(std::mem_fun(&ufs::Plugin::AmxUnload), amx));
    return AMX_ERR_NONE;
  }

  void ProcessTick() {
    if (load_state_ == LoadNow) {
      DeferredLoad();
    }
    ufs::UFS::Instance().ForEachPlugin(
      std::mem_fun(&ufs::Plugin::ProcessTick));
    ProcessTimers();
  }

 private:
  void DeferredLoad() {
    LoadStuff();
    for (std::vector<AMX*>::iterator it = normal_scripts_.begin();
         it != normal_scripts_.end(); it++) {
      AmxUnload(*it);
    }
  }

  void LoadStuff() {
    assert(load_state_ != Loaded);
    ufs::UFS::Instance().LoadPlugins();
    ufs::UFS::Instance().LoadScripts();
    load_state_ = Loaded;
  }

  void UnloadStuff() {
    assert(load_state_ == Loaded);
    ufs::UFS::Instance().UnloadScripts();
    ufs::UFS::Instance().UnloadPlugins();
    load_state_ = Unloaded;
  }

 private:
  LoadState load_state_;
  std::vector<AMX*> normal_scripts_;
};

UFSPlugin ufs_plugin;

} // anonymous namespace

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  return ufs_plugin.Load(ppData);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
  ufs_plugin.LoadAsync();
  return ufs_plugin.AmxLoad(amx);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
  return ufs_plugin.AmxUnload(amx);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  ufs_plugin.Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  ufs_plugin.ProcessTick();
}
