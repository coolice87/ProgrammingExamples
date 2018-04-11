#! /bin/sh -

int=1

while [ $int -lt 5 ]
do 
	sq=`expr $int \* $int`
	echo $sq
	int=`expr $int + 1`
done

int=1
until [ $int -ge 5 ]
do 
	sq=`expr $int \* $int`
	echo $sq
	int=`expr $int + 1`
done
