#include <sampgdk/plugin.h>
#include "plugin.h"

#ifdef _WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

Plugin_::Plugin_()
	: loaded_(false)
{
}

Plugin_::Plugin_(const std::string &filename)
	: loaded_(false)
	, filename_(filename)
{
}

Plugin_::Plugin_(const std::string &filename, void **ppData)
	: loaded_(false)
{
	Load(filename_, ppData);
}

Plugin_::~Plugin_() {
	Unload();
}

PluginError Plugin_::Load(void **ppData) {
	if (!filename_.empty()) {
		return Load(filename_, ppData);
	}
	return PLUGIN_ERROR_LOAD;
}

PluginError Plugin_::Load(const std::string &filename, void **ppData) {
	if (!loaded_) {
		#ifdef _WIN32
			handle_ = (void*)LoadLibrary(filename.c_str());
		#else
			handle_ = dlopen(filename.c_str(), RTLD_NOW);
		#endif
		if (handle_ == 0) {
			return PLUGIN_ERROR_LOAD;
		}
		Supports_t Supports = (Supports_t)GetSymbol("Supports");
		if (Supports != 0) {
			unsigned int flags = Supports();
			if ((flags & SUPPORTS_VERSION_MASK) > SUPPORTS_VERSION) {
				return PLUGIN_ERROR_VERSION;
			}
			if ((flags & SUPPORTS_AMX_NATIVES) != 0) {
				AmxLoad_ = (AmxLoad_t)GetSymbol("AmxLoad");
				if (AmxLoad_ == 0) {
					return PLUGIN_ERROR_API;
				}
				AmxUnload_ = (AmxUnload_t)GetSymbol("AmxUnload");
				if (AmxUnload_ == 0) {
					return PLUGIN_ERROR_API;
				}
			} else {
				AmxLoad_ = AmxUnload_ = 0;
			}
			if ((flags & SUPPORTS_PROCESS_TICK) != 0) {
				ProcessTick_ = (ProcessTick_t)GetSymbol("ProcessTick");
				if (ProcessTick_ == 0) {
					return PLUGIN_ERROR_API;
				}
			} else {
				ProcessTick_ = 0;
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
	}
	return PLUGIN_ERROR_LOAD;
}

void Plugin_::Unload() {
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

void *Plugin_::GetSymbol(const std::string &name) const {
	#ifdef _WIN32
		return (void*)GetProcAddress((HMODULE)handle_, name.c_str());
	#else
		return dlsym(handle_, name.c_str());
	#endif
}

int Plugin_::AmxLoad(AMX *amx) const {
	if (AmxLoad_ != 0) {
		return AmxLoad_(amx);
	}
	return AMX_ERR_NONE;
}

int Plugin_::AmxUnload(AMX *amx) const {
	if (AmxUnload_ != 0) {
		return AmxUnload_(amx);
	}
	return AMX_ERR_NONE;
}

void Plugin_::ProcessTick() const {
	if (ProcessTick_ != 0) {
		ProcessTick_();
	}
}