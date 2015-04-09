#! /usr/bin/python3.4

import os
import sys
import random

try:
	size = sys.argv[1]
	size = int(size)
except IndexError as a:
	print("Supposed to write size")
	exit()

if type(size) != type(1) or size < 1:
	print("Argument supposed to be positive number")
	exit()

try:
	sys.argv[2]
except IndexError as a:
	print("Type name of output file as second argument")
	exit()

f = open(sys.argv[2], "w")
wolfram = open("wolfram.txt", "w")

wolfram.write("[")
f.write(str(size) + "\n")
for i in range(size):
	wolfram.write("")
	for j in range(size):
		rand_num = random.randint(-2, 2)
		wolfram.write(str(rand_num))
		f.write(str(rand_num))
		if j < size - 1:
			wolfram.write(" ")
			f.write(" ")
	
	if (i < size - 1):
		wolfram.write("; ")
	else:
		wolfram.write("")
	f.write("\n")
wolfram.write("]\n")
f.write("\n")

f.close()
wolfram.close()