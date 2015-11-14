#!/usr/bin/python3
__author__ = "Sergey Ivanychev"

import sys

from pymongo import Connection
from pymongo.errors import ConnectionFailure

def main():
    try:
        c = Connection(host="localhost", port=27017)
        print("Connected successfully")
    except ConnectionFailure as e:
        sys.stderr.write("Could not connect to MongoDB: %s" % e)
        sys.exit(1)

if __name__ == "__main__":
    main()
