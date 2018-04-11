#! /bin/sh -

if [ $# -eq 0 ]
then
	echo "usage: $0 <integer list>"
	exit 1
fi

sum=0;

until [ $# -eq 0 ]
do
	sum=`expr $sum + $1`
	shift 2	
done

echo "sum: $sum"

