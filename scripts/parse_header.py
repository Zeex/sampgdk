#!/usr/bin/env python

import os
import re
import sys
import xml.dom.minidom

def parse_argument_list(string):
	""" For each entry of the arg_list returns a tuple made of
	    argument type and name. """
	args = []
	for string in re.split(r"\s*,\s*", string):
		if len(string) == 0:
			continue
		match = re.match(r"([\w ]+ |[\w ]+\*)(\w+)$", string)
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
	    function arguments and "attributes" is a dictionary of attributes. """
	match = re.match(pattern, string)
	if match == None:
		return None
	type = match.group(1)
	name = match.group(2)
	args = parse_argument_list(match.group(3))
	comment = match.group(4)
	if comment is not None:
		comment = get_comment_text(comment)
	attrs = {}
	for attr in parse_attributes(comment):
		attrs[attr[0]] = attr[1]
	return (type, name, args, attrs)

def parse_header(text):
	pattern = r"^SAMPGDK_NATIVE\((int|bool|float),\s*(\w+)\((.*)\)\);\s*(/\*.*$)?"
	for line in text.splitlines():
		decl = parse_function_decl(line, pattern)
		if decl is not None:
			yield decl

def main(argv):
	document = xml.dom.minidom.Document()
	exports = document.createElement("exports")
	for type, name, args, attrs in parse_header(sys.stdin.read()):
		function = document.createElement("function")
		function.setAttribute("type", type)
		function.setAttribute("name", name)
		for type, name in args:
			argument = document.createElement("argument")
			argument.setAttribute("type", type)
			argument.setAttribute("name", name)
			function.appendChild(argument)
		for name, value in attrs.items():
			attribute = document.createElement("attribute")
			attribute.setAttribute("name", name)
			if value is not None:
				attribute.setAttribute("value", value)
			function.appendChild(attribute)
		exports.appendChild(function)
		pass
	document.appendChild(exports)
	print document.toprettyxml(indent="\t")

if __name__ == "__main__":
	main(sys.argv)
