#!/usr/bin/env bash

source config.txt

ssh -i $pemfile ubuntu@$host
