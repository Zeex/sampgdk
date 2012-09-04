#!/usr/bin/env python
#
# Copyright (C) 2012 Zeex
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
import cidl
import itertools
import os
import sys

from codegen import *

def previous_and_next(iterable):
    prevs, items, nexts = itertools.tee(iterable, 3)
    prevs = itertools.chain([None], prevs)
    nexts = itertools.chain(itertools.islice(nexts, 1, None), [None])
    return itertools.izip(prevs, items, nexts)

def main(argv):
	argparser = argparse.ArgumentParser()

	argparser.add_argument("-idl", required=True)
	argparser.add_argument("-header")
	argparser.add_argument("-source")
	argparser.add_argument("-exports")

	args = argparser.parse_args(argv[1:])

	try:
		idlparser = cidl.Parser()
		idl = idlparser.parse(open(args.idl, 'r').read())

		natives = filter(lambda x: x.has_attr('native'), idl.functions)

		if args.header is not None:
			header = open(args.header, 'w')

			# Generate #define's for constants.
			for c in idl.constants:
				header.write('#define %s (%s)\n' % (c.name, value_to_c_literal(c.value)))
			header.write('\n')

			# Generate native declarations and defines.
			for f in natives:
				header.write('SAMPGDK_EXPORT %s SAMPGDK_CALL sampgdk_%s(%s);\n' % (f.type, f.name, params_to_string(f.params)))
				header.write('#undef %s\n' % f.name)
				header.write('#define %s sampgdk_%s\n\n' % (f.name, f.name))

			header.close()

		if args.source is not None:
			source = open(args.source, 'w')

			# Generate native implementation code.
			for f in natives:
				source.write('SAMPGDK_EXPORT %s SAMPGDK_CALL sampgdk_%s(%s) {\n' % (f.type, f.name, params_to_string(f.params)))
				source.write('\tstatic AMX_NATIVE native;\n')
				source.write('\tstruct fakeamx *fa;\n')
				source.write('\t%s retval;\n' % f.type)

				if f.params:
					source.write('\tcell params[%d];\n' % (len(f.params) + 1))

					# Define local vaiables to store AMX heap addresses.
					for p in filter(is_ref_param, f.params):
						source.write('\tcell %s_;\n' % p.name)

					source.write('\tif (unlikely(native == NULL))\n')
					source.write('\t\tnative = native_lookup_warn_stub("%s");\n' % f.name)

				source.write('\tfakeamx_instance(&fa);\n')

				if f.params:
					# Call to fakeamx_push() for parameters.
					for pprev, p, pnext in previous_and_next(f.params):
						if is_ref_param(p):
							if p.type == 'char': # output string (const char *)
								source.write('\tfakeamx_push(fa, %s, &%s_);\n' % (pnext.name, p.name))
							elif p.type == 'string': # input string (char *)
								source.write('\tfakeamx_push_string(fa, %s, NULL, &%s_);\n' % (p.name, p.name))
							else:
								source.write('\tfakeamx_push(fa, 1, &%s_);\n' % p.name)

					# Fill the params array.
					source.write('\tparams[0] = %d * sizeof(cell);\n' % len(f.params))
					for index, p in enumerate(f.params, 1):
						if is_value_param(p):
							source.write('\tparams[%d] = %s;\n' % (index, 
								{
									'int'   : '(cell)%s' % p.name,
									'bool'  : '(cell)%s' % p.name,
									'char'  : '(cell)%s' % p.name,
									'float' : 'amx_ftoc(%s)' % p.name,
								}[p.type]
							))
						else:
							source.write('\tparams[%d] = %s_;\n' % (index, p.name))

				source.write('\tretval = (%s)native(&fa->amx, %s);\n' % (f.type, ('NULL', 'params')[bool(f.params)]))

				if f.params:
					# Copy data to output arguments.
					for pprev, p, pnext in previous_and_next(f.params):
						if is_ref_param(p):
							if p.type == 'string':
								pass
							elif p.type == 'char':
								source.write('\tfakeamx_get_string(fa, %s_, %s, %s);\n' % (p.name, p.name, pnext.name))
							else:
								source.write('\tfakeamx_get_%s(fa, %s_, %s);\n' % (
									{
										'int'   : "cell",
										'bool'  : "bool",
										'float' : "float"
									}[p.type]
								,	
								p.name, p.name))

					# Free previously allocated heap space (in reverse order).
					for p in reversed(filter(is_ref_param, f.params)):
						source.write('\tfakeamx_pop(fa, %s_);\n' % p.name)

				source.write('\treturn retval;\n')
				source.write('}\n')

			source.close()

		if args.exports is not None:
			exports = open(args.exports, 'w')

			for f in natives:
				exports.write('sampgdk_%s\n' % f.name)

			exports.close()

	except cidl.Error as e:
		print e

if __name__ == '__main__':
	main(sys.argv)
