#!/usr/bin/env python

import os
import sys
import cidl

type_map = {
  'int':    'int',
  'float':  'float',
  'bool':   'bool',
  'string': 'const char *',
}

if len(sys.argv) < 2:
  print 'Usage: %s <idl>' % os.path.basename(sys.argv[0])
  sys.exit()

parser = cidl.Parser()
idl = parser.parse(open(sys.argv[1], 'r').read())

callbacks = filter(lambda x: x.has_attr('callback'), idl.functions)

out = file('callbacks.cpp', 'w')

out.write('#include "script.h"\n')
out.write('#include "ufs.h"\n\n')

out.write('namespace ufs {\n\n')

for c in callbacks:
  out.write('class %s {\n' % c.name)
  out.write(' public:\n')

  if len(c.params) > 0:
    out.write('  %s(%s): %s {}\n' % (c.name, 
      ', '.join(['%s %s' % (type_map[p.type], p.name) for p in c.params]),
      ', '.join(['%s(%s)' % (p.name, p.name) for p in c.params]),
    ))
  else:
    out.write('  %s() {}\n' % c.name)

  out.write('  bool operator()(Script *s) const {\n')

  for p in reversed(c.params):
    if p.type == 'string':
      out.write('    cell %s_;\n' % p.name)
      out.write('    amx_PushString(s->amx(), &%s_, 0, %s, 0, 0);\n' % (p.name,
                                                                        p.name))
    elif p.type == 'float':
      out.write('    amx_Push(s->amx(), amx_ftoc(%s));\n' % p.name)
    else:
      out.write('    amx_Push(s->amx(), %s);\n' % p.name)

  badret = c.get_attr('badret', cidl.Value('bool', False))
  defret = ('false', 'true')[not badret.value.data]

  if len(c.params) > 0:
    out.write('    bool ret = s->Exec("%s", %s);\n' % (c.name, defret))
    for p in c.params:
      if p.type == 'string':
        out.write('    amx_Release(s->amx(), %s_);\n' % p.name)
    out.write('    return ret;\n')
  else:
    out.write('    return s->Exec("%s", %s);\n' % (c.name, defret))

  out.write('  }\n')

  out.write(' private:\n')
  for p in c.params:
    out.write('  %s %s;\n'  % (type_map[p.type], p.name));
  out.write('};\n\n')

out.write('} // namespace ufs\n\n')

for c in callbacks:
  params = ', '.join(['%s %s' % (type_map[x.type], x.name) for x in c.params])

  out.write('PLUGIN_EXPORT bool PLUGIN_CALL %s(%s) {\n' % (c.name, params))
  out.write('  using namespace ufs;\n')
  out.write('  return UFS::Instance().ForEachScript(\n')

  badret = c.get_attr('badret', cidl.Value('bool', False))
  defret = ('false', 'true')[not badret.value.data]

  args = ', '.join([p.name for p in c.params])
  out.write('    ufs::%s(%s), %s);\n' % (c.name, args, defret))

  out.write('}\n\n')
