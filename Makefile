#############################################################################
# Makefile for building: stray68K
#############################################################################

MAKEFILE      = Makefile

EQ            = =

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
ASSRMBLER_DIR = ../stray68K/assembler

####### Files

SOURCES       = ../stray68K/ARCH.c \
		../stray68K/assembler/assembler.c \
		../stray68K/assembler/dictionary.c \
		../stray68K/assembler/lexical.c \
		../stray68K/assembler/semantic.c \
		../stray68K/assembler/strcmpci.c \
		../stray68K/assembler/syntactic.c \
		../stray68K/cpu.c \
		../stray68K/loader.c \
		../stray68K/main.c \
		../stray68K/memory.c \
		../stray68K/opcode.c \
		../stray68K/opcode_handlers.c \
		../stray68K/utils.c 

OBJECTS       = $(OBJECTS_DIR)/ARCH.o \
		$(OBJECTS_DIR)/assembler.o \
		$(OBJECTS_DIR)/dictionary.o \
		$(OBJECTS_DIR)/lexical.o \
		$(OBJECTS_DIR)/semantic.o \
		$(OBJECTS_DIR)/strcmpci.o \
		$(OBJECTS_DIR)/syntactic.o \
		$(OBJECTS_DIR)/cpu.o \
		$(OBJECTS_DIR)/loader.o \
		$(OBJECTS_DIR)/main.o \
		$(OBJECTS_DIR)/memory.o \
		$(OBJECTS_DIR)/opcode.o \
		$(OBJECTS_DIR)/opcode_handlers.o \
		$(OBJECTS_DIR)/utils.o

TARGET        = $(BUILD_DIR)/stray68K



first: object_dir build_dir all


####### Build rules

$(BUILD_DIR)/stray68K:  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

generators: $(ASSRMBLER_DIR)/lexical.c $(ASSRMBLER_DIR)/lexical.h $(ASSRMBLER_DIR)/syntactic.c $(ASSRMBLER_DIR)/syntactic.h

all: generators $(BUILD_DIR)/stray68K

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)

cleanassembler:
	-$(DEL_FILE) $(ASSRMBLER_DIR)/lexical.c $(ASSRMBLER_DIR)/lexical.h $(ASSRMBLER_DIR)/syntactic.c $(ASSRMBLER_DIR)/syntactic.h

cleanall: clean cleanassembler
	-$(DEL_DIR)  $(OBJECTS_DIR)
	-$(DEL_DIR)  $(BUILD_DIR)


####### Create dirs

object_dir:
	@$(MKDIR) objects

build_dir:
	@$(MKDIR) build


####### Compile


$(ASSRMBLER_DIR)/lexical.c $(ASSRMBLER_DIR)/lexical.h: $(ASSRMBLER_DIR)/lexical.l $(ASSRMBLER_DIR)/syntactic.h
	$(LEX) --outfile=$(ASSRMBLER_DIR)/lexical.c --header-file=$(ASSRMBLER_DIR)/lexical.h $<

$(ASSRMBLER_DIR)/syntactic.c $(ASSRMBLER_DIR)/syntactic.h: $(ASSRMBLER_DIR)/syntactic.y
	$(YACC) --output=$(ASSRMBLER_DIR)/syntactic.c --header=$(ASSRMBLER_DIR)/syntactic.h --debug $<


$(OBJECTS_DIR)/ARCH.o: ../stray68K/ARCH.c ../stray68K/ARCH.h \
		../stray68K/cpu.h \
		../stray68K/opcode_handlers.h \
		../stray68K/motorolatypes.h \
		../stray68K/opcode.h \
		../stray68K/enums.h \
		../stray68K/utils.h \
		../stray68K/memory.h \
		../stray68K/loader.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/ARCH.o ../stray68K/ARCH.c

$(OBJECTS_DIR)/assembler.o: ../stray68K/assembler/assembler.c ../stray68K/assembler/assembler.h \
		../stray68K/assembler/clowncommon.h \
		../stray68K/assembler/semantic.h \
		../stray68K/assembler/syntactic.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/assembler.o ../stray68K/assembler/assembler.c

$(OBJECTS_DIR)/dictionary.o: ../stray68K/assembler/dictionary.c ../stray68K/assembler/dictionary.h \
		../stray68K/assembler/clowncommon.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/dictionary.o ../stray68K/assembler/dictionary.c

$(OBJECTS_DIR)/lexical.o: ../stray68K/assembler/lexical.c ../stray68K/assembler/syntactic.h \
		../stray68K/assembler/clowncommon.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/lexical.o ../stray68K/assembler/lexical.c

$(OBJECTS_DIR)/semantic.o: ../stray68K/assembler/semantic.c ../stray68K/assembler/semantic.h \
		../stray68K/assembler/clowncommon.h \
		../stray68K/assembler/syntactic.h \
		../stray68K/assembler/dictionary.h \
		../stray68K/assembler/strcmpci.h \
		../stray68K/assembler/lexical.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/semantic.o ../stray68K/assembler/semantic.c

$(OBJECTS_DIR)/strcmpci.o: ../stray68K/assembler/strcmpci.c ../stray68K/assembler/strcmpci.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/strcmpci.o ../stray68K/assembler/strcmpci.c

$(OBJECTS_DIR)/syntactic.o: ../stray68K/assembler/syntactic.c ../stray68K/assembler/syntactic.h \
		../stray68K/assembler/clowncommon.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/syntactic.o ../stray68K/assembler/syntactic.c

$(OBJECTS_DIR)/cpu.o: ../stray68K/cpu.c ../stray68K/cpu.h \
		../stray68K/opcode_handlers.h \
		../stray68K/motorolatypes.h \
		../stray68K/opcode.h \
		../stray68K/enums.h \
		../stray68K/utils.h \
		../stray68K/memory.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/cpu.o ../stray68K/cpu.c

$(OBJECTS_DIR)/loader.o: ../stray68K/loader.c ../stray68K/loader.h \
		../stray68K/motorolatypes.h \
		../stray68K/utils.h \
		../stray68K/enums.h \
		../stray68K/memory.h \
		../stray68K/cpu.h \
		../stray68K/opcode_handlers.h \
		../stray68K/opcode.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/loader.o ../stray68K/loader.c

$(OBJECTS_DIR)/main.o: ../stray68K/main.c ../stray68K/strayemu.h \
		../stray68K/ARCH.h \
		../stray68K/cpu.h \
		../stray68K/opcode_handlers.h \
		../stray68K/motorolatypes.h \
		../stray68K/opcode.h \
		../stray68K/enums.h \
		../stray68K/utils.h \
		../stray68K/memory.h \
		../stray68K/loader.h \
		../stray68K/assembler/assembler.h \
		../stray68K/assembler/clowncommon.h \
		../stray68K/assembler/semantic.h \
		../stray68K/assembler/syntactic.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/main.o ../stray68K/main.c

$(OBJECTS_DIR)/memory.o: ../stray68K/memory.c ../stray68K/memory.h \
		../stray68K/motorolatypes.h \
		../stray68K/utils.h \
		../stray68K/enums.h \
		../stray68K/cpu.h \
		../stray68K/opcode_handlers.h \
		../stray68K/opcode.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/memory.o ../stray68K/memory.c

$(OBJECTS_DIR)/opcode.o: ../stray68K/opcode.c ../stray68K/opcode.h \
		../stray68K/motorolatypes.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/opcode.o ../stray68K/opcode.c

$(OBJECTS_DIR)/opcode_handlers.o: ../stray68K/opcode_handlers.c ../stray68K/opcode_handlers.h \
		../stray68K/motorolatypes.h \
		../stray68K/opcode.h \
		../stray68K/enums.h \
		../stray68K/utils.h \
		../stray68K/memory.h \
		../stray68K/cpu.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/opcode_handlers.o ../stray68K/opcode_handlers.c

$(OBJECTS_DIR)/utils.o: ../stray68K/utils.c ../stray68K/utils.h \
		../stray68K/motorolatypes.h \
		../stray68K/enums.h \
		../stray68K/memory.h \
		../stray68K/cpu.h \
		../stray68K/opcode_handlers.h \
		../stray68K/opcode.h
	$(CC) -c $(CFLAGS) -o $(OBJECTS_DIR)/utils.o ../stray68K/utils.c

