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

#include <Windows.h>

void *plugin_address_to_handle(void *address) {
	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery(address, &mbi, sizeof(mbi));
	return (void*)mbi.AllocationBase;
}

void *plugin_find_symbol(void *plugin, const char *name)  {
	return (void*)GetProcAddress((HMODULE)plugin, name);
}
