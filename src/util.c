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
#include <sampgdk/amx.h>

#include <string.h>

#include "util.h"

static unsigned char *get_data_ptr(AMX *amx) {
	return amx->data != 0 
		? amx->data 
		: amx->base + ((AMX_HEADER*)amx->base)->dat;
}

static cell *get_stack_ptr(AMX *amx) {
	return (cell*)(get_data_ptr(amx) + amx->stk);
}

cell read_amx_stack_cell(AMX *amx, int index) {
	return get_stack_ptr(amx)[index];
}

bool read_amx_stack_bool(AMX *amx, int index) {
	return (bool)read_amx_stack_cell(amx, index);
}

float read_amx_stack_float(AMX *amx, int index) {
	cell value;

	value = read_amx_stack_cell(amx, index);
	return amx_ctof(value);
}

char *read_amx_stack_string(AMX *amx, int index) {
	cell amx_addr;
	cell *phys_addr;
	int length;
	char *string;
	
	amx_addr = read_amx_stack_cell(amx, index);
	if (amx_GetAddr(amx, amx_addr, &phys_addr) != AMX_ERR_NONE) {
		return NULL;
	}
	
	amx_StrLen(phys_addr, &length);
	string = malloc((length + 1) * sizeof(char));
	
	if (amx_GetString(string, phys_addr, 0, length + 1) != AMX_ERR_NONE) {
		free(string);
		return NULL;
	}

	return string;
}

void hook_native(AMX *amx, const char *name, AMX_NATIVE address) {
	AMX_HEADER *hdr;
	AMX_FUNCSTUBNT *cur;
	AMX_FUNCSTUBNT *end;

	hdr = (AMX_HEADER*)(amx->base);
	cur = (AMX_FUNCSTUBNT*)(amx->base + hdr->natives);
	end = (AMX_FUNCSTUBNT*)(amx->base + hdr->libraries);

	while (cur < end) {
		if (strcmp((char*)(cur->nameofs + amx->base), name) == 0) {
			cur->address = (cell)address;
			break;
		}
		cur++;
	}
}
