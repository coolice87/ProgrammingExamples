#/bin/bash

CHECK_DIR="/home/he_liangbin/test /home/he_liangbin/tools"

exec > report.rpt

echo "Top ten disk space usage"
echo "for $CHECK_DIR directory"

for dir in $CHECK_DIR
do
	echo ""
	echo "The $dir directory:"
	du -S $dir/* 2>/dev/null |
	sort -rn |
	sed '{11,$D; =}' |
	sed '{N; s/\n/ /}' |
	awk '{print $1 ":\t" $2 "\t" $3}'
done

