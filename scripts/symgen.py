#!/usr/bin/env python
#
# Copyright (C) 2013-2014 Zeex
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

import fnmatch
import os
import os.path
import sys

def filter_api_files(path):
  for root, dirnames, filenames in os.walk(path):
    for filename in fnmatch.filter(filenames, '*.api'):
      yield os.path.join(root, filename)

def main(argv):
  if len(argv) < 3:
    print('Usage: %s sym-file dir1 dir2 ...' % os.path.basename(argv[0]))
  else:
    with open(argv[1], 'w') as outfile:
      for dir in argv[2:]:
        for file in filter_api_files(dir):
          for line in open(file, 'r').readlines():
            outfile.write('%s\n' % line.strip())

if __name__ == '__main__':
  main(sys.argv)