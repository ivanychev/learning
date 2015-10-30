#!/usr/bin/env python3

def decrypt(msg, key):
	return str([x ^ key for x in msg])

def enumerate(msg):
	for x in range(256):
		print(decrypt(msg, x))



fin = open("start.dat", "r")
chiphro = fin.read()
enumerate(chiphro)
fin.close()