#!/bin/bash
CONFIG=../config/variables
FILES=../data/raw_data/flag/2013/*.txt
OUTPUT=../one_file_test/output.txt
IND=../one_file_test/ind.txt

for i in $FILES; do
	echo "$i";
	./create_data $CONFIG $OUTPUT $IND $i;
done
