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
  file.write('#include <sampgdk/a_objects.h>\n')
  file.write('#include <sampgdk/a_players.h>\n')
  file.write('#include <sampgdk/a_samp.h>\n')
  file.write('#include <sampgdk/a_vehicles.h>\n')
  file.write('#include <sampgdk/core.h>\n')
  file.write('#include <sampgdk/sdk.h>\n\n')

  file.write('extern void *pAMXFunctions;\n\n')

  file.write('PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {\n')
  file.write('  return sampgdk::Supports() | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;\n')
  file.write('}\n\n')

  file.write('PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {\n')
  file.write('  pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];\n')
  file.write('  return sampgdk::Load(ppData);\n')
  file.write('}\n\n')

  file.write('PLUGIN_EXPORT void PLUGIN_CALL Unload() {\n')
  file.write('}\n\n')

  file.write('PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {\n')
  file.write('  return AMX_ERR_NONE;\n')
  file.write('}\n\n')

  file.write('PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {\n')
  file.write('  return AMX_ERR_NONE;\n')
  file.write('}\n\n')

  file.write('PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {\n')
  file.write('  sampgdk::ProcessTick();\n')
  file.write('}\n\n')

  for c in get_callbacks(idl):
    params = ['%s %s' % (C_TYPES[x.type], x.name) for x in c.params]
    file.write('PLUGIN_EXPORT bool PLUGIN_CALL %s(%s) {\n' %
               (c.name, ', '.join(params)))
    badret = c.get_attr('badret', cidl.Value('bool', False))
    file.write('  return %s;\n' %
               ('false', 'true')[not badret.value.data])
    file.write('}\n\n')

def generate_exports(file, idl):
  file.write('EXPORTS\n')
  file.write('\tSupports\n')
  file.write('\tLoad\n')
  file.write('\tUnload\n')
  file.write('\tAmxLoad\n')
  file.write('\tAmxUnload\n')
  file.write('\tProcessTick\n')

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
