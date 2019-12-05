
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

CFLAGS  += -I$(includedir)/sysapi/pciemcc -I$(srcdir)/include
CFLAGS  += -Wall -Werror -O1
#get from hisi SDK
CFLAGS += -march=armv7-a -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations

#LDFLAGS += -static

LDFLAGS += -L$(libdir) -lpciemcc -lpthread

OBJS = pciemcc_host.o

BIN = pciemcc

all: $(BIN)
#	cp $(BIN) $(bindir)/

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

clean:
	$(RM) $(BIN) $(OBJS) 

