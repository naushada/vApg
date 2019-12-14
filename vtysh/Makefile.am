
bin_PROGRAMS =vtysh

vtysh_SOURCES = src/readlineIF.cc \
		src/vtysh.cc

vtysh_CPPFLAGS=-I$(srcdir)/inc \
       	       -I/usr/local \
               -I/usr/local/ACE-6.5.0/includea \
               -I/home/naushada/sw-packages/ACE_wrappers

vtysh_CXXFLAGS=-g -Wall -std=gnu++11

vtysh_LDFLAGS=-L/usr/local/ACE-6.5.0/lib \
              -L/home/naushada/sw-packages/ACE_wrappers/ace

vtysh_LDADD = -lreadline -lACE -ltinfo -lpthread
