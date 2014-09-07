#include <sampgdk/sdk.h>
#include "plugin.h"

#ifdef _WIN32
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif

namespace ufs {

Plugin::Plugin()
 : loaded_(false),
   handle_(0),
   AmxLoad_(0),
   AmxUnload_(0),
   ProcessTick_(0)
{
}

Plugin::Plugin(const std::string &filename)
 : filename_(filename),
   loaded_(false),
   handle_(0),
   AmxLoad_(0),
   AmxUnload_(0),
   ProcessTick_(0)
{
}

Plugin::~Plugin() {
  Unload();
}

PluginError Plugin::Load(void **ppData) {
  if (!filename_.empty()) {
    return Load(filename_, ppData);
  }
  return PLUGIN_ERROR_FAILED;
}

PluginError Plugin::Load(const std::string &filename, void **ppData) {
  if (!loaded_) {
    #ifdef _WIN32
      handle_ = (void*)LoadLibraryA(filename.c_str());
    #else
      handle_ = dlopen(filename.c_str(), RTLD_NOW);
    #endif

    if (handle_ == 0) {
      return PLUGIN_ERROR_FAILED;
    }

    Supports_t Supports = (Supports_t)GetSymbol("Supports");
    if (Supports == 0) {
      return PLUGIN_ERROR_FAILED;
    }

    unsigned int flags = Supports();

    if ((flags & SUPPORTS_VERSION_MASK) > SUPPORTS_VERSION) {
      return PLUGIN_ERROR_VERSION;
    }

    if ((flags & SUPPORTS_AMX_NATIVES) != 0) {
      if ((AmxLoad_ = (AmxLoad_t)GetSymbol("AmxLoad")) == 0
          || (AmxUnload_ = (AmxUnload_t)GetSymbol("AmxUnload")) == 0) {
        return PLUGIN_ERROR_API;
      }
    }

    if ((flags & SUPPORTS_PROCESS_TICK) != 0) {
      ProcessTick_ = (ProcessTick_t)GetSymbol("ProcessTick");
      if (ProcessTick_ == 0) {
        return PLUGIN_ERROR_API;
      }
    }

    Load_t Load = (Load_t)GetSymbol("Load");
    if (Load == 0) {
      return PLUGIN_ERROR_API;
    }

    if (Load(ppData)) {
      filename_ = filename;
      loaded_ = true;
      return PLUGIN_ERROR_OK;
    }
  }

  return PLUGIN_ERROR_FAILED;
}

void Plugin::Unload() {
  if (loaded_) {
    Unload_t Unload = (Unload_t)GetSymbol("Unload");
    if (Unload != 0) {
      Unload();
    }
    #ifdef _WIN32
      FreeLibrary((HMODULE)handle_);
    #else
      dlclose(handle_);
    #endif
  }
}

void *Plugin::GetSymbol(const std::string &name) const {
  #ifdef _WIN32
    return (void *)GetProcAddress((HMODULE)handle_, name.c_str());
  #else
    return dlsym(handle_, name.c_str());
  #endif
}

int Plugin::AmxLoad(AMX *amx) const {
  if (AmxLoad_ != 0) {
    return AmxLoad_(amx);
  }
  return AMX_ERR_NONE;
}

int Plugin::AmxUnload(AMX *amx) const {
  if (AmxUnload_ != 0) {
    return AmxUnload_(amx);
  }
  return AMX_ERR_NONE;
}

void Plugin::ProcessTick() const {
  if (ProcessTick_ != 0) {
    ProcessTick_();
  }
}

} // namespace samp
