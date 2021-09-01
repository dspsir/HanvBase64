#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
# THIS FILE IS PART OF HANVBASE64
# makefile - The makefile to compile HanvBase64's demo
#
# License to copy and use this software is granted provided that it is identified
# as the "Cosmo. Wang" or "HANV" in all material mentioning or referencing this
# software or this function.
#
# Copyright (C) 2020, Cosmo. Wang (ciherenzai@hotmail.com). All rights reserved.
# Version: 1.0.0.0
#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

SHELL?=/bin/bash

CROSSCOMPILE ?=
CFLAGS += -Wall
CXXFLAGS = $(CFLAGS)

TARGET = $(notdir $(CURDIR))
CC=$(CROSSCOMPILE)gcc
CXX=$(CROSSCOMPILE)g++
SRC_C=$(wildcard *.c)
SRC_CXX=$(wildcard *.cpp)
OBJ_C=$(SRC_C:%.c=tmp/%.o)
OBJ_CXX=$(SRC_CXX:%.cpp=tmp/%.o)

.PHONY: all clean

all: $(OBJ_C) $(OBJ_CXX)
	$(CXX) $(CXXFLAGS) $(OBJ_C) $(OBJ_CXX) -o $(TARGET)

$(OBJ_C): tmp/%.o : %.c
	$(shell mkdir -p tmp/)
	$(CC) $(CFLAGS) -c -o $@ $^ -DHANV_TEST_BASE64

$(OBJ_CXX): tmp/%.o : %.cpp
	$(shell mkdir -p tmp/)
	$(CXX) $(CXXFLAGS) -c -o $@ $^ -DHANV_TEST_BASE64
	
clean: 
	rm -rf tmp
	rm -rf $(TRAGET)