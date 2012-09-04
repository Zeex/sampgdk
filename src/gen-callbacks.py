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
import os
import sys

from codegen import *

def main(argv):
	argparser = argparse.ArgumentParser()

	argparser.add_argument("-idl", required=True)
	argparser.add_argument("-header")
	argparser.add_argument("-source")
	argparser.add_argument("-list")

	args = argparser.parse_args(argv[1:])

	try:
		idlparser = cidl.Parser()
		idl = idlparser.parse(open(args.idl, 'r').read())

		callbacks = filter(lambda x: x.has_attr('callback'), idl.functions)

		if args.header is not None:
			header = open(args.header, 'w')

			for f in callbacks:
				header.write('PLUGIN_EXPORT %s PLUGIN_CALL %s(%s);\n' % (f.type, f.name, params_to_string(f.params)))

			header.close()

		if args.source is not None:
			source = open(args.source, 'w')

			for f in callbacks:
				source.write('typedef %s (PLUGIN_CALL *%s_type)(%s);\n' % (f.type, f.name, params_to_string(f.params)))
				source.write('bool %s(AMX *amx, void *callback, cell *retval) {\n' % f.name)

				badret = f.get_attr('badret')
				if badret is not None:
					source.write('\tbool retval_;\n')

				# Declare local variables for temporary storage of callback arguments.
				for p in f.params:
					source.write('\t%s %s;\n' % (get_param_c_type(p), p.name))

				# Copy parameters from AMX stack.
				for index, p in enumerate(f.params):
					source.write('\t%s = amx_stack_get_arg_%s(amx, %d);\n' % (p.name,
						{
							'int'    : 'cell',
							'bool'   : 'bool',
							'float'  : 'float',
							'char'   : 'char',
							'string' : 'string'
						}[p.type], index)
					)

				# Invoke the callback function.
				if badret is not None:
					source.write('\tretval_ = ((%s_type)callback)(%s);\n' % (f.name, params_to_string_no_type(f.params)))
					source.write('\tif (retval != NULL) {\n')
					source.write('\t\t*retval = (cell)retval_;\n')
					source.write('\t}\n')
				else:
					source.write('\t((%s_type)callback)(%s);\n' % (f.name, params_to_string_no_type(f.params)))

				# Free the memory allocated for strings.
				for p in filter(lambda p: p.type == 'string', f.params):
					source.write('\tfree((void*)%s);\n' % p.name)

				if badret is not None:
					source.write('\treturn (retval_ != %s);\n' % value_to_c_literal(badret.value))
				else:
					source.write('\treturn true;\n')

				source.write('}\n\n')

			source.write('int register_callbacks() {\n')
			source.write('\tint error;\n')

			for f in callbacks:
				source.write('\tif ((error = callback_add_handler("%s", %s)) < 0)\n' % (f.name, f.name))
				source.write('\t\treturn error;\n')

			source.write('\t(void)error;\n')
			source.write('\treturn 0;\n')
			source.write('}\n')
			
			source.close()

	except cidl.Error as e:
		print e

if __name__ == '__main__':
	main(sys.argv)
