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

import argparse
import os
import re
import sys

def extract_path(include):
  match = re.match('["<](.*)[">]', include)
  if match is not None:
    return match.group(1)
  return None

def resolve_include(filename, include, include_dirs):
  rel_path = extract_path(include)
  if include.startswith('"'):
    path = os.path.join(os.path.dirname(filename), rel_path)
    if os.path.exists(path):
      return os.path.realpath(path)
  for dir in include_dirs:
    path = os.path.join(dir, rel_path)
    if os.path.exists(path):
      return os.path.realpath(path)
  return None

def find_includes(text):
  return re.findall(r'#include\s*(["<].*[">])', text)

def find_deps(files, include_dirs):
  deps = {}
  for f in files:
    find_file_deps(f, include_dirs, deps)
  return deps

def find_file_deps(filename, include_dirs, deps):
  deps[filename] = []
  with open(filename, 'r') as file:
    for i in find_includes(file.read()):
      d = resolve_include(filename, i, include_dirs)
      if d is not None:
        deps[filename].append(d)
        if d not in deps:
          find_file_deps(d, include_dirs, deps)
  return deps

def sort_deps(files, deps):
  sorted = []
  current = [f for f in files if not deps[f]]
  while current:
    f = current.pop(0)
    sorted.append(f)
    for depender, dependees in deps.items():
      if f in dependees:
        dependees.remove(f)
        if not dependees:
          current.append(depender)
  try:
    next(x for x in deps.values() if x)
  except StopIteration:
    return sorted
  raise Exception('Circular dependency or missing file')

def sort_files(files, include_dirs):
  return sort_deps(files, find_deps(files, include_dirs))

def print_deps(deps):
  for f, ds in deps.items():
    for d in ds:
      print('%s -> %s' % (f, d))

def amalgamate(sources, headers, include_dirs, out_source, out_header):
  sfile = open(out_source, 'w')
  hfile = open(out_header, 'w')

  sorted_sources = sort_files(sources + headers, include_dirs)
  sorted_headers = sort_files(headers, include_dirs)
  all_files = sorted_sources + sorted_headers

  for f in all_files:
    with open(f, 'r') as ifile:
      ofile = (hfile, sfile)[f in sources]
      ofile.write('/* File: %s */\n\n' % os.path.relpath(f, os.getcwd()))
      for line in ifile.readlines():
        includes = find_includes(line)
        if includes:
          path = resolve_include(f, includes[0], include_dirs)
          if path in headers and f in sources:
            ofile.write('#include "%s"\n' % os.path.basename(out_header))
            continue
          if path in all_files:
            continue
        ofile.write('%s' % line)
      ofile.write('\n')

def parse_args(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('-c', dest='sources', metavar='file', action='append',
                      help='add source file')
  parser.add_argument('-i', dest='headers', metavar='file', action='append',
                      help='add header file')
  parser.add_argument('-I', dest='include_dirs', metavar='dir', action='append',
                      help='add include directory')
  parser.add_argument('-oc', dest='out_source', metavar='file', required=True,
                      help='output source file')
  parser.add_argument('-oi', dest='out_header', metavar='file', required=True,
                      help='output header file')
  return parser.parse_args()

def main(argv):
  args = parse_args(argv[1:])
  sources = []
  if args.sources is not None:
    sources = args.sources
  headers = []
  if args.headers is not None:
    headers = args.headers
  include_dirs = []
  if args.include_dirs is not None:
    include_dirs = args.include_dirs
  amalgamate([os.path.realpath(f) for f in sources],
             [os.path.realpath(f) for f in headers],
             include_dirs, args.out_source, args.out_header)

if __name__ == '__main__':
  main(sys.argv)
