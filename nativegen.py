#!/usr/bin/python

# This script generates code for SA-MP natives from their C declarations
# in sampgdk headers like a_players.h, etc.

import os
import re
import sys

class InvalidNativeArgumentType:
	def __init__(self, type):
		self.type = type
	
class NativeArgument:
	def __init__(self, string):
		match = re.match(r"([\w ]+ |[\w ]+\*)(\w+)$", string)
		self.type = match.group(1).strip()
		self.name = match.group(2).strip()

def parse_argument_list(arg_list):
	""" For each entry of the arg_list returns a tuple made of
	    argument type and name. """
	for string in arg_list:
		if len(string) == 0:
			continue
		yield NativeArgument(string)

def parse_attributes(string):
	""" Parse generator attributes. Each attribute is a key=value pair
	    separated by commas. """
	attrs = dict()
	if string != None:
		items = string.split(",")
		for item in items:
			nv = item.split("=")
			if len(nv) > 1:
				attrs[nv[0].strip()] = nv[1].strip()
			else:
				attrs[nv[0].strip()] = None
	return attrs

def get_comment_text(comment):
	""" Extracts text in /* ... */ comments (C-style comments). """
	text = comment
	text = re.sub("^\s*/\*\s*", "", text)
	text = re.sub("\s*\*/\s*$", "", text)
	return text

def generate_native_code(return_type, name, arg_list, comment):
	if comment is not None:
		comment = get_comment_text(comment)
	attrs = parse_attributes(comment)

	if "$skip" in attrs:
		return None

	# Write first line, same as function declaration + "{\n".
	code = "SAMPGDK_EXPORT " + return_type + " SAMPGDK_CALL sampgdk_native_" + name\
		+ "(" + ", ".join(arg_list) + ") {\n"

	# A "static" variable that holds native address.
	if "$real_name" in attrs:
		real_name = attrs["$real_name"]
	else:
		real_name = name
	code += "\tstatic AMX_NATIVE native = sampgdk::Natives::GetInstance().GetNativeWarn(\"" + real_name + "\");\n"

	# Generate code for local variables, params array and ref argument assignment.
	locals_code = ""
	params_code = "\tcell params[] = {\n\t\t0"
	assign_code = ""
	expect_buffer_size = False
	for arg in parse_argument_list(arg_list):
		# Local FakeAmxHeapObject instances.
		if expect_buffer_size:
			locals_code += arg.name + ");\n"
			assign_code += arg.name + ");\n"
			expect_buffer_size = False
		if arg.type.endswith("*"):
			locals_code += "\tsampgdk::FakeAmxHeapObject " + arg.name + "_"
			if arg.type == "char *":
				# Output string buffer whose size is passed via next argument.
				locals_code += "("
				expect_buffer_size = True
			elif arg.type == "const char *":
				# Constant string.
				locals_code += "(" + arg.name + ");\n"
			else:
				# Other output parameters.
				locals_code += ";\n"
		# The "params" array.
		params_code += ",\n\t\t"
		if arg.type == "int" or arg.type == "bool":
			params_code += arg.name
		elif arg.type == "float":
			params_code += "amx_ftoc(" + arg.name + ")"
		elif arg.type.endswith("*"):
			params_code += arg.name + "_.address()"
		else:
			raise InvalidNativeArgumentType(arg.type)
		# Assignment of pointer arguments.
		if arg.type.endswith("*"):
			if arg.type == "const char *":
				pass
			elif arg.type == "char *":
				assign_code += "\t" + arg.name + "_.GetAsString(" + arg.name + ", "
				expect_buffer_size = True
			else:
				assign_code += "\t*" + arg.name + " = " + arg.name + "_."
				if arg.type == "int *":
					assign_code += "Get();\n"
				elif arg.type == "bool *":
					assign_code += "GetAsBool();\n"
				elif arg.type == "float *":
					assign_code += "GetAsFloat();\n"
				else:
					raise InvalidNativeArgumentType(arg.type)
	params_code += "\n\t};\n"
	code += locals_code + params_code + assign_code

	code += "\treturn sampgdk::FakeAmx::"
	if return_type == "bool":
		code += "CallNativeBool"
	elif return_type == "float":
		code += "CallNativeFloat"
	else:
		code += "CallNative"
	code += "(native, params);\n}\n"
	return code

def generate_native_macro(return_type, name, arg_list, comment):
	code = "#undef " + name + "\n"
	code += "#define " + name + " sampgdk_native_" + name + "\n"
	return code

def process_native_decl(string):
	""" Returns a tuple of (type, name, arg_list) where arg_list is a
	    list of arguments and each argument is a string that consists
	    of an argument type and name (no default values can occur). """
	match = re.match(r"SAMPGDK_EXPORT (int|bool|float) SAMPGDK_CALL (\w+)\((.*)\);\s*(/\*.*$)?", string)
	if match == None:
		return None
	return_type = match.group(1)
	name = match.group(2)
	arg_list = match.group(3).split(", ")
	comment = match.group(4)
	return (return_type, name, arg_list, comment)	

def process_file(header_file, source_file, macros_file):
	""" Processes a C/C++ header file "src" finding native function
	    declarations and outputs generated code to "dest". """
	header = open(header_file, "r")
	source = open(source_file, "w")
	macros = open(macros_file, "w")
	for line in header:
		line = line.strip()
		if len(line) == 0:
			continue
		try:
			native = process_native_decl(line)
			if native is not None:
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
