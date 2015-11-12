#!/bin/bash

set -e

clear

make clean
make
echo "compilation complete----------------------------------"

./trek
