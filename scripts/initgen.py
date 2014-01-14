#!/usr/bin/env python
#
# Copyright (C) 2014 Zeex
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

import os
import sys

def generate_init_func(outfile, modules):
  for name in modules:
    outfile.write('extern int sampgdk_%s_init(void);\n' % name)
  outfile.write('\nint sampgdk_module_init(void) {\n')
  outfile.write('  int error;\n')
  for name in modules:
    outfile.write('  if ((error = sampgdk_%s_init()) < 0) {\n' % name)
    outfile.write('    return error;\n')
    outfile.write('  }\n')
  outfile.write('  return 0;\n')
  outfile.write('}\n\n')

def generate_cleanup_func(outfile, modules):
  for name in modules:
    outfile.write('extern int sampgdk_%s_cleanup(void);\n' % name)
  outfile.write('\nvoid sampgdk_module_cleanup(void) {\n')
  for name in modules:
    outfile.write('  sampgdk_%s_cleanup();\n' % name)
  outfile.write('}\n\n')

def main(argv):
  if len(argv) != 3:
    print('Usage: %s input-file output-file' % os.path.basename(argv[0]))
  else:
    modules = []
    for line in file(sys.argv[1]).readlines():
      name = line.strip()
      if name == 'module':
        sys.exit('Module name cannot be "module"')
      modules.append(name)
    with open(argv[2], 'w') as outfile:
      generate_init_func(outfile, modules)
      generate_cleanup_func(outfile, modules)

if __name__ == '__main__':
  main(sys.argv)