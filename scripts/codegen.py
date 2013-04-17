#!/usr/bin/env python
#
# Copyright (C) 2012-2013 Zeex
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

NAMESPACE = 'sampgdk'
EXPORT_PREFIX = NAMESPACE + '_'

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
  def __init__(self, type, name, default=None, attrlist=None):
    cidl.Parameter.__init__(self, type, name, default, attrlist)

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
    return ', '.join(['%s %s' % (p.c_type, p.name) for p in
                      filter(lambda x: x.default is None, self._params)])

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

def generate_api_file(module_name, idl, file):
  natives = filter(lambda x: x.has_attr('native'), idl.functions)
  for f in natives:
    file.write('%s%s\n' % (EXPORT_PREFIX, f.name))

def generate_header_file(module_name, idl, file):
  natives = filter(lambda x: x.has_attr('native'), idl.functions)

  for func in natives:
    generate_native_decl(file, func)
  file.write('\n')

  file.write('#ifndef __cplusplus\n\n')

  for const in idl.constants:
    generate_constant_c(file, const)
  file.write('\n')  
  for func in natives:
    generate_native_alias_c(file, func)
  file.write('\n')

  file.write('#else /* __cplusplus */\n\n')
  file.write('namespace %s {\n\n' % NAMESPACE)

  for const in idl.constants:
    generate_constant_cxx(file, const)
  file.write('\n')
  for func in natives:
    generate_native_alias_cxx(file, func)
  file.write('\n')

  file.write('} // namespace %s\n\n' % NAMESPACE)
  file.write('#endif /* __cplusplus */\n\n')

  callbacks = filter(lambda x: x.has_attr('callback'), idl.functions)
  for func in callbacks:
    generate_callback_decl(file, func)

def generate_source_file(module_name, idl, file):
  file.write(
    '#include <sampgdk/export.h>\n'
    '\n'
    '#include "private/amx-stack.h"\n'
    '#include "private/callback.h"\n'
    '#include "private/fakeamx.h"\n'
    '#include "private/init.h"\n'
    '#include "private/likely.h"\n'
    '#include "private/native.h"\n'
  )

  file.write('\n')

  natives = filter(lambda x: x.has_attr('native') and not x.has_attr('noimpl'),
                   idl.functions)
  for func in natives:
    generate_native_impl(file, func)
    file.write('\n')

  callbacks = filter(lambda x: x.has_attr('callback'), idl.functions)
  for func in callbacks:
    generate_callback_impl(file, func);
    file.write('\n')

  file.write('static const struct callback_info callback_table[] = {\n')

  for func in sorted(callbacks, key=lambda x: x.name, reverse=True):
    file.write('\t"%s", %s_handler,\n' % (func.name, func.name))

  file.write('\tNULL, NULL\n')
  file.write('};\n\n')

  file.write('DEFINE_INIT_FUNC(%s_init) {\n' % module_name)
  file.write('\treturn callback_register_table(callback_table);\n')
  file.write('}\n')

  file.write('DEFINE_CLEANUP_FUNC(%s_cleanup) {\n' % module_name)
  file.write('\tcallback_unregister_table(callback_table);\n')
  file.write('}\n')

def generate_constant_c(file, const):
  file.write('#define %s (%s)\n' % (const.name, const.value))

def generate_constant_cxx(file, const):
  file.write('const %s %s = %s;\n' % (const.type, const.name, const.value))

def generate_native_decl(file, func):
  file.write('SAMPGDK_NATIVE_EXPORT %s SAMPGDK_NATIVE_CALL %s%s(%s);\n'
             % (func.type, EXPORT_PREFIX, func.name, ParamList(func.params)))

def generate_native_alias_c(file, func):
  file.write('#undef  %s\n' % func.name)
  file.write('#define %s %s%s\n' % (func.name, EXPORT_PREFIX, func.name))

def generate_native_alias_cxx(file, func):
  file.write('static inline %s %s(%s) {\n' % (func.type, func.name, ParamList(func.params)))
  if func.type != 'void':
    file.write('\treturn ::%s%s(%s);\n' % (EXPORT_PREFIX, func.name, ArgList(func.params)))
  else:
    file.write('\t::%s%s(%s);\n' % (EXPORT_PREFIX, func.name, ArgList(func.params)))
  file.write('}\n')

def generate_native_impl(file, func):
  file.write('SAMPGDK_NATIVE_EXPORT %s SAMPGDK_NATIVE_CALL %s%s(%s) {\n' %
             (func.type, EXPORT_PREFIX, func.name, ParamList(func.params)))
  file.write('\tstatic AMX_NATIVE native;\n')
  file.write('\tstruct fakeamx *fa;\n')
  file.write('\tcell retval;\n')

  if func.params:
    file.write('\tcell params[%d];\n' % (len(func.params) + 1))

    for p in filter(lambda p: p.is_ref, func.params):
      file.write('\tcell %s_;\n' % p.name)

  file.write('\tif (unlikely(native == NULL))\n')
  file.write('\t\tnative = native_lookup_warn_stub("%s");\n' % func.name)

  file.write('\tfa = fakeamx_global();\n')

  if func.params:
    for pprev, p, pnext in previous_and_next(func.params):
      if p.is_ref:
        if p.default is not None:
          value = p.default
        else:
          value = p.name
        if p.type == 'char':
          file.write('\tfakeamx_heap_push(fa, %s, &%s_);\n' % (pnext.name, p.name))
        elif p.type == 'string':
          file.write('\tfakeamx_heap_push_string(fa, %s, NULL, &%s_);\n' % (value, p.name))
        else:
          file.write('\tfakeamx_heap_push(fa, 1, &%s_);\n' % p.name)

    file.write('\tparams[0] = %d * sizeof(cell);\n' % len(func.params))
    for index, p in enumerate(func.params, 1):
      if p.is_value:
        if p.default is not None:
          value = p.default
        else:
          value = p.name
        file.write('\tparams[%d] = %s;\n' % (index, 
          {
            'int'   : '(cell)%s' % value,
            'bool'  : '(cell)%s' % value,
            'char'  : '(cell)%s' % value,
            'float' : 'amx_ftoc(%s)' % value,
          }[p.type]
        ))
      else:
        file.write('\tparams[%d] = %s_;\n' % (index, p.name))


  file.write('\tretval = native(&fa->amx, %s);\n' %
             ('NULL', 'params')[bool(func.params)])

  if func.params:
    for pprev, p, pnext in previous_and_next(func.params):
      if p.is_ref:
        if p.type == 'string':
          pass
        elif p.type == 'char':
          file.write('\tfakeamx_heap_get_string(fa, %s_, %s, %s);\n' %
                     (p.name, p.name, pnext.name))
        else:
          file.write('\tfakeamx_heap_get_%s(fa, %s_, %s);\n' % (
            {
              'int'   : 'cell',
              'bool'  : 'bool',
              'float' : 'float',
            }[p.type]
          ,  
          p.name, p.name))

    for p in reversed(filter(lambda p: p.is_ref, func.params)):
      file.write('\tfakeamx_heap_pop(fa, %s_);\n' % p.name)

  file.write('\treturn %s(retval);\n' % ({
      'int'   : '(int)',
      'bool'  : '(bool)',
      'float' : 'amx_ctof',
    }[func.type]
  ))

  file.write('}\n')

def generate_callback_decl(file, func):
    file.write('SAMPGDK_CALLBACK_EXPORT %s SAMPGDK_CALLBACK_CALL %s(%s);\n' %
               (func.type, func.name, ParamList(func.params)))

def generate_callback_impl(file, func):
  file.write('typedef %s (SAMPGDK_CALLBACK_CALL *%s_type)(%s);\n' %
             (func.type, func.name, ParamList(func.params)))
  file.write('static bool %s_handler(AMX *amx, void *callback, cell *retval)'
             ' {\n' % func.name)

  badret = func.get_attr('badret')
  if badret is not None:
    file.write('\tbool retval_;\n')

  for p in func.params:
    file.write('\t%s %s;\n' % (p.c_type, p.name))

  for index, p in enumerate(func.params):
    file.write('\t%s = amx_stack_get_arg_%s(amx, %d);\n' % (p.name,
      {
        'int'    : 'cell',
        'bool'   : 'bool',
        'float'  : 'float',
        'char'   : 'char',
        'string' : 'string',
      }[p.type], index)
    )

  if badret is not None:
    file.write('\tretval_ = ((%s_type)callback)(%s);\n' % (func.name, ArgList(func.params)))
    file.write('\tif (retval != NULL)\n')
    file.write('\t\t*retval = (cell)retval_;\n')
  else:
    file.write('\t((%s_type)callback)(%s);\n' %
                 (func.name, ArgList(func.params)))

  for p in filter(lambda p: p.type == 'string', func.params):
    file.write('\tfree((void*)%s);\n' % p.name)

  if badret is not None:
    file.write('\treturn (retval_ != %s);\n' % badret.value)
  else:
    file.write('\treturn true;\n')

  file.write('}\n')

def main(argv):
  argparser = argparse.ArgumentParser()

  argparser.add_argument('--module-name', dest='module_name', metavar='name', required=True)
  argparser.add_argument('--idl-file', dest='idl_file', metavar='path', required=True)
  argparser.add_argument('--api-file', dest='api_file', metavar='path')
  argparser.add_argument('--header-file', dest='header_file', metavar='path')
  argparser.add_argument('--source-file', dest='source_file', metavar='path')

  args = argparser.parse_args(argv[1:])

  try:
    idlparser = cidl.Parser(value_class=Value, param_class=Parameter)
    idl = idlparser.parse(open(args.idl_file, 'r').read())

    def ensure_dir(filename):
      directory = os.path.dirname(filename)
      if not os.path.exists(directory):
        os.makedirs(directory)

    api = None
    if args.api_file is not None:
      ensure_dir(args.api_file)
      with open(args.api_file, 'w') as file:
        generate_api_file(args.module_name, idl, file)

    header = None
    if args.header_file is not None:
      ensure_dir(args.header_file)
      with open(args.header_file, 'w') as file:
        generate_header_file(args.module_name, idl, file)

    source = None
    if args.source_file is not None:
      ensure_dir(args.source_file)
      with open(args.source_file, 'w') as file:
        generate_source_file(args.module_name, idl, file)

  except cidl.Error as e:
    sys.stderr.write('%s\n' % e)

if __name__ == '__main__':
  main(sys.argv)
