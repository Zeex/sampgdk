#!/usr/bin/env python

import argparse
import os
import random
import string
import subprocess
import sys

def generate_password(size=10, chars=string.ascii_letters + string.digits):
	# By Ignacio Vazquez-Abram at StackOverflow:
	# http://stackoverflow.com/questions/2257441/python-random-string-generation-with-upper-case-letters-and-digits
	return ''.join(random.choice(chars) for x in range(size))

def get_arguments(args):
	parser = argparse.ArgumentParser()

	parser.add_argument("-announce", type=int, choices=[0, 1], default=0)
	parser.add_argument("-bind")
	parser.add_argument("-filterscrips", nargs="*")
	parser.add_argument("-gamemode0", required=True)
	for i in range(1, 10):
		parser.add_argument("-gamemode" + str(i))
	parser.add_argument("-gamemodetext")
	parser.add_argument("-hostname")
	parser.add_argument("-lanmode", type=int, choices=[0, 1], default=0)
	parser.add_argument("-logtimeformat")
	parser.add_argument("-mapname")
	parser.add_argument("-maxplayers", type=int, default=1)
	parser.add_argument("-maxnpc", type=int, default=0)
	parser.add_argument("-output", type=int, choices=[0, 1], default=0)
	parser.add_argument("-password")
	parser.add_argument("-path", default="")
	parser.add_argument("-plugins", nargs="*")
	parser.add_argument("-port", type=int, default=7777)
	parser.add_argument("-query", type=int, choices=[0, 1], default=0)
	parser.add_argument("-rcon", type=int, choices=[0, 1], default=0)
	parser.add_argument("-rcon_password", default=generate_password())
	parser.add_argument("-timestamp", type=int, choices=[0, 1], default=1)
	parser.add_argument("-weburl")

	args = parser.parse_args(args)
	return vars(args)

def write_config(filename, options, newline="\n"):
	file = open(filename, "w")
	for name, value in options.items():
		if value is not None:
			file.write(name + " " + str(value) + newline)
	file.close()

def run(options):
	write_config("server.cfg", args)
	server_root = args["path"]
	if os.name == "nt":
		server_exe = "samp-server.exe"
	else:
		server_exe = "samp03svr"
	server_path = os.path.join(server_root, server_exe)
	subprocess.call(server_path)

if __name__ == "__main__":
	run(get_arguments(sys.argv[1:]))
