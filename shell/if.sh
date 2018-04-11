#! /bin/sh -

#check argument
if [ $# -ne 1 ]
then
	echo "usage: $0 <directory>"
	exit 1
fi

#check directory
if [ ! -d $1 ] 
then
	echo "$1 is not directory"
	exit 2
fi

cd $1
ls -l

read var
echo $var

