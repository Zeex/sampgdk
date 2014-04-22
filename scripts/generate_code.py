#!/usr/bin/env python
#
# Copyright (C) 2012-2014 Zeex
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

idl_to_c_type_in = {
  'int'    : 'int',
  'bool'   : 'bool',
  'float'  : 'float',
  'string' : 'const char *',
}

idl_to_c_type_out = {
  'int'    : 'int *',
  'bool'   : 'bool *',
  'float'  : 'float *',
  'string' : 'char *',
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
    try:
      return itertools.izip(prevs, items, nexts)
    except AttributeError:
      return zip(prevs, items, nexts)

def generate_api_file(module_name, idl, file):
  for f in filter(lambda x: x.has_attr('native'), idl.functions):
    file.write('sampgdk_%s\n' % f.name)

def generate_header_file(module_name, idl, file):
  natives = list(filter(lambda x: x.has_attr('native'),
                        idl.functions))
  file.write('#ifndef DOXYGEN\n')
  for func in natives:
    generate_native_alias(file, func)
  file.write('#endif\n\n')

  for func in natives:
    generate_native_decl(file, func)
  file.write('\n')

  for const in idl.constants:
    generate_constant(file, const)
  file.write('\n')

  callbacks = list(filter(lambda x: x.has_attr('callback'),
                          idl.functions))
  for func in callbacks:
    generate_callback_decl(file, func)

def generate_source_file(module_name, idl, file):
  natives = list(filter(lambda x: x.has_attr('native') and not
                                  x.has_attr('noimpl'),
                        idl.functions))
  for func in natives:
    generate_native_impl(file, func)
    file.write('\n')

  callbacks = list(filter(lambda x: x.has_attr('callback'), idl.functions))
  for func in callbacks:
    generate_callback_impl(file, func);
    file.write('\n')

  file.write('static const struct sampgdk_callback callback_table[] = {\n')

  for func in sorted(callbacks, key=lambda x: x.name, reverse=True):
    file.write('  {"%s", %s_handler},\n' % (func.name, func.name))

  file.write('  {NULL, NULL}\n')
  file.write('};\n\n')

  file.write('SAMPGDK_MODULE_INIT(%s) {\n' % module_name)
  file.write('  return sampgdk_callback_register_table(callback_table);\n')
  file.write('}\n')

  file.write('SAMPGDK_MODULE_CLEANUP(%s) {\n' % module_name)
  file.write('  sampgdk_callback_unregister_table(callback_table);\n')
  file.write('}\n')

def generate_constant(file, const):
  file.write('#define %s (%s)\n' % (const.name, const.value))

def generate_native_decl(file, func):
  file.write('\n')
  file.write('/**\n')
  file.write(' * \\ingroup natives\n')
  file.write(' * \\see <a href="http://wiki.sa-mp.com/wiki/%s">'
             '%s on SA-MP Wiki</a>' % (func.name, func.name))
  file.write(' */\n')
  file.write('SAMPGDK_NATIVE(%s, %s(%s));\n'
             % (func.type, func.name, ParamList(func.params)))

def generate_native_alias(file, func):
  file.write('#undef  %s\n' % func.name)
  file.write('#define %s sampgdk_%s\n' % (func.name, func.name))

def generate_native_impl(file, func):
  file.write('SAMPGDK_NATIVE(%s, %s(%s)) {\n' %
             (func.type, func.name, ParamList(func.params)))
  file.write('  static AMX_NATIVE native;\n')
  file.write('  cell retval;\n')

  if func.params:
    file.write('  cell params[%d];\n' % (len(func.params) + 1))

    for p in filter(lambda p: p.is_ref, func.params):
      file.write('  cell %s_;\n' % p.name)

  file.write('  if (unlikely(native == NULL)) {\n')
  file.write('    native = sampgdk_native_find_warn_stub("%s");\n' % func.name)
  file.write('  }\n')

  if func.params:
    for pprev, p, pnext in previous_and_next(func.params):
      if p.is_ref:
        if p.default is not None:
          value = p.default
        else:
          value = p.name
        if p.type == 'string':
          if p.is_out:
            file.write('  sampgdk_fakeamx_push(%s, &%s_);\n' %
                       (pnext.name, p.name))
          else:
            file.write('  sampgdk_fakeamx_push_string(%s, NULL, &%s_);\n' %
                       (value, p.name))
        else:
          file.write('  sampgdk_fakeamx_push(1, &%s_);\n' % p.name)

    file.write('  params[0] = %d * sizeof(cell);\n' % len(func.params))
    for index, p in enumerate(func.params, 1):
      if p.is_value:
        if p.default is not None:
          value = p.default
        else:
          value = p.name
        file.write('  params[%d] = %s;\n' % (index, 
          {
            'int'   : '(cell)%s' % value,
            'bool'  : '(cell)%s' % value,
            'float' : 'amx_ftoc(%s)' % value,
          }[p.type]
        ))
      else:
        file.write('  params[%d] = %s_;\n' % (index, p.name))


  file.write('  retval = native(sampgdk_fakeamx_amx(), %s);\n' %
             ('NULL', 'params')[bool(func.params)])

  if func.params:
    for pprev, p, pnext in previous_and_next(func.params):
      if p.is_out:
        if p.type == 'string': 
          file.write('  sampgdk_fakeamx_get_string(%s_, %s, %s);\n' %
                     (p.name, p.name, pnext.name))
        else:
          file.write('  sampgdk_fakeamx_get_%s(%s_, %s);\n' % (
            {
              'int'    : 'cell',
              'bool'   : 'bool',
              'float'  : 'float',
              'string' : 'string',
            }[p.type]
          ,  
          p.name, p.name))

    for p in reversed(list(filter(lambda p: p.is_ref, func.params))):
      file.write('  sampgdk_fakeamx_pop(%s_);\n' % p.name)

  file.write('  return %s(retval);\n' % ({
      'int'   : '(int)',
      'bool'  : '(bool)',
      'float' : 'amx_ctof',
    }[func.type]
  ))

  file.write('}\n')

def generate_callback_decl(file, func):
  file.write('\n')
  file.write('/**\n')
  file.write(' * \\ingroup callbacks\n')
  file.write(' * \\see <a href="http://wiki.sa-mp.com/wiki/%s">'
             '%s on SA-MP Wiki</a>' % (func.name, func.name))
  file.write(' */\n')
  file.write('SAMPGDK_CALLBACK(%s, %s(%s));\n' %
               (func.type, func.name, ParamList(func.params)))

def generate_callback_impl(file, func):
  file.write('typedef %s (SAMPGDK_CALLBACK_CALL *%s_type)(%s);\n' %
             (func.type, func.name, ParamList(func.params)))
  file.write('static bool %s_handler(AMX *amx, void *callback, cell *retval)'
             ' {\n' % func.name)

  badret = func.get_attr('badret')
  if badret.value is not None:
    file.write('  bool retval_;\n')

  for p in func.params:
    file.write('  %s %s;\n' % (p.c_type, p.name))

  for index, p in enumerate(func.params):
    file.write('  sampgdk_param_get_%s(amx, %d, (void*)&%s);\n' % ({
        'int'    : 'cell',
        'bool'   : 'bool',
        'float'  : 'float',
        'string' : 'string',
      }[p.type], index, p.name)
    )

  if badret.value is not None:
    file.write('  retval_ = ((%s_type)callback)(%s);\n' %
               (func.name, ArgList(func.params)))
    file.write('  if (retval != NULL) {\n')
    file.write('    *retval = (cell)retval_;\n')
    file.write('  }\n')
  else:
    file.write('  ((%s_type)callback)(%s);\n' %
                 (func.name, ArgList(func.params)))

  for p in filter(lambda p: p.type == 'string', func.params):
    file.write('  free((void*)%s);\n' % p.name)

  if badret.value is not None:
    file.write('  return (retval_ != %s);\n' % badret.value)
  else:
    file.write('  return true;\n')

  file.write('}\n')

def parse_args(argv):
  argparser = argparse.ArgumentParser()
  argparser.add_argument('--module', dest='module_name', required=True)
  argparser.add_argument('--idl', dest='idl_file', required=True)
  argparser.add_argument('--api', dest='api_file')
  argparser.add_argument('--header', dest='header_file')
  argparser.add_argument('--source', dest='source_file')
  return argparser.parse_args(argv)

def main(argv):
  args = parse_args(argv[1:])

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
