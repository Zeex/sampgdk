#!/usr/bin/env python2

import os
import re
import sys
import xml.dom.minidom

def parse_argument_list(string):
	""" For each entry of the arg_list returns a tuple made of
	    argument type and name. """
	args = []
	for arg in re.split(r"\s*,\s*", string):
		if len(arg) == 0:
			continue
		match = re.match(r"([\w ]+ |[\w ]+\*)(\w+)$", arg)
		if len(match.groups()) < 2:
			continue
		args.append((match.group(1).strip(), match.group(2).strip()))
	return args

def parse_attributes(string):
	""" Parse generator attributes. Each attribute is a key=value pair
	    separated by commas. """
	attrs = []
	if string != None:
		items = re.split(r"\s*,\s*", string)
		for item in items:
			attr = re.split(r"\s*=\s*", item, maxsplit=1)
			if len(attr) != 2:
				attrs.append((attr[0], None))
			else:
				attrs.append(tuple(attr))
	return attrs

def get_comment_text(comment):
	""" Extracts text in /* ... */ comments (C-style comments). """
	text = comment
	text = re.sub("^\s*/\*\s*", "", text)
	text = re.sub("\s*\*/\s*$", "", text)
	return text

def parse_function_decl(string, pattern):
	""" Returns a tuple of the form: (type, name, args, attributes)
	    where "args" is a again a list of tuples (type, name) that represents
	    function arguments and "attributes" is a dictionary of attributes. 

	    The pattern must have exactly 3 capture groups:
	      1. return type
	      2. function name
	      3. comma-seperated argument list
	"""
	match = re.match(pattern + r"\s*;\s*(/\*.*$)?", string)
	if match is None:
		return None
	type = match.group(1)
	name = match.group(2)
	args = []
	if match.group(3) is not None:
		args = parse_argument_list(match.group(3))
	comment = match.group(4)
	if comment is not None:
		comment = get_comment_text(comment)
	attrs = {}
	for attr in parse_attributes(comment):
		attrs[attr[0]] = attr[1]
	return (type, name, args, attrs)

def get_natives(text):
	pattern = r"^SAMPGDK_NATIVE\((int|bool|float),\s*(\w+)\((.*)\)\)"
	for line in text.splitlines():
		decl = parse_function_decl(line, pattern)
		if decl is not None:
			yield decl

def get_callbacks(text):
	pattern = r"^SAMPGDK_CALLBACK\((bool),\s*(\w+)\((.*)\)\)" # only "bool" callbacks are allowed
	for line in text.splitlines():
		decl = parse_function_decl(line, pattern)
		if decl is not None:
			yield decl

def main(argv):
	code = sys.stdin.read()
	document = xml.dom.minidom.Document()
	decls = document.createElement("declarations")
	for type, name, args, attrs in get_natives(code):
		native = document.createElement("native")
		native.setAttribute("type", type)
		native.setAttribute("name", name)
		for type, name in args:
			argument = document.createElement("argument")
			argument.setAttribute("type", type)
			argument.setAttribute("name", name)
			native.appendChild(argument)
		for name, value in attrs.items():
			attribute = document.createElement("attribute")
			attribute.setAttribute("name", name)
			if value is not None:
				attribute.setAttribute("value", value)
			native.appendChild(attribute)
		decls.appendChild(native)
	for type, name, args, attrs in get_callbacks(code):
		callback = document.createElement("callback")
		callback.setAttribute("type", type)
		callback.setAttribute("name", name)
		for type, name in args:
			argument = document.createElement("argument")
			argument.setAttribute("type", type)
			argument.setAttribute("name", name)
			callback.appendChild(argument)
		for name, value in attrs.items():
			attribute = document.createElement("attribute")
			attribute.setAttribute("name", name)
			if value is not None:
				attribute.setAttribute("value", value)
			callback.appendChild(attribute)
		decls.appendChild(callback)
	document.appendChild(decls)
	print document.toprettyxml(indent="\t")

if __name__ == "__main__":
	main(sys.argv)
