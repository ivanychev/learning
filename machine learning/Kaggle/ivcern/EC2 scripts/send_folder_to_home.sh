#!/usr/bin/env bash
#
# Usage: $ ./send_folder_to_home.sh folder ~
source config.txt

scp -r -i $pemfile $1 ubuntu@$host:~
