#!/bin/sh -

while getopts mdy OPTION
do
	case $OPTION in
		m) date '+%m';;
		d) date '+%d';;
		y) date '+%y';;
		\?) echo "enter options is error"
	esac
done

