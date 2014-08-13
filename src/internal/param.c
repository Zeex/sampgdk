/* Copyright (C) 2012-2014 Zeex
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

#include <assert.h>
#include <stdlib.h>

#include "amx.h"
#include "param.h"

static unsigned char *_sampgdk_param_get_data(AMX *amx) {
  if (amx->data != 0) {
    return amx->data;
  } else {
    return amx->base + ((AMX_HEADER *)amx->base)->dat;
  }
}

static cell *_sampgdk_param_get_stack(AMX *amx) {
  return (cell *)(_sampgdk_param_get_data(amx) + amx->stk);
}

static cell _sampgdk_param_get_by_index(AMX *amx, int index) {
  return _sampgdk_param_get_stack(amx)[index];
}

void sampgdk_param_get_all(AMX *amx, bool exec, cell **params) {
  assert(params != NULL);
  if (exec) {
    *params = _sampgdk_param_get_stack(amx) - 1;
    *params[0] = amx->paramcount * sizeof(cell);
  } else {
    *params = _sampgdk_param_get_stack(amx);
  }
}

void sampgdk_param_get_cell(AMX *amx, int index, cell *param) {
  assert(param != NULL);
  *param = _sampgdk_param_get_by_index(amx, index);
}

void sampgdk_param_get_bool(AMX *amx, int index, bool *param) {
  assert(param != NULL);
  *param = !!_sampgdk_param_get_by_index(amx, index);
}

void sampgdk_param_get_float(AMX *amx, int index, float *param) {
  cell p = _sampgdk_param_get_by_index(amx, index);
  assert(param != NULL);
  *param = amx_ctof(p);
}

void sampgdk_param_get_string(AMX *amx, int index, char **param) {
  cell amx_addr;
  cell *phys_addr;
  int length;
  char *string;

  amx_addr = _sampgdk_param_get_by_index(amx, index);
  if (amx_GetAddr(amx, amx_addr, &phys_addr) != AMX_ERR_NONE) {
    return;
  }
 
  amx_StrLen(phys_addr, &length);
  string = malloc((length + 1) * sizeof(char));

  if (amx_GetString(string, phys_addr, 0, length + 1) != AMX_ERR_NONE) {
    free(string);
    return;
  }

  assert(param != NULL);
  *param = string;
}
