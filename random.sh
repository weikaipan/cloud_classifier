#!/bin/bash
CONFIG=../config/variables
DIR=../data/raw_data/flag/2013/
OUTPUT=../one_file_test

j=201
while [ $j -le 500 ]; do
  echo "Dealing with $j"
  for i in $(ls "$DIR" | shuf -n50) ;do
      ./create_data $CONFIG $OUTPUT/$j.txt $i;
  done
  j=$(( j+1 ))
done
