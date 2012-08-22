#!/usr/bin/env python

import os
import re
import sys

from parse_header import *

def generate_callback_handler(name, args, bad_ret):
	code = "bool " + name + "(AMX *amx, void *callback, cell *retval) {\n"

	if bad_ret is not None:
		code += "\tbool retval_;\n"

	callargs = ""
	declargs = ", ".join([" ".join(list(arg)) for arg in args])

	locals_code = stack_read_code = free_code = ""

	for index, (argtype, argname) in enumerate(args):
		if index > 0:
			callargs += ", "
		callargs += argname

		if argtype == "bool":
			method = "read_amx_stack_bool"
		elif argtype == "float":
			method = "read_amx_stack_float"
		elif argtype == "const char *" or argtype == "char *":
			method = "read_amx_stack_string"
			free_code += "\tfree((char *)" + argname + ");\n"
		else:
			method = "read_amx_stack_cell"

		locals_code += "\t" + argtype + " " + argname + ";\n"
		stack_read_code += "\t" + argname + " = " + method + "(amx, " + str(index) + ");\n"

	if locals_code:
		code += locals_code + "\n"
	if stack_read_code:
		code += stack_read_code + "\n"

	functype = name + "Type"
	typedef_code = "typedef bool (PLUGIN_CALL *" + functype + ")(" + declargs + ");\n"

	if bad_ret is not None:
		code += "\tretval_ = ((" + functype + ")callback)(" + callargs + ");\n"
		code += "\tif (retval != 0) {\n"
		code += "\t\t*retval = (cell)retval_;\n"
		code += "\t}\n"
	else:
		code += "\t((" + functype + ")callback)(" + callargs + ");\n"

	if free_code:
		code += free_code + "\n"

	if bad_ret is not None:
		code += "\treturn (retval_ != " + str(bad_ret) + ");\n"
	else:
		code += "\treturn true;\n"
		
	code += "}\n"

	return typedef_code + code

def main(argv):
	callbacks = list(get_callbacks(sys.stdin.read()))

	for type, name, args, attrs in callbacks:
		bad_ret = None
		if "$bad_ret" in attrs:
			bad_ret = attrs["$bad_ret"]
		print generate_callback_handler(name, args, bad_ret)

	print "int register_callback_handlers() {"
	print "\tint error;\n"
	for type, name, args, attrs in callbacks:
		print "\tif ((error = callback_add_handler(\"" + name + "\", " + name + ")) < 0)"
		print "\t\treturn error;"

	print "\treturn 0;"
	print "}"

if __name__ == "__main__":
	main(sys.argv)
