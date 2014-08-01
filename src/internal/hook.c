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
  typedef __int32 _sampgdk_hook_intptr_t;
#else
  #include <stdint.h>
  typedef intptr_t _sampgdk_hook_intptr_t;
#endif

#define _SAMPGDK_HOOK_JMP_OPCODE 0xE9

#pragma pack(push, 1)

struct _sampgdk_hook_jmp {
  unsigned char          opcpde;
  _sampgdk_hook_intptr_t offset;
};

#pragma pack(pop)

struct _sampgdk_hook {
  void *src;
  void *dst;
  unsigned char code[sizeof(struct _sampgdk_hook_jmp)];
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
  _sampgdk_hook_intptr_t pagesize;

  pagesize = sysconf(_SC_PAGESIZE);
  address = (void *)((_sampgdk_hook_intptr_t)address & ~(pagesize - 1));

  if (mprotect(address, size, PROT_READ | PROT_WRITE | PROT_EXEC) != 0)
    return NULL;

  return address;
}

#endif /* !SAMPGDK_WINDOWS */

sampgdk_hook_t sampgdk_hook_new(void *src, void *dst) {
  struct _sampgdk_hook *hook;

  if ((hook = malloc(sizeof(*hook))) == NULL)
    return NULL;

  hook->src = src;
  hook->dst = dst;
  memcpy(hook->code, src, sizeof(hook->code));

  _sampgdk_hook_unprotect(src, sizeof(struct _sampgdk_hook_jmp));

  return (sampgdk_hook_t)hook;
}

void sampgdk_hook_free(sampgdk_hook_t hook) {
  free(hook);
}

void sampgdk_hook_install(sampgdk_hook_t hook) {
  struct _sampgdk_hook_jmp jmp;

  jmp.opcpde = _SAMPGDK_HOOK_JMP_OPCODE;
  jmp.offset =  (_sampgdk_hook_intptr_t)hook->dst - (
                (_sampgdk_hook_intptr_t)hook->src + sizeof(jmp));

  memcpy(hook->src, &jmp, sizeof(jmp));
}

void sampgdk_hook_remove(sampgdk_hook_t hook) {
  memcpy(hook->src, hook->code, sizeof(hook->code));
}
