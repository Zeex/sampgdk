#!/usr/bin/python

# This script generates code for SA-MP natives from their C declarations
# in sampgdk headers like a_players.h, etc.

import os
import re
import sys

from h2xml import *

class InvalidNativeArgumentType:
	def __init__(self, type):
		self.type = type
	
class NativeArgument:
	def __init__(self, string):
		match = re.match(r"([\w ]+ |[\w ]+\*)(\w+)$", string)
		self.type = match.group(1).strip()
		self.name = match.group(2).strip()

def to_argument_list(args):
	arg_list = []
	for type, name in args:
		yield type + " " + name

def generate_native_code(return_type, name, args, attrs):
	if "$skip" in attrs:
		return None

	# Write first line, same as function declaration + "{\n".
	code = "SAMPGDK_EXPORT " + return_type + " SAMPGDK_CALL sampgdk_" + name\
		+ "(" + ", ".join(to_argument_list(args)) + ") {\n"

	# A "static" variable that holds native address.
	if "$real_name" in attrs:
		real_name = attrs["$real_name"]
	else:
		real_name = name
	code += "\tstatic AMX_NATIVE native = sampgdk::Natives::GetInstance().GetNativeWarn(\"" + real_name + "\");\n"

	# Generate code for local variables, params array and ref argument assignment.
	if len(args) > 0:
		locals_code = ""
		params_code = "\tcell params[] = {\n\t\t0"
		assign_code = ""
		expect_buffer_size = False
		for type, name in args:
			# Local FakeAmxHeapObject instances.
			if expect_buffer_size:
				locals_code += name + ");\n"
				assign_code += name + ");\n"
				expect_buffer_size = False
			if type.endswith("*"):
				locals_code += "\tsampgdk::FakeAmxHeapObject " + name + "_"
				if type == "char *":
					# Output string buffer whose size is passed via next argument.
					locals_code += "("
					expect_buffer_size = True
				elif type == "const char *":
					# Constant string.
					locals_code += "(" + name + ");\n"
				else:
					# Other output parameters.
					locals_code += ";\n"
			# The "params" array.
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
		code += locals_code + params_code + assign_code

	code += "\treturn sampgdk::FakeAmx::"
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
	code += "}\n"
	return code

def generate_native_macro(return_type, name, args, comment):
	code = "#undef " + name + "\n"
	code += "#define " + name + " sampgdk_" + name + "\n"
	return code

def process_file(header_file, source_file, macros_file):
	""" Processes a C/C++ header file "src" finding native function
	    declarations and outputs generated code to "dest". """
	header = open(header_file, "r")
	source = open(source_file, "w")
	macros = open(macros_file, "w")
	for native in parse_header(header.read()):
		try:
			native_macro = generate_native_macro(*native)
			if native_macro is not None:
				macros.write(native_macro + "\n")
			native_code = generate_native_code(*native)
			if native_code is not None:
				source.write(native_code + "\n")
		except InvalidNativeArgumentType as arg:
			sys.stderr.write("Invalid argument type '" + arg.type + "' in declaration:\n" + line + "\n")
	header.close()
	source.close()
	macros.close()

if __name__ == "__main__":
	if len(sys.argv) <= 3:
		sys.stderr.write("Usage: " + os.path.basename(sys.argv[0]) + " <header-file> <source-file> <macros-file>\n")
		sys.stderr.write("  header-file <- file that contains declarations of native functions\n")
		sys.stderr.write("  source-file <- where to write generated code to\n")
		sys.stderr.write("  macros-file <- where to write #define's for generated natives\n")
	else:
		process_file(sys.argv[1], sys.argv[2], sys.argv[3])
