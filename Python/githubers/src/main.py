#!/usr/bin/env python3

import sys
import config
import githubers

CONFIG_PATH = "../resources/config.json"
def check_args(argv):
    if len(argv) != 3:
        print("Github login and password are expected as script parameters")
        return False
    return True



def main(argv):
    if not check_args(argv):
        return -1
    login, password = argv[1], argv[2]
    path = config.read_config(CONFIG_PATH)
    last_id = githubers.get_biggest_id(path)
    while last_id is not None:
        users_jsons = githubers.get_next_users(last_id, 1000, login, password)
        last_id = githubers.save_users(users_jsons, path)
        print("Last id in base: " + str(last_id))


if __name__ == "__main__":
    sys.exit(main(sys.argv))
