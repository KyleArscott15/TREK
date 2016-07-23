#!/bin/bash

set -e

#clear

# format code
./crust.sh

#make clean
make -j 4
echo "compilation complete----------------------------------"

./trek
