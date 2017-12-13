ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS=-pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS=-pthread
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS=-lsocket -lnsl
endif

PROGS =	bindunix pollmsg sendmsg
FDPASS =

ifeq "$(PLATFORM)" "linux"
	FDPASS = recvfd2.o sendfd2.o
endif
ifeq "$(PLATFORM)" "freebsd"
	FDPASS = recvfd2.o sendfd2.o
endif

all: $(PROGS) $(FDPASS)

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc

