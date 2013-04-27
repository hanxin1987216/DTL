#
# Include this file at the begin of makefile, to determine the compilation environment:
# CPU: [i386|x64]
# PLATFORM: [linux]
# BUILD:[debug|release]

include $(DTSRC)/build.config

ifeq ("$(BUILD)", "")
BUILD = debug
endif

PLATFORM = linux

ifeq ("$(CPU)", "x64")
PLATFORM = linux
endif