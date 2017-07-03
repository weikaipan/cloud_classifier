#!/bin/bash
CONFIG=../config/variables
FILES=../data/raw_data/flag/2013/*.txt
OUTPUT=../one_file_test/
for i in $FILES; do
	echo "$i";
	./pdf $CONFIG $OUTPUT $i;
done
