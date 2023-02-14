#############################################################################
# Makefile for building: stray68K
#############################################################################

####### Compiler, tools and options

CC            = gcc
CFLAGS        = -pipe -g -Wall -Wextra -fPIC -O3
DEL_FILE      = rm -f
MKDIR         = mkdir -p
DEL_DIR       = rmdir
ROOT_DIR      := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CXX       = g++
CXXFLAGS  = -std=c++14
LIBS      = -lwthttp -lwt

LEX           = flex
YACC          = bison

PORT ?= 8080
HOST ?= 127.0.0.1

####### Output directory

OBJECTS_DIR   = objects
BUILD_DIR     = build
ASSEMBLER_DIR = $(ROOT_DIR)/src/assembler
EMULATOR_DIR  = $(ROOT_DIR)/src/emulator
WWW_DIR       = $(ROOT_DIR)/src/www
SOURCE_DIR    = $(ROOT_DIR)/src

####### Files

SOURCES       = $(EMULATOR_DIR)/emulator.c \
		$(ASSEMBLER_DIR)/assembler.c \
		$(ASSEMBLER_DIR)/dictionary.c \
		$(ASSEMBLER_DIR)/lexical.c \
		$(ASSEMBLER_DIR)/semantic.c \
		$(ASSEMBLER_DIR)/strcmpci.c \
		$(ASSEMBLER_DIR)/syntactic.c \
		$(ASSEMBLER_DIR)/JSON.c \
		$(EMULATOR_DIR)/cpu.c \
		$(EMULATOR_DIR)/handler.c \
		$(SOURCE_DIR)/main.c \
		$(EMULATOR_DIR)/ram.c \
		$(EMULATOR_DIR)/utils.c \
		$(WWW_DIR)/header.cpp \
		$(WWW_DIR)/footer.cpp \
		$(WWW_DIR)/editor.cpp \
		$(WWW_DIR)/dispatcher.cpp \
		$(WWW_DIR)/memory.cpp \
		$(WWW_DIR)/console.cpp \
		$(WWW_DIR)/register.cpp

OBJECTS       = $(OBJECTS_DIR)/emulator.o \
		$(OBJECTS_DIR)/assembler.o \
		$(OBJECTS_DIR)/dictionary.o \
		$(OBJECTS_DIR)/lexical.o \
		$(OBJECTS_DIR)/semantic.o \
		$(OBJECTS_DIR)/strcmpci.o \
		$(OBJECTS_DIR)/syntactic.o \
		$(OBJECTS_DIR)/cpu.o \
		$(OBJECTS_DIR)/main.o \
		$(OBJECTS_DIR)/ram.o \
		$(OBJECTS_DIR)/handler.o \
		$(OBJECTS_DIR)/JSON.o \
		$(OBJECTS_DIR)/utils.o \
		$(OBJECTS_DIR)/header.o \
		$(OBJECTS_DIR)/footer.o \
		$(OBJECTS_DIR)/editor.o \
		$(OBJECTS_DIR)/dispatcher.o \
		$(OBJECTS_DIR)/memory.o \
		$(OBJECTS_DIR)/console.o \
		$(OBJECTS_DIR)/register.o

TARGET        = $(BUILD_DIR)/stray68K-Web



first: all


####### Build rules

$(BUILD_DIR)/stray68K-Web:  $(OBJECTS)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

generators: $(ASSEMBLER_DIR)/lexical.c $(ASSEMBLER_DIR)/lexical.h $(ASSEMBLER_DIR)/syntactic.c $(ASSEMBLER_DIR)/syntactic.h

all: generators $(BUILD_DIR)/stray68K-Web


clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)

cleanassembler:
	-$(DEL_FILE) $(ASSEMBLER_DIR)/lexical.c $(ASSEMBLER_DIR)/lexical.h $(ASSEMBLER_DIR)/syntactic.c $(ASSEMBLER_DIR)/syntactic.h

cleanall: clean cleanassembler

rebuild: cleanall all

####### Create dirs


deepclean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
	rm -rf $(OBJECTS_DIR)
	rm -rf $(BUILD_DIR)

create:
	mkdir build
	mkdir objects


####### Compile


$(ASSEMBLER_DIR)/lexical.c $(ASSEMBLER_DIR)/lexical.h: $(ASSEMBLER_DIR)/lexical.l $(ASSEMBLER_DIR)/syntactic.h
	$(LEX) --outfile=$(ASSEMBLER_DIR)/lexical.c --header-file=$(ASSEMBLER_DIR)/lexical.h $<

$(ASSEMBLER_DIR)/syntactic.c $(ASSEMBLER_DIR)/syntactic.h: $(ASSEMBLER_DIR)/syntactic.y
	$(YACC) --output=$(ASSEMBLER_DIR)/syntactic.c --header=$(ASSEMBLER_DIR)/syntactic.h --debug $<


$(OBJECTS_DIR)/emulator.o: $(EMULATOR_DIR)/emulator.c $(EMULATOR_DIR)/emulator.h \
		$(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/handler.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/ram.h 
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/emulator.o $(EMULATOR_DIR)/emulator.c

$(OBJECTS_DIR)/assembler.o: $(ASSEMBLER_DIR)/assembler.c $(ASSEMBLER_DIR)/assembler.h \
		$(ASSEMBLER_DIR)/clowncommon.h \
		$(ASSEMBLER_DIR)/semantic.h \
		$(ASSEMBLER_DIR)/syntactic.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/assembler.o $(ASSEMBLER_DIR)/assembler.c

$(OBJECTS_DIR)/dictionary.o: $(ASSEMBLER_DIR)/dictionary.c $(ASSEMBLER_DIR)/dictionary.h \
		$(ASSEMBLER_DIR)/clowncommon.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/dictionary.o $(ASSEMBLER_DIR)/dictionary.c

$(OBJECTS_DIR)/lexical.o: $(ASSEMBLER_DIR)/lexical.c $(ASSEMBLER_DIR)/syntactic.h \
		$(ASSEMBLER_DIR)/clowncommon.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/lexical.o $(ASSEMBLER_DIR)/lexical.c

$(OBJECTS_DIR)/semantic.o: $(ASSEMBLER_DIR)/semantic.c $(ASSEMBLER_DIR)/semantic.h \
		$(ASSEMBLER_DIR)/clowncommon.h \
		$(ASSEMBLER_DIR)/syntactic.h \
		$(ASSEMBLER_DIR)/dictionary.h \
		$(ASSEMBLER_DIR)/strcmpci.h \
		$(ASSEMBLER_DIR)/lexical.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/semantic.o $(ASSEMBLER_DIR)/semantic.c

$(OBJECTS_DIR)/strcmpci.o: $(ASSEMBLER_DIR)/strcmpci.c $(ASSEMBLER_DIR)/strcmpci.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/strcmpci.o $(ASSEMBLER_DIR)/strcmpci.c

$(OBJECTS_DIR)/syntactic.o: $(ASSEMBLER_DIR)/syntactic.c $(ASSEMBLER_DIR)/syntactic.h \
		$(ASSEMBLER_DIR)/clowncommon.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/syntactic.o $(ASSEMBLER_DIR)/syntactic.c

$(OBJECTS_DIR)/cpu.o: $(EMULATOR_DIR)/cpu.c $(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/handler.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/ram.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/cpu.o $(EMULATOR_DIR)/cpu.c


$(OBJECTS_DIR)/ram.o: $(EMULATOR_DIR)/ram.c $(EMULATOR_DIR)/ram.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/handler.h 
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/ram.o $(EMULATOR_DIR)/ram.c

$(OBJECTS_DIR)/JSON.o: $(EMULATOR_DIR)/JSON.c $(EMULATOR_DIR)/JSON.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/handler.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/ram.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/JSON.o $(EMULATOR_DIR)/JSON.c

$(OBJECTS_DIR)/handler.o: $(EMULATOR_DIR)/handler.c $(EMULATOR_DIR)/handler.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/ram.h \
		$(EMULATOR_DIR)/cpu.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/handler.o $(EMULATOR_DIR)/handler.c

$(OBJECTS_DIR)/utils.o: $(EMULATOR_DIR)/utils.c $(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/ram.h \
		$(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/handler.h 
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/utils.o $(EMULATOR_DIR)/utils.c

$(OBJECTS_DIR)/main.o: $(SOURCE_DIR)/main.cpp \
		$(SOURCE_DIR)/stray_m68k.h \
		$(EMULATOR_DIR)/emulator.h \
		$(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/handler.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/ram.h \
		$(ASSEMBLER_DIR)/assembler.h \
		$(ASSEMBLER_DIR)/clowncommon.h \
		$(ASSEMBLER_DIR)/semantic.h \
		$(ASSEMBLER_DIR)/syntactic.h
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/main.o -c $(SOURCE_DIR)/main.cpp $(LIBS)

$(OBJECTS_DIR)/header.o: $(WWW_DIR)/header.cpp $(WWW_DIR)/header.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/header.o -c $(WWW_DIR)/header.cpp $(LIBS)

$(OBJECTS_DIR)/footer.o: $(WWW_DIR)/footer.cpp $(WWW_DIR)/footer.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/footer.o -c $(WWW_DIR)/footer.cpp $(LIBS)

$(OBJECTS_DIR)/editor.o: $(WWW_DIR)/editor.cpp $(WWW_DIR)/editor.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/editor.o -c $(WWW_DIR)/editor.cpp $(LIBS)

$(OBJECTS_DIR)/dispatcher.o: $(WWW_DIR)/dispatcher.cpp $(WWW_DIR)/dispatcher.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/dispatcher.o -c $(WWW_DIR)/dispatcher.cpp $(LIBS)

$(OBJECTS_DIR)/memory.o: $(WWW_DIR)/memory.cpp $(WWW_DIR)/memory.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/memory.o -c $(WWW_DIR)/memory.cpp $(LIBS)

$(OBJECTS_DIR)/console.o: $(WWW_DIR)/console.cpp $(WWW_DIR)/console.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/console.o -c $(WWW_DIR)/console.cpp $(LIBS)

$(OBJECTS_DIR)/register.o: $(WWW_DIR)/register.cpp $(WWW_DIR)/register.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJECTS_DIR)/register.o -c $(WWW_DIR)/register.cpp $(LIBS)


deploy: all
	./$(TARGET) --docroot . --http-address $(HOST) --http-port $(PORT) --resources-dir=template/resources
	