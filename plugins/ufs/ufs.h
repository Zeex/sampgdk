#ifndef UFS_UFS_H
#define UFS_UFS_H

#include <map>
#include <sampgdk/core.hpp>
#include "plugin.h"
#include "script.h"

namespace ufs {

class UFS {
 public:
  typedef std::map<std::string, Plugin*> Plugins;
  typedef std::map<std::string, Script*> Scripts;

  static UFS &Instance();

  ~UFS();

  bool LoadPlugin(const std::string &name, PluginError &error);
  void LoadPlugins();

  void UnloadPlugin(ufs::Plugin *plugin);
  void UnloadPlugins();

  bool LoadScript(const std::string &name);
  void LoadScripts();

  bool UnloadScript(Script *fs);
  bool UnloadScript(const std::string &name);
  void UnloadScripts();

  template<typename F>
  void ForEachPlugin(const F &f) {
    for (Plugins::iterator it = plugins_.begin();
         it != plugins_.end(); it++) {
      f(it->second);
    }
  }

  template<typename F>
  void ForEachScript(const F &f) {
    for (Scripts::iterator it = scripts_.begin();
         it != scripts_.end(); it++) {
      f(it->second);
    }
  }

  template<typename F>
  bool ForEachScript(const F &f, bool while_retval) {
    for (Scripts::iterator it = scripts_.begin();
         it != scripts_.end(); it++) {
      if (f(it->second) != while_retval) {
        return !while_retval;
      }
    }
    return while_retval;
  }

 private:
  UFS() {}
  UFS(const UFS &);
  void operator=(const UFS &);

 private:
  Plugins plugins_; 
  Scripts scripts_;
};

} // namespace ufs

#endif // UFS_UFS_H
