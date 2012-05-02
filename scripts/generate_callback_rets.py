#!/usr/bin/env python

import os
import re
import sys

from parse_header import *

def main(argv):
	code = ""
	for type, name, args, attrs in get_callbacks(sys.stdin.read()):
		if "$ret" in attrs:
			bad_ret = attrs["$ret"]
			code += "callbackBadRetVals[\"" + name + "\"] = " + bad_ret + ";\n"
	sys.stdout.write(code)

if __name__ == "__main__":
	main(sys.argv)
