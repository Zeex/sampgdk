#include <cassert>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>
#include "ufs.h"

enum LoadState {
  WaitLoad,
  BeginLoad,
  Loaded,
  Unloaded
};

extern void *pAMXFunctions;

static LoadState load_state = WaitLoad;
static std::vector<AMX*> normal_scripts;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return sampgdk::Supports() | SUPPORTS_PROCESS_TICK | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
  ufs::UFS::Instance().SetPluginData(ppData);
  load_state = BeginLoad;
  return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  assert(load_state == Loaded);
  ufs::UFS::Instance().UnloadScripts();
  ufs::UFS::Instance().UnloadPlugins();
  load_state = Unloaded;
  sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  if (load_state == BeginLoad) {
    assert(load_state != Loaded);
    ufs::UFS::Instance().LoadPlugins();
    ufs::UFS::Instance().LoadScripts();
    load_state = Loaded;
    for (std::vector<AMX*>::iterator it = normal_scripts.begin();
          it != normal_scripts.end(); it++) {
      ufs::UFS::Instance().ForEachPlugin(
        std::bind2nd(std::mem_fun(&ufs::Plugin::AmxLoad), *it));
    }
  }
  ufs::UFS::Instance().ForEachPlugin(
    std::mem_fun(&ufs::Plugin::ProcessTick));
  sampgdk::ProcessTick();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
  normal_scripts.push_back(amx);
  return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
  ufs::UFS::Instance().ForEachPlugin(
    std::bind2nd(std::mem_fun(&ufs::Plugin::AmxUnload), amx));
  return AMX_ERR_NONE;
}
