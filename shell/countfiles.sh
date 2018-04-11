#!/bin/bash

allpath=$(echo $PATH | sed 's/:/ /g')

for dir in $allpath
do
	count=0;
	perdir=$(ls $dir)
	for file in $perdir
	do
		count=$[$count + 1]
	done
	echo "$dir - $count"
done
