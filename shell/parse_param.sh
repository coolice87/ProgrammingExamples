#!/bin/sh -

count=1
for param in "$*"
do
	echo "\$* param $count=$param"
	count=`expr $count + 1`
done

count=1
for param in "$@"
do
	echo "\$@ param $count=$param"
	count=`expr $count + 1`
done

