/* Copyright (C) 2012-2013 Zeex
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

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>

#include <stdlib.h>

static unsigned char *get_arg_data_ptr(AMX *amx) {
	return amx->data != 0 
		? amx->data 
		: amx->base + ((AMX_HEADER*)amx->base)->dat;
}

static cell *get_arg_stack_ptr(AMX *amx) {
	return (cell*)(get_arg_data_ptr(amx) + amx->stk);
}

cell amx_stack_get_arg_cell(AMX *amx, int index) {
	return get_arg_stack_ptr(amx)[index];
}

bool amx_stack_get_arg_bool(AMX *amx, int index) {
	return (bool)amx_stack_get_arg_cell(amx, index);
}

float amx_stack_get_arg_float(AMX *amx, int index) {
	cell value;

	value = amx_stack_get_arg_cell(amx, index);
	return amx_ctof(value);
}

char *amx_stack_get_arg_string(AMX *amx, int index) {
	cell amx_addr;
	cell *phys_addr;
	int length;
	char *string;
	
	amx_addr = amx_stack_get_arg_cell(amx, index);
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

