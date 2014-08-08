# This file demonstrates how to compile the RouteConnectorPlugin project on Linux.
#
# To compile RouteConnectorPlugin do:
#
# make RouteConnectorPlugin 
#

GPP = g++
GCC = gcc
RouteConnectorPlugin_OUTFILE = "../RouteConnectorPlugin.so"

COMPILE_FLAGS = -std=c++0x -m32 -O3 -fPIC -c -I ./RouteConnector/cq -w -D LINUX -D PROJECT_NAME=\"RouteConnectorPlugin\"

RouteConnectorPlugin = -D RouteConnectorPlugin $(COMPILE_FLAGS)

all: RouteConnectorPlugin

clean:
	-rm -f *~ *.o *.so

RouteConnectorPlugin: clean
	$(GPP) $(RouteConnectorPlugin) ./RouteConnector/*.cpp
	$(GPP) -std=c++0x -m32 -L ./linux_tbb -ltbb -ltbbmalloc -fshort-wchar -shared -o $(RouteConnectorPlugin_OUTFILE) *.o

