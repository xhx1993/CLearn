ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

CLD =

ifeq "$(PLATFORM)" "linux"
  CLD = child
endif
ifeq "$(PLATFORM)" "solaris"
  CLD = child
endif

PROGS = sigusr reenter child tsleep2 read1 read2 critical sigjmp \
		suspend1 suspend2 myabort sigtstp sig2str alrm pra10_6 myabort1 printsignal
MOREPROGS = systest2 tsleep2

all:	$(PROGS) $(MOREPROGS) abort.o sleep1.o sleep2.o system.o $(CLD)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

tsleep2:	tsleep2.o  $(LIBAPUE)
		$(CC) $(CFLAGS) -o tsleep2 tsleep2.o  $(LDFLAGS) $(LDLIBS)

systest2:	systest2.o system.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o systest2 systest2.o system.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o file.hole $(CLD)

include $(ROOT)/Make.libapue.inc

