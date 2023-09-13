#!/usr/bin/env python

import argparse
import os
import sys
import cidl

C_TYPES = {
  'int':    'int',
  'float':  'float',
  'bool':   'bool',
  'string': 'const char *',
}

def generate_source(file, idl):
  file.write('#include "script.h"\n')
  file.write('#include "ufs.h"\n\n')
  file.write('namespace ufs {\n\n')

  for c in get_callbacks(idl):
    generate_callback_class(file, c)
  file.write('} // namespace ufs\n\n')
  for c in get_callbacks(idl):
    generate_callback(file, c)

def generate_callback_class(file, func):
  file.write('class %s {\n' % func.name)
  file.write(' public:\n')

  if len(func.params) > 0:
    file.write('  %s(%s): %s {}\n' % (func.name,
      ', '.join(['%s %s' % (C_TYPES[p.type], p.name)
                            for p in func.params]),
      ', '.join(['%s_(%s)' % (p.name, p.name) for p in func.params]),
    ))
  else:
    file.write('  %s() {}\n' % func.name)

  file.write('  bool operator()(Script *s) {\n')

  for p in reversed(func.params):
    if p.type == 'string':
      file.write('    cell %s_addr;\n' % p.name)
      file.write('    amx_PushString(s->amx(), &%s_addr, 0, %s_, 0, 0);\n' %
                 (p.name, p.name))
    elif p.type == 'float':
      file.write('    amx_Push(s->amx(), amx_ftoc(%s_));\n' % p.name)
    else:
      file.write('    amx_Push(s->amx(), %s_);\n' % p.name)

  badret = func.get_attr('badret', cidl.Value('bool', False))
  defret = ('false', 'true')[not badret.value.data]

  if len(func.params) > 0:
    file.write('    bool ret = s->Exec("%s", %s);\n' % (func.name, defret))
    for p in func.params:
      if p.type == 'string':
        file.write('    amx_Release(s->amx(), %s_addr);\n' % p.name)
    file.write('    return ret;\n')
  else:
    file.write('    return s->Exec("%s", %s);\n' % (func.name, defret))

  file.write('  }\n')

  file.write(' private:\n')
  for p in func.params:
    file.write('  %s %s_;\n'  % (C_TYPES[p.type], p.name));
  file.write('};\n\n')

def generate_callback(file, func):
  params = ', '.join(['%s %s' % (C_TYPES[x.type], x.name)
                      for x in func.params])

  file.write('PLUGIN_EXPORT bool PLUGIN_CALL %s(%s) {\n' % (func.name, params))
  file.write('  return ufs::UFS::Instance().ForEachScript(')

  badret = func.get_attr('badret', cidl.Value('bool', False))
  defret = ('false', 'true')[not badret.value.data]
  args = ', '.join([p.name for p in func.params])

  file.write('ufs::%s(%s), %s);\n' % (func.name, args, defret))
  file.write('}\n\n')

def generate_exports(file, idl):
  for c in get_callbacks(idl):
    file.write('\t%s\n' % c.name)

def get_callbacks(idl):
  return list(filter(lambda x: x.has_attr('callback'), idl.functions))

def parse_args(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('-i', '--idl', metavar='filename', required=True,
                      help='IDL file name')
  parser.add_argument('-s', '--source', metavar='filename', required=True,
                      help='source file name')
  return parser.parse_args()

def parse_idl(filename):
  parser = cidl.Parser()
  try:
    file = open(filename, 'rU')
  except ValueError:
    file = open(filename, 'r') # Python 3
  idl = parser.parse(file.read())
  file.close()
  return idl

def main(argv):
  args = parse_args(argv[1:])
  idl = parse_idl(args.idl)
  with open(args.source, 'w') as file:
    generate_source(file, idl)
  with open(os.path.splitext(args.source)[0] + '.def', 'w') as file:
    generate_exports(file, idl)

if __name__ == '__main__':
  sys.exit(main(sys.argv))
