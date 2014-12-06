#! /usr/bin/python3

import os
import sys

source 		= sys.argv[1]
name_list 	= source.split(".")
name 		= name_list[0]

os.system("clang " + source + " -o " + name + ".out -g -std=c11")
