# This file demonstrates how to compile the easybmp project on Linux.
#
# To compile easybmp do:
#
# make easybmp
#

GPP = g++
GCC = gcc
easybmp_OUTFILE = "plugins/easybmp.so"

COMPILE_FLAGS = -m32 -fPIC -c -O3 -w -D LINUX -D PROJECT_NAME=\"easybmp\" -I ./SDK/amx/

easybmp = -D easybmp $(COMPILE_FLAGS)

all: easybmp

clean:
	-rm -f *~ *.o *.so

easybmp: clean
	$(GPP) $(easybmp) ./SDK/amx/*.c
	$(GPP) $(easybmp) ./SDK/*.cpp
	$(GPP) $(easybmp) *.cpp
	$(GPP) -m32 -O2 -fshort-wchar -shared -o $(easybmp_OUTFILE) *.o
