#include <cstring>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "ufs.h"

namespace {

int AMXAPI amx_Register_(AMX *amx, const AMX_NATIVE_INFO *nativelist, int n) {
  AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);

  AMX_FUNCSTUBNT *natives = reinterpret_cast<AMX_FUNCSTUBNT*>(amx->base +
                                                              hdr->natives);
  int num_natives = (hdr->libraries - hdr->natives) / hdr->defsize;

  int error = AMX_ERR_NONE;

  for (int i = 0; i < n || (n <= 0 && nativelist[i].name != 0); i++) {
    for (int j = 0; j < num_natives; j++) {
      char *name = reinterpret_cast<char*>(amx->base + natives[j].nameofs);
      if (natives[j].address == 0 &&
          std::strcmp(name, nativelist[i].name) == 0) {
        natives[j].address = reinterpret_cast<ucell>(nativelist[i].func);
        continue;
      }
    }
  }

  for (int i = 0; i < num_natives; i++) {
    if (natives[i].address == 0) {
      amx->flags &= ~AMX_FLAG_NTVREG;
      return AMX_ERR_NOTFOUND;
    }
  }

  amx->flags |= AMX_FLAG_NTVREG;
  return error;
}

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

static void GetPluginNames(std::vector<std::string> &names) {
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

bool UFS::LoadPlugin(const std::string &name, PluginError &error) {
  Plugin *plugin = new Plugin(GetPluginPath(name));
  if (plugin != 0) {
    error = plugin->Load(sampgdk_get_plugin_data());
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
  ServerLog::Printf("");
  ServerLog::Printf("Server Plugins");
  ServerLog::Printf("--------------");

  std::vector<std::string> names;
  GetPluginNames(names);

  for (std::vector<std::string>::const_iterator it = names.begin();
       it != names.end(); it++) {
    const std::string &name = *it;
    ServerLog::Printf(" Loading plugin: %s", name.c_str());

    PluginError error;
    if (LoadPlugin(name, error)) {
      ServerLog::Printf("  Loaded.");
    } else {
      switch (error) {
        case PLUGIN_ERROR_LOAD: {
          ServerLog::Printf("  Failed.");
          break;
        }
        case PLUGIN_ERROR_VERSION:
          ServerLog::Printf("  Unsupported version.");
          break;
        case PLUGIN_ERROR_API:
          ServerLog::Printf("  Plugin does not conform to acrhitecture.");
          break;
        default:
          break;
      }
    }
  }

  ServerLog::Printf(" Loaded %d plugins.\n", plugins_.size());
  ServerLog::Printf("");
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

  amx_Register_(fs->amx(), sampgdk_get_natives(), -1);
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

  ServerLog::Printf("Filterscripts");
  ServerLog::Printf("---------------");

  for (std::vector<std::string>::const_iterator it = names.begin();
       it != names.end(); it++) {
    const std::string &name = *it;
    ServerLog::Printf("  Loading filterscript '%s.amx'", name.c_str());
    LoadScript(name);
  }

  ServerLog::Printf("  Loaded %d filterscripts.\n", scripts_.size());
  ServerLog::Printf("");
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
