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
  if include is not None:
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

def find_first_include(text):
  includes = find_includes(text)
  if includes:
    return includes[0]
  return None

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

def parse_args(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('-c',
                      dest='sources',
                      metavar='file',
                      action='append',
                      help='add source file')
  parser.add_argument('-i', dest='headers',
                      metavar='file',
                      action='append',
                      help='add header file')
  parser.add_argument('-I', dest='include_dirs',
                      metavar='dir',
                      action='append',
                      help='add include directory')
  parser.add_argument('-oc', dest='out_source',
                      metavar='file',
                      required=True,
                      help='output source file')
  parser.add_argument('-oi', dest='out_header',
                      metavar='file',
                      required=True,
                      help='output header file')
  return parser.parse_args()

def main(argv):
  args = parse_args(argv[1:])

  sources = []
  if args.sources is not None:
    sources = [os.path.realpath(f) for f in args.sources]
  headers = []
  if args.headers is not None:
    headers = [os.path.realpath(f) for f in args.headers]
  include_dirs = []
  if args.include_dirs is not None:
    include_dirs = args.include_dirs

  sfile = open(args.out_source, 'w')
  hfile = open(args.out_header, 'w')

  headers = sort_files(headers, include_dirs)
  all_files = sort_files(sources + headers, include_dirs)

  header_path = os.path.relpath(args.out_header,
                                os.path.dirname(args.out_source))

  sfile.write('#include "%s"\n\n' % os.path.basename(header_path))

  for f in all_files:
    ofile = (sfile, hfile)[f in headers]
    with open(f, 'r') as ifile:
      for line in ifile.readlines():
        include = find_first_include(line)
        include_path = resolve_include(f, include, include_dirs)
        if include_path is None:
          ofile.write(line)
      ofile.write('\n')

if __name__ == '__main__':
  main(sys.argv)
