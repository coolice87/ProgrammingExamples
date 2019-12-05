rootdir = ..
srcdir = $(rootdir)/src
toolsdir = $(rootdir)/tools
testdir = $(rootdir)/test

lib:
	make -C $(srcdir) 

all:
	make -C $(srcdir)
	make -C $(testdir)

test:
	make -C $(testdir)

clean:
	make -C $(srcdir) clean
	make -C $(testdir) clean
