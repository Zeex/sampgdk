#include <cstring>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <sampgdk/core.h>
#include <sampgdk/interop.h>
#include "ufs.h"

namespace {

std::string GetServerCfgOption(const std::string &option) {
  std::string name, value;
  std::string line;
  std::fstream server_cfg("server.cfg");
  if (server_cfg) {
    while (std::getline(server_cfg, line)) {
      std::stringstream ss(line);
      ss >> name;
      if (name == option) {
        ss >> value;
        break;
      }
    }
  }
  return value;
}

void SplitString(const std::string &string,
                 std::vector<std::string> &substrings) {
  std::stringstream stream(string);
  std::copy(
    std::istream_iterator<std::string>(stream),
    std::istream_iterator<std::string>(),
    std::back_inserter(substrings)
  );
}

void GetScriptNames(std::vector<std::string> &names) {
  std::string opt = GetServerCfgOption("filterscripts2");
  if (!opt.empty()) {
    SplitString(opt, names);
  }
}

void GetPluginNames(std::vector<std::string> &names) {
  std::string opt = GetServerCfgOption("plugins2");
  if (!opt.empty()) {
    SplitString(opt, names);
  }
}

bool StringEndsWith(const std::string &s, const std::string &what) {
  return s.rfind(what) == s.length() - what.length();
}

std::string GetItemPath(const std::string &name, const std::string &dir,
                        const std::string &ext) {
  std::string path;
  path.append(dir);
  path.append("/");
  path.append(name);
  if (!StringEndsWith(name, ext)) {
    path.append(ext);
  }
  return path;
}

std::string GetScriptPath(const std::string &name) {
  return GetItemPath(name, "filterscripts", ".amx");
}

std::string GetPluginPath(const std::string &name) {
  return GetItemPath(name, "plugins", ufs::PluginExtension);
}

} // anonymous namespace

namespace ufs {

// static
UFS &UFS::Instance() {
  static UFS ufs;
  return ufs;
}

UFS::~UFS() {
  UnloadScripts();
  UnloadPlugins();
}

void UFS::SetPluginData(void **data) {
  plugin_data_ = data;
}

bool UFS::LoadPlugin(const std::string &name, PluginError &error) {
  Plugin *plugin = new Plugin(GetPluginPath(name));
  if (plugin != 0) {
    error = plugin->Load(plugin_data_);
    if (plugin->IsLoaded()) {
      plugins_.insert(std::make_pair(name, plugin));
      return true;
    } else {
      delete plugin;
    }
  }
  return false;
}

void UFS::LoadPlugins() {
  sampgdk_logprintf("");
  sampgdk_logprintf("Server Plugins");
  sampgdk_logprintf("--------------");

  std::vector<std::string> names;
  GetPluginNames(names);

  for (std::vector<std::string>::const_iterator it = names.begin();
       it != names.end(); it++) {
    const std::string &name = *it;
    sampgdk_logprintf(" Loading plugin: %s", name.c_str());

    PluginError error;
    if (LoadPlugin(name, error)) {
      sampgdk_logprintf("  Loaded.");
    } else {
      switch (error) {
        case PLUGIN_ERROR_LOAD: {
          sampgdk_logprintf("  Failed.");
          break;
        }
        case PLUGIN_ERROR_VERSION:
          sampgdk_logprintf("  Unsupported version.");
          break;
        case PLUGIN_ERROR_API:
          sampgdk_logprintf("  Plugin does not conform to acrhitecture.");
          break;
        default:
          break;
      }
    }
  }

  sampgdk_logprintf(" Loaded %d plugins.\n", plugins_.size());
  sampgdk_logprintf("");
}

void UFS::UnloadPlugin(Plugin *plugin) {
  plugin->Unload();
}

void UFS::UnloadPlugins() {
  for (Plugins::iterator it = plugins_.begin();
       it != plugins_.end(); it++) {
    Plugin *plugin = it->second;
    UnloadPlugin(plugin);
    delete plugin;
  }
  plugins_.clear();
}

bool UFS::LoadScript(const std::string &name) {
  Script *fs = new Script(GetScriptPath(name));
  if (fs == 0 || !fs->IsLoaded()) {
    delete fs;
    return false;
  }

  scripts_.insert(std::make_pair(name, fs));

  int num_natives;
  const AMX_NATIVE_INFO *natives = sampgdk_GetNatives(&num_natives);
  amx_Register(fs->amx(), natives, num_natives);

  for (Plugins::iterator it = plugins_.begin();
       it != plugins_.end(); it++) {
    Plugin *plugin = it->second;
    plugin->AmxLoad(fs->amx());
  }

  fs->Init();
  return true;
}

bool UFS::UnloadScript(Script *fs) {
  fs->Exit();
  fs->Unload();
  return true;
}

void UFS::LoadScripts() {
  std::vector<std::string> names;
  GetScriptNames(names);

  sampgdk_logprintf("Filterscripts");
  sampgdk_logprintf("---------------");

  for (std::vector<std::string>::const_iterator it = names.begin();
       it != names.end(); it++) {
    const std::string &name = *it;
    sampgdk_logprintf("  Loading filterscript '%s.amx'", name.c_str());
    LoadScript(name);
  }

  sampgdk_logprintf("  Loaded %d filterscripts.\n", scripts_.size());
  sampgdk_logprintf("");
}

bool UFS::UnloadScript(const std::string &name) {
  Scripts::iterator it = scripts_.find(name);
  if (it != scripts_.end()) {
    Script *fs = it->second;
    return UnloadScript(fs);
  }
  return false;
}

void UFS::UnloadScripts() {
  for (Scripts::iterator it = scripts_.begin();
       it != scripts_.end(); it++) {
    Script *script = it->second;
    UnloadScript(script);
    delete script;
  }
  scripts_.clear();
}

} // namespace ufs
