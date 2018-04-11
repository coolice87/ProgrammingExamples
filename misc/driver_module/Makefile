#this module is a example of driver

PWD=$(shell pwd)
LINUX_SRC_ROOT=/home/he_liangbin/svn/linux_v3.10.y/Trunk/src

obj-m := driver_test.o
driver_test-y := driver_module.o

module:
	make -C $(LINUX_SRC_ROOT) M=$(PWD) modules

clean:
	make -C $(LINUX_SRC_ROOT) M=$(PWD) clean
