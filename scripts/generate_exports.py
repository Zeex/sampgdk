#!/usr/bin/env python
#
# Copyright (C) 2013-2015 Zeex
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
import fnmatch
import os
import os.path
import sys

def parse_args(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('-o', '--output', metavar='filename', required=True,
                      help='output file name')
  parser.add_argument('-f', '--format', choices=['list', 'def'], required=True,
                      help='output format')
  parser.add_argument('api_files', nargs='+')
  return parser.parse_args(argv)

def main(argv):
  args = parse_args(argv[1:])
  with open(args.output, 'w') as outfile:
    if args.format == 'def':
      outfile.write('EXPORTS\n')
    for file in args.api_files:
      for line in open(file, 'r').readlines():
        symbol = line.strip()
        if args.format == 'list':
          outfile.write('%s\n' % symbol)
        elif args.format == 'def':
          outfile.write('\t%s\n' % symbol)

if __name__ == '__main__':
  sys.exit(main(sys.argv))
