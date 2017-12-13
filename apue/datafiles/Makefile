ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


PROGS =  getpwuid getpwnam getspent getgrnam getgroups uname \
		strftime pra6_5

all : $(PROGS)

%:  %.c $(LIBAPUE) 
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(tempfiles) *.o

include $(ROOT)/Make.libapue.inc
