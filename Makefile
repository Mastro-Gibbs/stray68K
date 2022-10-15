#############################################################################
# Makefile for building: stray68K
#############################################################################

####### Compiler, tools and options

CC            = gcc
CFLAGS        = -pipe -g -Wall -Wextra -fPIC
DEL_FILE      = rm -f
MKDIR         = mkdir -p
DEL_DIR       = rmdir

LEX           = flex
YACC          = bison

####### Output directory

OBJECTS_DIR   = objects
BUILD_DIR     = build
ASSEMBLER_DIR = ../stray68K/src/assembler
EMULATOR_DIR  = ../stray68K/src/emulator
SOURCE_DIR    = ../stray68K/src

####### Files

SOURCES       = $(EMULATOR_DIR)/emulator.c \
		$(ASSEMBLER_DIR)/assembler.c \
		$(ASSEMBLER_DIR)/dictionary.c \
		$(ASSEMBLER_DIR)/lexical.c \
		$(ASSEMBLER_DIR)/semantic.c \
		$(ASSEMBLER_DIR)/strcmpci.c \
		$(ASSEMBLER_DIR)/syntactic.c \
		$(EMULATOR_DIR)/cpu.c \
		$(EMULATOR_DIR)/handler.c \
		$(SOURCE_DIR)/main.c \
		$(EMULATOR_DIR)/ram.c \
		$(EMULATOR_DIR)/utils.c 

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
		$(OBJECTS_DIR)/utils.o

TARGET        = $(BUILD_DIR)/stray68K



first: object_dir build_dir all


####### Build rules

$(BUILD_DIR)/stray68K:  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

generators: $(ASSEMBLER_DIR)/lexical.c $(ASSEMBLER_DIR)/lexical.h $(ASSEMBLER_DIR)/syntactic.c $(ASSEMBLER_DIR)/syntactic.h

all: generators $(BUILD_DIR)/stray68K

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)

cleanassembler:
	-$(DEL_FILE) $(ASSEMBLER_DIR)/lexical.c $(ASSEMBLER_DIR)/lexical.h $(ASSEMBLER_DIR)/syntactic.c $(ASSEMBLER_DIR)/syntactic.h

cleanall: clean cleanassembler


####### Create dirs

object_dir:
	@$(MKDIR) objects

build_dir:
	@$(MKDIR) build


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

$(OBJECTS_DIR)/main.o: $(SOURCE_DIR)/main.c $(SOURCE_DIR)/stray_m68k.h \
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
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/main.o $(SOURCE_DIR)/main.c

$(OBJECTS_DIR)/ram.o: $(EMULATOR_DIR)/ram.c $(EMULATOR_DIR)/ram.h \
		$(EMULATOR_DIR)/motorolatypes.h \
		$(EMULATOR_DIR)/utils.h \
		$(EMULATOR_DIR)/enums.h \
		$(EMULATOR_DIR)/cpu.h \
		$(EMULATOR_DIR)/handler.h 
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/ram.o $(EMULATOR_DIR)/ram.c

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

