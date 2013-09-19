#include <functional>
#include <sstream>
#include <string>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>
#include "ufs.h"

namespace {

class UFSPlugin: public ThisPlugin {
 public:
  UFSPlugin(): loaded_stuff_(false) {}
  void LoadStuff() {
    if (!loaded_stuff_) {
      ufs::UFS::Instance().LoadPlugins();
      ufs::UFS::Instance().LoadScripts();
      loaded_stuff_ = true;
    }
  }
  void UnloadStuff() {
    if (loaded_stuff_) {
      ufs::UFS::Instance().UnloadScripts();
      ufs::UFS::Instance().UnloadPlugins();
      loaded_stuff_ = false;
    }
  }
 private:
  bool loaded_stuff_;
};

UFSPlugin ufs_plugin;

} // anonymous namespace

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  if (ufs_plugin.Load(ppData) >= 0) {
    //ufs::UFS::Instance().LoadPlugins();
    //ufs::UFS::Instance().LoadScripts();
    return true;
  }
  return false;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
  ufs_plugin.LoadStuff();
  ufs::UFS::Instance().ForEachPlugin(
    std::bind2nd(std::mem_fun(&ufs::Plugin::AmxLoad), amx));
  return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
  ufs::UFS::Instance().ForEachPlugin(
    std::bind2nd(std::mem_fun(&ufs::Plugin::AmxUnload), amx));
  return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  ufs_plugin.UnloadStuff();
  ufs_plugin.Unload();
  ufs::UFS::Instance().UnloadScripts();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  ufs_plugin.ProcessTimers();
  ufs::UFS::Instance().ForEachPlugin(
    std::mem_fun(&ufs::Plugin::ProcessTick));
}
