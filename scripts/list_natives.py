#!/usr/bin/env python2

import sys

from parse_header import *

def main(argv):
	prefix = ""

	if len(argv) > 1:
		prefix = argv[1]

	for type, name, args, attrs in get_natives(sys.stdin.read()):
		print prefix + name

if __name__ == "__main__":
	main(sys.argv)
