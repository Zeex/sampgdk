#!/usr/bin/env python

import os
import re
import sys

from parse_header import *

def generate_native_macro(return_type, name, args, comment):
	code = "#undef " + name + "\n"
	code += "#define " + name + " sampgdk_" + name + "\n"
	return code

def main(argv):
	for native in get_natives(sys.stdin.read()):
		code = generate_native_macro(*native)
		if code is not None:
			sys.stdout.write(code + "\n")
		sys.stdout.flush()

if __name__ == "__main__":
	main(sys.argv)
