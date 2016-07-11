#!/bin/bash

CONFIG=./cpp.cfg

# only cleans up source code in the current directory
for file in `ls *.cpp *.h`
do
	uncrustify -q -c $CONFIG -f ${file} -o ${file}
done

rm -f *unc-backup*
