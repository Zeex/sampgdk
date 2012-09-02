#!/usr/bin/env python2

import sys

from parse_header import *

def main(argv):
	for type, name, args, attrs in get_callbacks(sys.stdin.read()):
		print name

if __name__ == "__main__":
	main(sys.argv)
