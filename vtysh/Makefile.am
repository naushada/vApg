
bin_PROGRAMS =vtysh 

vtysh_SOURCES = src/readlineIF.cc \
								src/vtysh.cc

vtysh_CPPFLAGS=-I$(srcdir)/inc \
               		-I/usr/local \
               		-I/usr/local/ACE-6.5.0/include

vtysh_CFLAGS=-g -Wall

vtysh_LDFLAGS=-L/usr/local/ACE-6.5.0/lib
vtysh_LDADD = -lreadline -lACE -ltinfo -lpthread
