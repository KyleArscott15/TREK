#!/bin/bash

set -e

#clear

# format code
./crust.sh

#make clean
make
echo "compilation complete----------------------------------"

./trek
