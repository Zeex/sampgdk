#include <sstream>
#include <string>
#include "ufs.h"

namespace {

void UnloadScriptRcon(const std::string &name) {
  if (!ufs::UFS::Instance().UnloadScript(name)) {
    ServerLog::Printf("  Filterscript '%s' unload failed.", name.c_str());
  }
}

void LoadScriptRcon(const std::string &name) {
  if (!ufs::UFS::Instance().LoadScript(name)) {
    ServerLog::Printf("  Filterscript '%s' load failed.", name.c_str());
  }
}

} // anonymous namespace

namespace ufs {

void ProcessRconCommand(const char *cmd) {
  std::string name, value;
  std::stringstream stream(cmd);
  stream >> name;
  stream >> value;

  const std::string &fs_name = value;
  if (name == "loadfs2") {
    LoadScriptRcon(fs_name);
  } else if (name == "unloadfs2") {
    UnloadScriptRcon(fs_name);
  } else if (name == "reloadfs2") {
    LoadScriptRcon(fs_name);
    UnloadScriptRcon(fs_name);
  }
}

} // namespace ufs
