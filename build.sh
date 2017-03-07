#!/bin/bash

set -e

#clear

# format code
#./crust.sh

#make clean
#make -j 4
make
echo "compilation complete----------------------------------"

./trek
