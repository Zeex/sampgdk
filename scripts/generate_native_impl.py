#!/usr/bin/env python2

import sys
import itertools

from parse_header import *

class InvalidNativeArgumentType:
	def __init__(self, type):
		self.type = type

def to_argument_list(args):
	arg_list = []
	for type, name in args:
		yield type + " " + name

def previous_and_next(some_iterable):
    prevs, items, nexts = itertools.tee(some_iterable, 3)
    prevs = itertools.chain([None], prevs)
    nexts = itertools.chain(itertools.islice(nexts, 1, None), [None])
    return itertools.izip(prevs, items, nexts)

def generate_native_impl(return_type, name, args, attrs):
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

		for index, (prev, cur, next) in enumerate(previous_and_next(args), 1):
			type, name = cur

			if next is not None:
				next_type, next_name = next
			else:
				next_type = next_name = ""

			addr_var_name = name + "_"
			size_arg_name = next_name

			if type.endswith("*"):
				locals_code += "\tcell " + addr_var_name + ";\n"
				if type == "char *":
					push_code += "\tfakeamx_push(fa, " + size_arg_name + ", &" + addr_var_name + ");\n"
				elif type == "const char *":
					push_code += "\tfakeamx_push_string(fa, " + name + ", NULL, &" + addr_var_name + ");\n"
				else:
					push_code += "\tfakeamx_push(fa, 1, &" + addr_var_name + ");\n"

			params_code += "\tparams[" + str(index) + "] = "
			if type == "int" or type == "bool":
				params_code += name
			elif type == "float":
				params_code += "amx_ftoc(" + name + ")"
			elif type.endswith("*"):
				params_code += addr_var_name
			else:
				raise InvalidNativeArgumentType(type)
			params_code += ";\n"

			if type.endswith("*"):
				pop_code += "\tfakeamx_pop(fa, " + addr_var_name + ");\n"
				if type == "const char *":
					pass
				elif type == "char *":
					get_code += "\tfakeamx_get_string(fa, " + addr_var_name + ", " + name + ", " + size_arg_name + ");\n"
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

	code += locals_code + "\n"
	code += "\tif (unlikely(native == NULL))\n"
	code += "\t\tnative = native_lookup_warn_stub(\"" + real_name + "\");\n"
	code += "\tfakeamx_instance(&fa);\n"
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
			code = generate_native_impl(*native)
			if code is not None:
				sys.stdout.write(code + "\n")
			sys.stdout.flush()
		except InvalidNativeArgumentType as arg:
			sys.stderr.write("Invalid argument type '" + arg.type + "' in declaration at line " + str(line) + "\n")

if __name__ == "__main__":
	main(sys.argv)

