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

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sampgdk/platform.h>

#if SAMPGDK_WINDOWS
  #include <windows.h>
#else
  #include <stdint.h>
  #include <unistd.h>
  #include <sys/mman.h>
#endif

#include "hook.h"

#if defined _MSC_VER
  typedef __int32 int32_t;
  typedef __int32 intptr_t;
#else
  #include <stdint.h>
#endif

#define _SAMPGDK_JMP_OPCODE 0xE9

static const unsigned char jmp_opcode = _SAMPGDK_JMP_OPCODE;
static const unsigned char jmp_instr[] =
  { _SAMPGDK_JMP_OPCODE, 0x0, 0x0, 0x0, 0x0 };

struct _sampgdk_hook {
  void *src;
  void *dst;
  unsigned char code[sizeof(jmp_instr)];
};

#if SAMPGDK_WINDOWS

static void *_sampgdk_hook_unprotect(void *address, size_t size) {
  DWORD old;

  if (VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &old) == 0)
    return NULL;

  return address;
}

#else /* SAMPGDK_WINDOWS */

static void *_sampgdk_hook_unprotect(void *address, size_t size) {
  intptr_t pagesize;

  pagesize = sysconf(_SC_PAGESIZE);
  address = (void *)((intptr_t)address & ~(pagesize - 1));

  if (mprotect(address, size, PROT_READ | PROT_WRITE | PROT_EXEC) != 0)
    return NULL;

  return address;
}

#endif /* !SAMPGDK_WINDOWS */

sampgdk_hook_t sampgdk_hook_new(void *src, void *dst) {
  struct _sampgdk_hook *hook;

  if ((hook = calloc(1, sizeof(*hook))) == NULL)
    return NULL;

  hook->src = src;
  hook->dst = dst;

  _sampgdk_hook_unprotect(src, sizeof(jmp_instr));

  return (sampgdk_hook_t)hook;
}

void sampgdk_hook_free(sampgdk_hook_t hook) {
  free(hook);
}

void sampgdk_hook_install(sampgdk_hook_t hook) {
  intptr_t offset;

  memcpy(hook->code, hook->src, sizeof(jmp_instr));
  memcpy(hook->src, &jmp_instr, sizeof(jmp_instr));

  offset = (intptr_t)hook->dst
         - ((intptr_t)hook->src + sizeof(jmp_instr));

  memcpy((void *)((intptr_t)hook->src + sizeof(jmp_opcode)),
         &offset,
         sizeof(jmp_instr) - sizeof(jmp_opcode));
}

void sampgdk_hook_remove(sampgdk_hook_t hook) {
  memcpy(hook->src, hook->code, sizeof(jmp_instr));
}
