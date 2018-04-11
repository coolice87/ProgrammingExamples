#! /bin/sh -

func()
{
	while true
	do
		echo -n "continue y/n: "
		read var
		
		case $var in
			[Yy])	return 0;;
			[Nn])	return 1;;
			*)	echo "Answer y or n"
		esac
	done;
}

if func
then
	echo "continue"
	continue
else
	echo "quit"
	break
fi
