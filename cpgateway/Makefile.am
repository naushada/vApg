#/*!Name of the binary*/

noinst_LIBRARIES = libcpgw.a

libcpgw_a_SOURCES = src/cpgateway.cc \
										src/CPGatewayStateActivated.cc \
										src/CPGatewayState.cc \
										src/CPGatewayStateLocked.cc \
										src/CPGatewayStateUnLocked.cc

libcpgw_a_CPPFLAGS=-I$(srcdir)/inc \
                  -I$(top_srcdir)/common/inc \
                  -I/usr/local \
                  -I/usr/local/ACE-6.5.0/include

libcpgw_a_CXXFLAGS=-g -Wall -std=gnu++11

libcpgw_a_AR=ar rvs
#libipc_a_LDFLAGS=-L/usr/localACE-6.5.0/lib


