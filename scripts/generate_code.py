#!/usr/bin/env python
#
# Copyright (C) 2012-2015 Zeex
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

C_TYPES_IN = {
  'int'    : 'int',
  'bool'   : 'bool',
  'float'  : 'float',
  'string' : 'const char *',
}

C_TYPES_OUT = {
  'int'    : 'int *',
  'bool'   : 'bool *',
  'float'  : 'float *',
  'string' : 'char *',
}

C_FORMAT_STRINGS = {
  'int'    : '%d',
  'bool'   : '%d',
  'float'  : '%f',
  'string' : '\\"%s\\"',
}

C_FORMAT_STRINGS_OUT = {
  'int'    : '@%p',
  'bool'   : '@%p',
  'float'  : '@%p',
  'string' : '@%p',
}

class Parameter(cidl.Parameter):
  def __init__(self, type, name, default=None, attrlist=None):
    cidl.Parameter.__init__(self, type, name, default, attrlist)

  @property
  def c_type(self):
    try:
      if self.is_out:
        return C_TYPES_OUT[self.type]
      else:
        return C_TYPES_IN[self.type]
    except KeyError:
      if self.is_out:
        return '%s *' % self.type
      else:
        return self.type
    return None

  @property
  def is_ref(self):
    return self.is_out or self.type == 'string'

  @property
  def is_value(self):
    return not self.is_ref

  @property
  def is_bound(self):
    return self.has_attr('bind')

  @property
  def bind(self):
    return self.get_attr('bind')

  @property
  def format_string(self):
    if self.is_out:
      return C_FORMAT_STRINGS_OUT[self.type]
    else:
      return C_FORMAT_STRINGS[self.type]

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

class ParameterList:
  def __init__(self, params, includes_types=True, includes_defaults=False):
    self._params = params
    self._includes_types = includes_types
    self._includes_defaults = includes_defaults

  def as_list(self):
    for p in filter(lambda p: not p.is_bound, self._params):
      s = p.name
      if self._includes_types:
        s = '%s %s' % (p.c_type, s)
      if self._includes_defaults and p.default is not None:
        s = '%s = %s' % (s, p.default)
      yield s

  def __str__(self):
    return ', '.join(self.as_list())

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
  header_symbol = 'SAMPGDK_%s_H' % module_name.upper()

  file.write('#ifndef %s\n' % header_symbol)
  file.write('#define %s\n' % header_symbol)
  file.write('\n')
  file.write('#include <sampgdk/bool.h>\n')
  file.write('#include <sampgdk/export.h>\n')
  file.write('#include <sampgdk/types.h>\n')
  file.write('\n')

  for const in idl.constants:
    generate_constant(file, const)
  file.write('\n')

  natives = list(filter(lambda x: x.has_attr('native'), idl.functions))
  for func in natives:
    generate_native_decl(file, func)
    file.write('\n')

  file.write('#ifndef DOXYGEN\n\n')
  file.write('#if defined SAMPGDK_CPP_WRAPPERS && !defined IN_SAMPGDK\n\n')
  file.write('namespace sampgdk {\n\n')
  for func in natives:
    generate_native_wrapper(file, func)
    file.write('\n')
  file.write('} // namespace sampgdk\n\n')
  file.write('#else /* SAMPGDK_CPP_WRAPPERS && !IN_SAMPGDK */\n\n')
  for func in natives:
    generate_native_alias(file, func)
    file.write('\n')
  file.write('#endif /* !SAMPGDK_CPP_WRAPPERS || IN_SAMPGDK */\n')
  file.write('#endif /* !DOXYGEN */\n\n')

  callbacks = list(filter(lambda x: x.has_attr('callback'), idl.functions))
  for func in callbacks:
    generate_callback_decl(file, func)
    file.write('\n')

  file.write('#endif /* !%s */\n' % header_symbol)

def generate_source_file(module_name, idl, file):
  file.write('#include <sampgdk/%s.h>\n' % module_name)
  file.write('\n')
  file.write('#include "internal/callback.h"\n')
  file.write('#include "internal/fakeamx.h"\n')
  file.write('#include "internal/init.h"\n')
  file.write('#include "internal/log.h"\n')
  file.write('#include "internal/native.h"\n')
  file.write('#include "internal/param.h"\n')
  file.write('\n')

  natives = list(filter(lambda x: x.has_attr('native') and not
                                  x.has_attr('noimpl'),
                        idl.functions))
  for func in natives:
    generate_native_impl(file, func)
    file.write('\n')

  callbacks = list(filter(lambda x: x.has_attr('callback'), idl.functions))
  for func in callbacks:
    generate_callback_impl(file, func)
    file.write('\n')

  file.write('SAMPGDK_MODULE_INIT(%s) {\n' % module_name)
  sorted_callbacks = list(sorted(callbacks, key=lambda x: x.name, reverse=True))
  if sorted_callbacks:
    file.write('  int error;\n')
  for func in sorted_callbacks:
    file.write('  if ((error = sampgdk_callback_register("%s", _%s)) < 0) {\n' %
               (func.name, func.name))
    file.write('    return error;\n')
    file.write('  }\n')
  file.write('  return 0;\n')
  file.write('}\n\n')

  file.write('SAMPGDK_MODULE_CLEANUP(%s) {\n' % module_name)
  for func in sorted_callbacks:
    file.write('  sampgdk_callback_unregister("%s");\n' % func.name)
  file.write('}\n\n')

def generate_constant(file, const):
  file.write('#define %s (%s)\n' % (const.name, const.value))

def generate_native_doc_comment(file, func):
  file.write('/**\n')
  file.write(' * \\ingroup natives\n')
  file.write(' * \\see <a href="http://wiki.sa-mp.com/wiki/%s">'
             '%s on SA-MP Wiki</a>\n' % (func.name, func.name))
  file.write(' */\n')

def generate_native_decl(file, func):
  generate_native_doc_comment(file, func)
  file.write('SAMPGDK_NATIVE(%s, %s(%s));\n' %
             (func.type, func.name, ParameterList(func.params)))

def generate_native_alias(file, func):
  file.write('#undef  %s\n' % func.name)
  file.write('#define %s sampgdk_%s\n' % (func.name, func.name))

def generate_native_wrapper(file, func):
  file.write('inline %s %s(%s) {\n' %
             (func.type, func.name, ParameterList(func.params, includes_defaults=True)))
  file.write('  return sampgdk_%s(%s);\n}\n' %
             (func.name, ParameterList(func.params, includes_types=False)))

def generate_native_impl(file, func):
  file.write('SAMPGDK_NATIVE(%s, %s(%s)) {\n' %
             (func.type, func.name, ParameterList(func.params)))
  file.write('  static AMX_NATIVE native;\n')
  file.write('  cell retval;\n')

  if func.params:
    file.write('  cell params[%d];\n' % (len(func.params) + 1))
    for p in filter(lambda p: p.is_ref, func.params):
      file.write('  cell %s_;\n' % p.name)

  if func.params:
    format = ', '.join([p.format_string for p in func.params])
    file.write('  sampgdk_log_debug("%s(%s)", %s);\n' %
               (func.name, format, ParameterList(func.params, includes_types=False)))
  else:
    file.write('  sampgdk_log_debug("%s()");\n' % func.name)

  file.write('  native = sampgdk_native_find_flexible("%s", native);\n' %
             func.name)

  if func.params:
    for pprev, p, pnext in previous_and_next(func.params):
      if p.is_ref:
        if p.is_bound:
          value = p.bind.value
        else:
          value = p.name
        if p.type == 'string':
          file.write('  sampgdk_fakeamx_push_string(%s, NULL, &%s_);\n' %
                      (value, p.name))
        else:
          file.write('  sampgdk_fakeamx_push_%s(*%s, &%s_);\n' % (
            {
              'int'   : 'cell',
              'bool'  : 'cell',
              'float' : 'float',
              'string': 'string'
            }[p.type], p.name, p.name
          ))

    file.write('  params[0] = %d * sizeof(cell);\n' % len(func.params))
    for index, p in enumerate(func.params, 1):
      if p.is_value:
        if p.is_bound:
          value = p.bind.value
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
            }[p.type], p.name, p.name))

    for p in reversed(list(filter(lambda p: p.is_ref, func.params))):
      file.write('  sampgdk_fakeamx_pop(%s_);\n' % p.name)

  file.write('  return %s(retval);\n' % ({
      'int'   : '(int)',
      'bool'  : '!!',
      'float' : 'amx_ctof',
    }[func.type]
  ))

  file.write('}\n')

def generate_callback_doc_comment(file, func):
  file.write('/**\n')
  file.write(' * \\ingroup callbacks\n')
  file.write(' * \\see <a href="http://wiki.sa-mp.com/wiki/%s">'
             '%s on SA-MP Wiki</a>\n' % (func.name, func.name))
  file.write(' */\n')

def generate_callback_decl(file, func):
  if not func.has_attr('nonstandard'):
    generate_callback_doc_comment(file, func)
  file.write('SAMPGDK_CALLBACK(%s, %s(%s));\n' %
             (func.type, func.name, ParameterList(func.params)))

def generate_callback_impl(file, func):
  file.write('typedef %s (SAMPGDK_CALLBACK_CALL *%s_callback)(%s);\n' %
             (func.type, func.name, ParameterList(func.params)))
  file.write('static bool _%s(AMX *amx, void *callback, cell *retval)'
             ' {\n' % func.name)

  badret = func.get_attr('badret').value
  if badret is not None:
    if badret.type == 'bool':
      file.write('  bool retval_;\n')
    else:
      raise Exception('%s: badret must be of type "bool"' % func.name)

  for p in func.params:
    file.write('  %s %s;\n' % (p.c_type, p.name))

  for index, p in enumerate(func.params):
    file.write('  sampgdk_param_get_%s(amx, %d, (%s *)&%s);\n' % ({
        'int'    : 'cell',
        'bool'   : 'bool',
        'float'  : 'float',
        'string' : 'string',
      }[p.type], index, {
        'int'    : 'cell',
        'bool'   : 'bool',
        'float'  : 'float',
        'string' : 'char *',
      }[p.type], p.name)
    )

  if func.params:
    format = ', '.join([p.format_string for p in func.params])
    file.write('  sampgdk_log_debug("%s(%s)", %s);\n' %
               (func.name, format, ParameterList(func.params, includes_types=False)))
  else:
    file.write('  sampgdk_log_debug("%s()");\n' % func.name)

  if badret is not None:
    file.write('  retval_ = ((%s_callback)callback)(%s);\n' %
               (func.name, ParameterList(func.params, includes_types=False)))
    file.write('  if (retval != NULL) {\n')
    file.write('    *retval = (cell)retval_;\n')
    file.write('  }\n')
  else:
    file.write('  ((%s_callback)callback)(%s);\n' %
               (func.name, ParameterList(func.params, includes_types=False)))

  for p in filter(lambda p: p.type == 'string', func.params):
    file.write('  free((void *)%s);\n' % p.name)

  if func.type not in ['bool', 'void']:
    raise Exception('%s: Return type must be either "bool" or "void"' %
                    func.name)

  if badret is not None:
    file.write('  return !!retval_ != %s;\n' % badret)
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
    idlparser = cidl.Parser(value_class=Value,
                            param_class=Parameter)
    try:
      file = open(args.idl_file, 'rU')
    except ValueError:
      file = open(args.idl_file, 'r') # Python 3
    idl = idlparser.parse(file.read())
    file.close()

    for (path, func) in [(args.api_file, generate_api_file),
                         (args.header_file, generate_header_file),
                         (args.source_file, generate_source_file)]:
      if path is not None:
        dir = os.path.dirname(path)
        if not os.path.exists(dir):
          os.makedirs(dir)
        with open(path, 'w') as file:
          func(args.module_name, idl, file)

  except cidl.Error as e:
    sys.stderr.write('%s\n' % e)
    return 1

if __name__ == '__main__':
  sys.exit(main(sys.argv))
