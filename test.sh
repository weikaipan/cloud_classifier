#!/bin/bash
for i in $( ls  ../data/raw_data/flag/2013/ | shuf -n50); do
	echo item: $i
done
