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

	# Write first line, same as function declaration + "{\n".
	code = "SAMPGDK_NATIVE(" + return_type + ", " + name\
		+ "(" + ", ".join(to_argument_list(args)) + ")) {\n"

	# A "static" variable that holds native address.
	if "$real_name" in attrs:
		real_name = attrs["$real_name"]
	else:
		real_name = name
	code += "\tstatic AMX_NATIVE native = sampgdk::natives::GetNativeFunctionWarn(\"" + real_name + "\");\n"

	locals_code = ""
	params_code = ""
	assign_code = ""

	code += "\tsampgdk::FakeAmx *fakeAmx = sampgdk::FakeAmx::GetGlobal();\n"

	if len(args) > 0:
		params_code += "\tcell params[] = {\n"
		params_code += "\t\t" + str(len(args)) + " * sizeof(cell)"
		expect_buffer_size = False
		for type, name in args:
			# Local FakeAmxHeapObject instances.
			if expect_buffer_size:
				locals_code += name + ");\n"
				assign_code += name + ");\n"
				expect_buffer_size = False
			if type.endswith("*"):
				locals_code += "\tsampgdk::FakeAmxHeapObject " + name + "_(fakeAmx"
				if type == "char *":
					# Output string buffer whose size is passed via next argument.
					locals_code += ", "
					expect_buffer_size = True
				elif type == "const char *":
					# Constant string.
					locals_code += ", " + name + ");\n"
				else:
					# Other output parameters.
					locals_code += ");\n"
			params_code += ",\n\t\t"
			if type == "int" or type == "bool":
				params_code += name
			elif type == "float":
				params_code += "amx_ftoc(" + name + ")"
			elif type.endswith("*"):
				params_code += name + "_.address()"
			else:
				raise InvalidNativeArgumentType(type)
			# Assignment of pointer arguments.
			if type.endswith("*"):
				if type == "const char *":
					pass
				elif type == "char *":
					assign_code += "\t" + name + "_.GetAsString(" + name + ", "
					expect_buffer_size = True
				else:
					assign_code += "\t*" + name + " = " + name + "_."
					if type == "int *":
						assign_code += "Get();\n"
					elif type == "bool *":
						assign_code += "GetAsBool();\n"
					elif type == "float *":
						assign_code += "GetAsFloat();\n"
					else:
						raise InvalidNativeArgumentType(type)
		params_code += "\n\t};\n"

	code += locals_code + params_code

	if len(assign_code) > 0:
		code += "\t" + return_type + " retval = "
	else:
		code += "\treturn "
	code += "fakeAmx->"
	if return_type == "bool":
		code += "CallNativeBool"
	elif return_type == "float":
		code += "CallNativeFloat"
	else:
		code += "CallNative"
	if len(args) > 0:
		code += "(native, params);\n"
	else:
		code += "(native);\n"
	if len(assign_code) > 0:
		code += assign_code
		code += "\treturn retval;\n"

	code += "}\n"
	return code

def main(argv):
	for native in get_natives(sys.stdin.read()):
		try:
			code = generate_native_code(*native)
			if code is not None:
				sys.stdout.write(code + "\n")
			sys.stdout.flush()
		except InvalidNativeArgumentType as arg:
			sys.stderr.write("Invalid argument type '" + arg.type + "' in declaration:\n" + line + "\n")

if __name__ == "__main__":
	main(sys.argv)
