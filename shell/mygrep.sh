#!/bin/sh -

if [ $# -lt 1 ];then
	echo "Please input context that you want find"
	exit 1
fi
grep -n --exclude-dir=".svn" --exclude="cscope.out" --exclude="tags" $1 ./* -r
