#!/bin/sh

for dev in /dev/sd*
do
	devname=$(echo $dev | awk -F/ '{print $NF}')
	echo $dev $devname
	if [ "$devname" = "sd*" ]; then
		continue
	fi

	mkdir /var/$devname
	mount -t vfat $dev /var/$devname
	if [ -f "/var/$devname/predictor_5.dat" ]
	then
		cp /var/$devname/predictor_5.dat /mnt/mtd/nandflash/
		echo "cp predictor_5.dat success"
		umount /var/$devname
		break;
	fi
	umount /var/$devname
done
