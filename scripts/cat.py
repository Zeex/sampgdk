#!/usr/bin/env python
#
# Copyright (C) 2015 Zeex
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
import zipfile

def parse_args(args):
  parser = argparse.ArgumentParser()
  parser.add_argument('outfile',
                      metavar='outfile',
                      help='output file (with merged contents)')
  parser.add_argument('files',
                      metavar='file',
                      nargs='+',
                      help='input file')
  return parser.parse_args()

def main(argv):
  args = parse_args(argv[1:])
  with open(args.outfile, 'w') as outfile:
    for f in args.files:
      print('Processing file: %s' % f)
      with open(f, 'r') as file:
        outfile.write(file.read())
  print('Done')

if __name__ == '__main__':
  sys.exit(main(sys.argv))
