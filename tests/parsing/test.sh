#!/bin/bash

EXECUTABLE=./parsing_test

make tests/parsing/parsing_test -C ../.. || exit 1

for file in files/*; do
	$EXECUTABLE $file;
	echo
	echo "leaks for file" $file ":"
	leaks -atExit -- $EXECUTABLE $file >tmp
	echo -n $'\t'
	cat tmp | grep "total leaked bytes"
	echo
done

rm -f tmp
