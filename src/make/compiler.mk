#
# Configuration file for Compiler
# Author: han.xin@datatom.com
#

####################################################################################################
#
# linux - gcc
#
ifeq ("$(PLATFORM)", "linux")

# C compiler on linux
CC = gcc

# C++ compiler on linux
CXX = g++
EXE_LINKER = g++
SO_LINKER = g++

# Static library linker on linux
LIBLINKER = ar

# Basic linker flags on linux
LDBASIC_FLAGS = -L. -Wl,-rpath,./:$(CUSTOM_VPATH_LDFLAGS)  $(CUSTOM_LINUX_LDFLAGS)
SO_BASIC_FLAGS = -shared
EXE_BASIC_FLAGS =
STATICLIB_BASIC_FLAG = -rc

endif
