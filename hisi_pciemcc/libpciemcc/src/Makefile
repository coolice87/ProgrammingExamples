
rootdir = ..
srcdir = $(rootdir)/src
bindir = $(rootdir)/bin
libdir = $(rootdir)/lib
includedir = $(rootdir)/include
testdir = $(rootdir)/test

CROSS_COMPILE = arm-hisiv300-linux-

CC = @echo " gcc   $@"; $(CROSS_COMPILE)gcc
LD = @echo " ld    $@"; $(CROSS_COMPILE)ld
AR = @echo " ar    $@"; $(CROSS_COMPILE)ar
RM = @echo " rm    $@"; rm -rf
STRIP = @echo " strip  $@"; $(CROSS_COMPILE)strip

#library information
lib_name="libpciemcc"
svn_url= $(shell svn info | grep '^URL:' | awk -F ': ' '{print $$2}')
svn_ver= $(shell svn info | grep '^Revision:' | awk -F ': ' '{print $$2}')
build_date= $(shell date '+%Y-%m-%d_%H:%M:%S')
build_usr= $(shell id | awk -F ' ' '{print $$1}')
build_host= $(shell hostname)

CFLAGS += -DLIB_NAME="\"$(lib_name)"\"
CFLAGS += -DSVN_URL="\"$(svn_url)"\"
CFLAGS += -DSVN_VERSION="\"$(svn_ver)"\"
CFLAGS += -DBUILD_DATE="\"$(build_date)"\"
CFLAGS += -DBUILD_USR="\"$(build_usr)"\"
CFLAGS += -DBUILD_HOST="\"$(build_host)"\"

CFLAGS  += -I$(includedir)/sysapi/pciemcc -I$(srcdir)/include
CFLAGS  += -Wall -Werror -O1
#CFLAGS  += -Wall -O1
#get from hisi SDK
CFLAGS += -march=armv7-a -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations

AFLAGS     += -r

OBJS =  pcie_dev.o \
		pcie_msg.o

LIB = libpciemcc.a


all: $(LIB)
	@echo "svn version: $(version)"

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB): $(OBJS)
	$(AR) $(AFLAGS) $@ $^
	cp $(LIB) $(bindir)/
	cp $(LIB) $(libdir)/

clean:
	$(RM) $(LIB) $(OBJS) 

