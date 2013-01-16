#!/usr/bin/env python
#
# Copyright (C) 2012 Zeex
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import cidl
import itertools
import os
import sys

EXPORT_PREFIX = 'sampgdk_'

idl_to_c_type_in = {
  'int'    : 'int',
  'bool'   : 'bool',
  'float'  : 'float',
  'char'   : 'char',
  'string' : 'const char *'
}

idl_to_c_type_out = {
  'int'    : 'int *',
  'bool'   : 'bool *',
  'float'  : 'float *',
  'char'   : 'char *',
  'string' : 'char **'
}

class Parameter(cidl.Parameter):
  def __init__(self, type, name, attrlist=None):
    cidl.Parameter.__init__(self, type, name, attrlist)

  @property
  def c_type(self):
    try:
      if self.is_out:
        return idl_to_c_type_out[self.type]
      if self.is_in:
        return idl_to_c_type_in[self.type]
    except KeyError:
      if self.is_out:
        return '%s *' % self.type
      if self.is_in:
        return self.type
    return None

  @property
  def is_ref(self):
    return self.is_out or self.type == 'string'

  @property
  def is_value(self):
    return not self.is_ref

class Value(cidl.Value):
  def __init__(self, type, data):
    cidl.Value.__init__(self, type, data)

  def as_string(self):
    if self.is_bool():
      return ('false', 'true')[self.data]
    elif self.is_int():
      if self.is_hex():
        return '0x%s' % hex(self.data)[2:].upper()
      elif self.is_oct():
        return '%s' % oct(self.data)
      return '%s' % int(self.data)
    elif self.is_float():
      return '%s' % self.data
    elif self.is_char():
      return '\'%s\'' % self.data
    elif self.is_string():
      return '"%s"' % self.data
    return None

  def __str__(self):
    string = self.as_string()
    if string is None:
      return '_codegen_invalid_literal_'
    return string

class ParamList:
  def __init__(self, params):
    self._params = params

  def __str__(self):
    return ', '.join(['%s %s' % (p.c_type, p.name) for p in self._params])

class ArgList:
  def __init__(self, params):
    self._params = params
  
  def __str__(self):
    return ', '.join(['%s' % p.name for p in self._params])

def previous_and_next(iterable):
    prevs, items, nexts = itertools.tee(iterable, 3)
    prevs = itertools.chain([None], prevs)
    nexts = itertools.chain(itertools.islice(nexts, 1, None), [None])
    return itertools.izip(prevs, items, nexts)

def gen_constants(idl, hdr):
  if hdr is not None:
    for c in idl.constants:
      hdr.write('#define %s (%s)\n' % (c.name, c.value))
    hdr.write('\n')

def gen_natives(idl, hdr, src, api):
  natives = filter(lambda x: x.has_attr('native'), idl.functions)
  natives_with_impl = filter(lambda x: not x.has_attr('noimpl'), natives)

  if hdr is not None:
    hdr.write('#ifndef SAMPGDK_NATIVE_EXPORT\n')
    hdr.write('\t#define SAMPGDK_NATIVE_EXPORT SAMPGDK_EXPORT\n')
    hdr.write('#endif\n')

    hdr.write('#ifndef SAMPGDK_NATIVE_CALL\n')
    hdr.write('\t#define SAMPGDK_NATIVE_CALL SAMPGDK_CALL\n')
    hdr.write('#endif\n')

    hdr.write('#ifndef SAMPGDK_NATIVE\n')
    hdr.write('\t#define SAMPGDK_NATIVE(type, func) \\\n')
    hdr.write('\t\tSAMPGDK_NATIVE_EXPORT type SAMPGDK_NATIVE_CALL %s##func\n' % EXPORT_PREFIX)
    hdr.write('#endif\n')

    hdr.write('\n')

    for f in natives:
      hdr.write('SAMPGDK_NATIVE_EXPORT %s SAMPGDK_NATIVE_CALL %s%s(%s);\n' % (f.type, EXPORT_PREFIX, f.name, ParamList(f.params)))
      hdr.write('#undef  %s\n' % f.name)
      hdr.write('#define %s %s%s\n\n' % (f.name, EXPORT_PREFIX, f.name))

    hdr.write('\n')

  if src is not None:
    for f in natives_with_impl:
      src.write('SAMPGDK_NATIVE_EXPORT %s SAMPGDK_NATIVE_CALL %s%s(%s) {\n' % (f.type, EXPORT_PREFIX, f.name, ParamList(f.params)))
      src.write('\tstatic AMX_NATIVE native;\n')
      src.write('\tstruct fakeamx *fa;\n')
      src.write('\t%s retval;\n' % f.type)

      if f.params:
        src.write('\tcell params[%d];\n' % (len(f.params) + 1))

        # Define local vaiables to store AMX heap addresses.
        for p in filter(lambda p: p.is_ref, f.params):
          src.write('\tcell %s_;\n' % p.name)

      src.write('\tif (unlikely(native == NULL))\n')
      src.write('\t\tnative = native_lookup_warn_stub("%s");\n' % f.name)

      src.write('\tfakeamx_instance(&fa);\n')

      if f.params:
        # Call to fakeamx_push() for parameters.
        for pprev, p, pnext in previous_and_next(f.params):
          if p.is_ref:
            if p.type == 'char': # output string (const char *)
              src.write('\tfakeamx_push(fa, %s, &%s_);\n' % (pnext.name, p.name))
            elif p.type == 'string': # input string (char *)
              src.write('\tfakeamx_push_string(fa, %s, NULL, &%s_);\n' % (p.name, p.name))
            else:
              src.write('\tfakeamx_push(fa, 1, &%s_);\n' % p.name)

        # Fill the params array.
        src.write('\tparams[0] = %d * sizeof(cell);\n' % len(f.params))
        for index, p in enumerate(f.params, 1):
          if p.is_value:
            src.write('\tparams[%d] = %s;\n' % (index, 
              {
                'int'   : '(cell)%s' % p.name,
                'bool'  : '(cell)%s' % p.name,
                'char'  : '(cell)%s' % p.name,
                'float' : 'amx_ftoc(%s)' % p.name,
              }[p.type]
            ))
          else:
            src.write('\tparams[%d] = %s_;\n' % (index, p.name))

      src.write('\tretval = (%s)native(&fa->amx, %s);\n' % (f.type, ('NULL', 'params')[bool(f.params)]))

      if f.params:
        # Copy data to output arguments.
        for pprev, p, pnext in previous_and_next(f.params):
          if p.is_ref:
            if p.type == 'string':
              pass
            elif p.type == 'char':
              src.write('\tfakeamx_get_string(fa, %s_, %s, %s);\n' % (p.name, p.name, pnext.name))
            else:
              src.write('\tfakeamx_get_%s(fa, %s_, %s);\n' % (
                {
                  'int'   : "cell",
                  'bool'  : "bool",
                  'float' : "float"
                }[p.type]
              ,  
              p.name, p.name))

        # Free previously allocated heap space (in reverse order).
        for p in reversed(filter(lambda p: p.is_ref, f.params)):
          src.write('\tfakeamx_pop(fa, %s_);\n' % p.name)

      src.write('\treturn retval;\n')
      src.write('}\n\n')

    src.write('\n')

  if api is not None:
    for f in natives:
      api.write('%s%s\n' % (EXPORT_PREFIX, f.name))

def gen_callbacks(idl, hdr, src):
  callbacks = filter(lambda x: x.has_attr('callback'), idl.functions)

  if hdr is not None:
    hdr.write('#ifndef SAMPGDK_CALLBACK_EXPORT\n')
    hdr.write('\t#define SAMPGDK_CALLBACK_EXPORT PLUGIN_EXPORT\n')
    hdr.write('#endif\n')

    hdr.write('#ifndef SAMPGDK_CALLBACK_CALL\n')
    hdr.write('\t#define SAMPGDK_CALLBACK_CALL PLUGIN_CALL\n')
    hdr.write('#endif\n')

    hdr.write('#ifndef SAMPGDK_CALLBACK\n')
    hdr.write('\t#define SAMPGDK_CALLBACK(type, func) \\\n')
    hdr.write('\t\tSAMPGDK_CALLBACK_EXPORT type SAMPGDK_CALLBACK_CALL func\n')
    hdr.write('#endif\n')

    hdr.write('\n')

    for f in callbacks:
      hdr.write('SAMPGDK_CALLBACK_EXPORT %s SAMPGDK_CALLBACK_CALL %s(%s);\n' %
                   (f.type, f.name, ParamList(f.params)))

  if src is not None:
    for f in callbacks:
      src.write('typedef %s (PLUGIN_CALL *%s_type)(%s);\n' % (f.type, f.name, ParamList(f.params)))
      src.write('bool %s_handler(AMX *amx, void *callback, cell *retval) {\n' %
                f.name)

      badret = f.get_attr('badret')
      if badret is not None:
        src.write('\tbool retval_;\n')

      # Declare local variables for temporary storage of callback arguments.
      for p in f.params:
        src.write('\t%s %s;\n' % (p.c_type, p.name))

      # Copy parameters from AMX stack.
      for index, p in enumerate(f.params):
        src.write('\t%s = amx_stack_get_arg_%s(amx, %d);\n' % (p.name,
          {
            'int'    : 'cell',
            'bool'   : 'bool',
            'float'  : 'float',
            'char'   : 'char',
            'string' : 'string'
          }[p.type], index)
        )

      # Invoke the callback function.
      if badret is not None:
        src.write('\tretval_ = ((%s_type)callback)(%s);\n' % (f.name, ArgList(f.params)))
        src.write('\tif (retval != NULL)\n')
        src.write('\t\t*retval = (cell)retval_;\n')
      else:
        src.write('\t((%s_type)callback)(%s);\n' %
                     (f.name, ArgList(f.params)))

      # Free the memory allocated for strings.
      for p in filter(lambda p: p.type == 'string', f.params):
        src.write('\tfree((void*)%s);\n' % p.name)

      if badret is not None:
        src.write('\treturn (retval_ != %s);\n' % badret.value)
      else:
        src.write('\treturn true;\n')

      src.write('}\n\n')

    src.write('int register_callbacks() {\n')
    src.write('\tint error;\n')

    for f in callbacks:
      src.write('\tif ((error = callback_add_handler("%s", %s_handler)) < 0)\n' % (f.name, f.name))
      src.write('\t\treturn error;\n')

    src.write('\t(void)error;\n')
    src.write('\treturn 0;\n')
    src.write('}\n\n')
    
def main(argv):
  argparser = argparse.ArgumentParser()

  argparser.add_argument('--idl', dest='idl_file', metavar='filename', required=True)
  argparser.add_argument('--header', dest='header_file', metavar='filename')
  argparser.add_argument('--source', dest='source_file', metavar='filename')
  argparser.add_argument('--api', dest='api_file', metavar='filename')
  argparser.add_argument('--constants', dest='gen_constants', action='store_true')
  argparser.add_argument('--natives', dest='gen_natives', action='store_true')
  argparser.add_argument('--callbacks', dest='gen_callbacks', action='store_true')
  argparser.add_argument('--all', dest='gen_all', action='store_true')

  args = argparser.parse_args(argv[1:])

  try:
    idlparser = cidl.Parser(value_class=Value, param_class=Parameter)
    idl = idlparser.parse(open(args.idl_file, 'r').read())

    def ensure_dir(filename):
      directory = os.path.dirname(filename)
      if not os.path.exists(directory):
        os.makedirs(directory)

    hdr = None
    if args.header_file is not None:
      ensure_dir(args.header_file)
      hdr = open(args.header_file, 'w')
    src = None
    if args.source_file is not None:
      ensure_dir(args.source_file)
      src = open(args.source_file, 'w')
    api = None
    if args.api_file is not None:
      ensure_dir(args.api_file)
      api = open(args.api_file, 'w')

    if args.gen_constants or args.gen_all:
      gen_constants(idl, hdr)
    if args.gen_natives or args.gen_all:
      gen_natives(idl, hdr, src, api)
    if args.gen_callbacks or args.gen_all:
      gen_callbacks(idl, hdr, src)

  except cidl.Error as e:
    sys.stderr.write('%s\n' % e)

if __name__ == '__main__':
  main(sys.argv)
