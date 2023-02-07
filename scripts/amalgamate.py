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
import io
import os
import re
import sys

def strip_license_blocks(s):
  return re.sub(r'/\*\s*Copyright.*?Zeex(.|[\r\n])*?\*/[\r\n]*', '', s, re.M | re.S)

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
  for file in files:
    find_file_deps(file, include_dirs, deps)
  return deps

def find_file_deps(filename, include_dirs, deps):
  deps[filename] = []
  with io.open(filename, 'rt', newline='\n') as file:
    for i in find_includes(file.read()):
      d = resolve_include(filename, i, include_dirs)
      if d is not None:
        deps[filename].append(d)
        if d not in deps:
          find_file_deps(d, include_dirs, deps)
  return deps

def sort_deps(files, deps):
  sorted = []
  current = [file for file in files if not deps[file]]
  while current:
    file = current.pop(0)
    sorted.append(file)
    for depender, dependees in deps.items():
      if file in dependees:
        dependees.remove(file)
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
  for file, ds in deps.items():
    for d in ds:
      print('%s -> %s' % (file, d))

def parse_args(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('--source',
                      dest='sources',
                      metavar='file',
                      action='append',
                      help='add source file')
  parser.add_argument('--header',
                      dest='headers',
                      metavar='file',
                      action='append',
                      help='add header file')
  parser.add_argument('--include-dir',
                      dest='include_dirs',
                      metavar='dir',
                      action='append',
                      help='add include directory')
  parser.add_argument('--output-source',
                      dest='output_source',
                      metavar='file',
                      required=True,
                      help='set output source file')
  parser.add_argument('--output-header',
                      dest='output_header',
                      metavar='file',
                      required=True,
                      help='set output header file')
  parser.add_argument('--source-preamble',
                      dest='source_preamble',
                      metavar='file',
                      help='prepend code to resulting source file')
  parser.add_argument('--header-preamble',
                      dest='header_preamble',
                      metavar='file',
                      help='prepend code to resulting header file')
  return parser.parse_args()

def main(argv):
  args = parse_args(argv[1:])

  sources = []
  if args.sources is not None:
    sources = [os.path.realpath(file) for file in args.sources]
  headers = []
  if args.headers is not None:
    headers = [os.path.realpath(file) for file in args.headers]
  include_dirs = []
  if args.include_dirs is not None:
    include_dirs = args.include_dirs

  (c_file, h_file) = (io.open(args.output_source, 'wt', newline='\n'),
                      io.open(args.output_header, 'wt', newline='\n'))

  if args.source_preamble is not None:
    with io.open(args.source_preamble, 'rt', newline='\n') as in_file:
      c_file.write(in_file.read().replace('\r', ''))
      c_file.write(u'\n')
  if args.header_preamble is not None:
    with io.open(args.header_preamble, 'rt', newline='\n') as in_file:
      h_file.write(in_file.read().replace('\r', ''))
      h_file.write(u'\n')

  headers = sort_files(headers, include_dirs)
  all_files = sort_files(sources + headers, include_dirs)

  header_path = os.path.relpath(args.output_header,
                                os.path.dirname(args.output_source))

  for file in all_files:
    out_file = (c_file, h_file)[file in headers]
    with io.open(file, 'rt', newline='\n') as in_file:
      header_included = False
      for line in strip_license_blocks(in_file.read()).splitlines():
        include = find_first_include(line)
        include_path = resolve_include(file, include, include_dirs)
        if include_path is None:
          out_file.write(line.replace('\r', '') + u'\n')
        elif include_path in headers and file not in headers:
          if not header_included:
            out_file.write(u'#include "%s"\n' % os.path.basename(header_path))
            header_included = True
        else:
          out_file.write(u'/* #include %s */\n' % include)
      out_file.write(u'\n')

  for out_file in (c_file, h_file):
    out_file.close()

if __name__ == '__main__':
  main(sys.argv)
