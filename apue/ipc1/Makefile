ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


PROGS = pipe1 pipe2 popen2 popen1 myuclc popen3 add2 pipe4 testmsg\
	tshm devzero devzero1 pra3 rwfifo pra12 devzero2

all: $(PROGS) popen.o slock.o tellwait.o

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS) -lpthread

slock.o: 

.PHONY: chean
clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
