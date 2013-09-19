#ifndef UFS_PLUGIN_H
#define UFS_PLUGIN_H

#include <string>
#include <sampgdk/amx.h>
#include <sampgdk/plugin.h>

namespace ufs {

#ifdef _WIN32
  const std::string PluginExtension = ".dll";
#else
  const std::string PluginExtension = ".so";
#endif

enum PluginError {
  PLUGIN_ERROR_OK,
  PLUGIN_ERROR_LOAD,
  PLUGIN_ERROR_VERSION,
  PLUGIN_ERROR_API
};

class Plugin {
 public:
  typedef unsigned int (PLUGIN_CALL *Supports_t)();
  typedef bool (PLUGIN_CALL *Load_t)(void **ppData);
  typedef void (PLUGIN_CALL *Unload_t)();
  typedef int (PLUGIN_CALL *AmxLoad_t)(AMX *amx);
  typedef int (PLUGIN_CALL *AmxUnload_t)(AMX *amx);
  typedef void (PLUGIN_CALL *ProcessTick_t)();

  Plugin();
  explicit Plugin(const std::string &filename);
  Plugin(const std::string &filename, void **ppData);
  ~Plugin();

  PluginError Load(void **ppData);
  PluginError Load(const std::string &filename, void **ppData);
  void Unload();

  void *GetSymbol(const std::string &name) const;

  bool IsLoaded() const { return loaded_; }
  operator bool() const { return IsLoaded(); }

  int AmxLoad(AMX *amx) const;
  int AmxUnload(AMX *amx) const;
  void ProcessTick() const;

 private:
  Plugin(const Plugin &other);
  void operator=(const Plugin &other);

 private:
  std::string filename_;
  void *handle_;
  bool loaded_;
  AmxLoad_t AmxLoad_;
  AmxUnload_t AmxUnload_;
  ProcessTick_t ProcessTick_;
};

} // namespace samp

#endif // UFS_PLUGIN_H
