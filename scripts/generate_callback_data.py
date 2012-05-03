#!/usr/bin/env python

import os
import re
import sys

from parse_header import *

def main(argv):
	print "typedef std::map<std::string, cell> CallbackBadRetMap;"
	print "static CallbackBadRetMap callbackBadRetMap;"
	print ""
	print "void CallbackDataInit() {"
	for type, name, args, attrs in get_callbacks(sys.stdin.read()):
		if "$badRet" in attrs:
			bad_ret = attrs["$badRet"]
			print "\tcallbackBadRetMap[\"" + name + "\"] = " + bad_ret + ";"
	print "}"

if __name__ == "__main__":
	main(sys.argv)
