#!/bin/bash
#archive all file or directory in config_backup file
#config_backup file need be in $HOME/archive directory

ROOT_DIR=$HOME/archive
if [ ! -d "$ROOT_DIR" ]; then
	mkdir $ROOT_DIR
fi

#create backup directory
YEAR=$(date +%Y)
MONTH=$(date +%m)
DATE=$(date +%d)
ARCHIVE_DIR=$ROOT_DIR/$YEAR/$MONTH/$DATE

if [ ! -d "$ROOT_DIR/$YEAR" ]; then
	mkdir $ROOT_DIR/$YEAR
	mkdir $ROOT_DIR/$YEAR/$MONTH
	mkdir $ROOT_DIR/$YEAR/$MONTH/$DATE
elif [ ! -d "$ROOT_DIR/$YEAR/$MONTH" ]; then
	mkdir $ROOT_DIR/$YEAR/$MONTH
	mkdir $ROOT_DIR/$YEAR/$MONTH/$DATE
elif [ ! -d "$ROOT_DIR/$YEAR/$MONTH/$DATE" ]; then
	mkdir $ROOT_DIR/$YEAR/$MONTH/$DATE
fi

#config file which files or directory to backup
CONFIG_FILE=/$ROOT_DIR/config_bakcup
TMP_CONFIG_FILE=/$ROOT_DIR/config_backup_tmp
if [ ! -f "$CONFIG_FILE" ];then
	echo "$CONFIG_FILE is not exist"
	exit 1
else
	sed '/^$/d' $CONFIG_FILE > $TMP_CONFIG_FILE
fi

#Redirect StdIn to name of Config file
exec < $TMP_CONFIG_FILE
#read 1st record
read FILE_NAME

while [ $? -eq 0 ]
do
	if [ -f $FILE_NAME ] || [ -d $FILE_NAME ]; then #directory or file
		echo $FILE_NAME
		TMP_FILE=$(echo $FILE_NAME | awk -F/ '{print $NF}')
		TOP_FILE=$(echo $FILE_NAME | sed "s/${TMP_FILE}//")
		cd $TOP_FILE
		tar zcf $TMP_FILE.tgz $TMP_FILE
		mv $TMP_FILE.tgz $ARCHIVE_DIR
		cd - 1>/dev/null
	: '
	elif [ -f $FILE_NAME ]; then #file
		echo $FILE_NAME
		TMP_FILE=$(echo $FILE_NAME | awk -F/ '{print $NF}')
		echo $TMP_FILE
		TOP_FILE=$(echo $FILE_NAME | sed "s/${TMP_FILE}//")
		TMP2_FILE=$(echo $TMP_FILE | awk -F. '{print $1}')
		cd $TOP_FILE
		tar zcf $TMP2_FILE.tgz $TMP_FILE
		mv $TMP2_FILE.tgz $ARCHIVE_DIR
		cd - 1>/dev/null
		'
	fi
	read FILE_NAME
done

rm $TMP_CONFIG_FILE

