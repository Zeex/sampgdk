#!/usr/bin/env python

import os
import re
import sys

from parse_header import *

class InvalidNativeArgumentType:
	def __init__(self, type):
		self.type = type

def to_argument_list(args):
	arg_list = []
	for type, name in args:
		yield type + " " + name

def generate_native_code(return_type, name, args, attrs):
	if "$codeless" in attrs:
		return None

	code = "SAMPGDK_NATIVE(" + return_type + ", " + name\
		+ "(" + ", ".join(to_argument_list(args)) + ")) {\n"

	locals_code = push_code = params_code = get_code = pop_code = ""

	if "$real_name" in attrs:
		real_name = attrs["$real_name"]
	else:
		real_name = name
	locals_code += "\tstatic AMX_NATIVE native;\n"
	locals_code += "\tstruct fakeamx *fa;\n"
	locals_code += "\t" + return_type + " retval;\n"

	if len(args) > 0:
		locals_code += "\tcell params[" + str(len(args) + 1) + "];\n"
		params_code += "\tparams[0] = " + str(len(args)) + " * sizeof(cell);\n"

		expect_buffer_size = False
		for index, (type, name) in enumerate(args, 1):
			alt_name = name + "_"
			local_size = "size_of_" + alt_name

			if expect_buffer_size:
				term = name + ");\n"
				push_code += term
				get_code  += term
				pop_code  += term
				expect_buffer_size = False

			if type.endswith("*"):
				locals_code += "\tcell " + alt_name + ";\n"
				if type == "char *":
					push_code += "\t" + alt_name + " = fakeamx_push(fa, "
					expect_buffer_size = True
				elif type == "const char *":
					locals_code += "\tsize_t " + local_size + ";\n"
					push_code += "\t" + alt_name + " = fakeamx_push_string(fa, " + name + ", &" + local_size + ");\n"
				else:
					push_code += "\t" + alt_name + " = fakeamx_push(fa, 1);\n"

			params_code += "\tparams[" + str(index) + "] = "
			if type == "int" or type == "bool":
				params_code += name
			elif type == "float":
				params_code += "amx_ftoc(" + name + ")"
			elif type.endswith("*"):
				params_code += alt_name
			else:
				raise InvalidNativeArgumentType(type)
			params_code += ";\n"

			if type.endswith("*"):
				if type == "const char *":
					pop_code += "\tfakeamx_pop(fa, " + local_size + ");\n"
				elif type == "char *":
					get_code += "\tfakeamx_get_string(fa, " + alt_name + ", " + name + ", "
					pop_code += "\tfakeamx_pop(fa, "
					expect_buffer_size = True
				else:
					get_code += "\tfakeamx_get_"
					try:
						get_code += {
							"int *"   : "cell",
							"bool *"  : "bool",
							"float *" : "float"
						}[type]
					except KeyError as e:
						raise InvalidNativeArgumentType(type)
					get_code += "(fa, " + name + "_, " + name + ");\n"
					pop_code += "\tfakeamx_pop(fa, 1);\n"

	code += locals_code + "\n"
	code += "\tif (native == NULL) {\n"
	code += "\t\tnative = native_lookup_warn(\"" + real_name + "\");\n"
	code += "\t}\n"
	code += "\tfa = fakeamx_global();\n"
	code += push_code
	code += params_code

	code += "\tretval = (" + return_type + ")native(&fa->amx, "
	if len(args) > 0:
		code += "params"
	else:
		code += "NULL"
	code += ");\n"

	code += get_code
	code += pop_code
	code += "\n\treturn retval;\n"
	code += "}\n"

	return code

def main(argv):
	for line, native in enumerate(get_natives(sys.stdin.read()), 1):
		try:
			code = generate_native_code(*native)
			if code is not None:
				sys.stdout.write(code + "\n")
			sys.stdout.flush()
		except InvalidNativeArgumentType as arg:
			sys.stderr.write("Invalid argument type '" + arg.type + "' in declaration at line " + str(line) + "\n")

if __name__ == "__main__":
	main(sys.argv)
