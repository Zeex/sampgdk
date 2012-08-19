/* Copyright (C) 2011-2012 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sampgdk/config.h>

#ifndef _GNU_SOURCE
	#define _GNU_SOURCE 1
#endif
#include <dlfcn.h>
#include <string.h>

void *plugin_address_to_handle(void *address) {
	Dl_info info;

	dladdr(address, &info);
	return dlopen(info.dli_fname, RTLD_NOW);
}

void *plugin_find_symbol(void *plugin, const char *name)  {
	return dlsym(plugin, name);
}

void plugin_get_file_name(void *plugin, char *name, size_t size) {
	Dl_info info;

	dladdr(plugin, &info);
	strncpy(name, info.dli_fname, size);
}
