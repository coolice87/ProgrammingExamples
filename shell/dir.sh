#! /bin/sh -
# use continue break case

while true
do
	#display menu
	echo "1: enter file"
	echo "2: enter dir"
	echo "3: quit"
	echo
	
	#enter choice
	echo -n "enter choice: "
	read CHOICE
	
	case $CHOICE in
		1) #read file
			echo -n "read a file: "
			read FILE;;
		2) #read dir
			echo -n "read a dir: "
			read dir
			if [ ! -d $dir ]
			then
				echo "$dir is not a dir!"
				continue
			fi
			cd $dir;;
		3) :;;
		*)
			echo "choice is not valid"
			continue
			
	esac
	
	# show file and dir information
	case $CHOICE in
		1)	ls -l $FILE;;
		2)	ls -l ;;
		3)	break;;
	esac
done


