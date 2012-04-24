#!/usr/bin/python

import getopt
import os
import sys

def usage():
	print "Usage:", os.path.basename(sys.argv[0]), "[-hv]"
	print "  -v, --verbose  do not strip trailing 0's"
	print "  -h, --help     show this message and exit"

def main():
	try:
		opts, args = getopt.getopt(sys.argv[1:], "hvg", ["help", "verbose", "git"])
	except getopt.GetoptError, err:
		print str(err)
		usage()
		sys.exit(1)
	verbose = False
	git = False
	for o, a in opts:
		if o in ("-v", "--verbose"):
			verbose = True
		elif o in ("-h", "--help"):
			usage()
			sys.exit()
		elif o in ("-g", "--git"):
			pass
	version = sys.stdin.readline().strip().split(".")
	if len(version) > 0:
		print version[0]
	elif verbose:
		print "0"
	if len(version) > 1:
		print version[1]
	elif verbose:
		print "0"
	if len(version) > 2:
		print version[2]
	elif verbose:
		print "0"
	if len(version) > 3:
		print version[3]
	elif verbose:
		print "0"

if __name__ == "__main__":
	main()
