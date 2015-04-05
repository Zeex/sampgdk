#!/usr/bin/env python
#
# Copyright (C) 2014-2015 Zeex
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
import os
import sys

def generate_init_func(outfile, modules):
  for level, name in modules:
    outfile.write('int sampgdk_%s_init(void);\n' % name)
  outfile.write('\nint sampgdk_module_init(void) {\n')
  outfile.write('  int error;\n')
  for level, name in modules:
    outfile.write('  if ((error = sampgdk_%s_init()) < 0) {\n' % name)
    outfile.write('    return error;\n')
    outfile.write('  }\n')
  outfile.write('  return 0;\n')
  outfile.write('}\n\n')

def generate_cleanup_func(outfile, modules):
  for level, name in modules:
    outfile.write('void sampgdk_%s_cleanup(void);\n' % name)
  outfile.write('\nvoid sampgdk_module_cleanup(void) {\n')
  for level, name in modules:
    outfile.write('  sampgdk_%s_cleanup();\n' % name)
  outfile.write('}\n\n')

def parse_args(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('-l', '--list', metavar='filename', required=True,
                      help='list file name')
  parser.add_argument('-s', '--source', metavar='filename', required=True,
                      help='source file name')
  return parser.parse_args()

def main(argv):
  args = parse_args(argv[1:])
  modules = []
  for line in open(args.list, 'r').readlines():
    level, name = line.strip().split()
    if name == 'module':
      sys.stderr.write('Module name cannot be "module"')
      return 1
    modules.append((level, name))
  with open(args.source, 'w') as outfile:
    generate_init_func(outfile, sorted(modules))
    generate_cleanup_func(outfile, sorted(modules, reverse=True))

if __name__ == '__main__':
  sys.exit(main(sys.argv))
