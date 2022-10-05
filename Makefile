####### Compiler, tools and options

CC         = gcc
CFLAGS     = -pipe -g -Wall -Wextra
DEL_FILE   = rm -f
DEL_DIRS   = rm -rf
OBJDIR     = objs
MKDIR      = mkdir -p
TARGET_DIR = build

####### Files

SOURCES = ARCH.c \
		  cpu.c \
		  main.c \
		  memory.c \
		  opcode.c \
		  opcode_handlers.c \
		  utils.c

OBJECTS = $(OBJDIR)/ARCH.o \
		  $(OBJDIR)/cpu.o \
		  $(OBJDIR)/main.o \
		  $(OBJDIR)/memory.o \
		  $(OBJDIR)/opcode.o \
		  $(OBJDIR)/opcode_handlers.o \
		  $(OBJDIR)/utils.o

TARGET = $(TARGET_DIR)/stray68K

####### Build rules

all: mk_dirs Makefile $(TARGET_DIR)/stray68K

first: all

$(TARGET_DIR)/stray68K:  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJDIR)/ARCH.o: ARCH.c ARCH.h \
		cpu.h \
		opcode_handlers.h \
		motorolatypes.h \
		opcode.h \
		enums.h \
		utils.h \
		memory.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/cpu.o: cpu.c cpu.h \
		opcode_handlers.h \
		motorolatypes.h \
		opcode.h \
		enums.h \
		utils.h \
		memory.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/main.o: main.c sim.h \
		ARCH.h \
		cpu.h \
		opcode_handlers.h \
		motorolatypes.h \
		opcode.h \
		enums.h \
		utils.h \
		memory.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/memory.o: memory.c memory.h \
		motorolatypes.h \
		utils.h \
		enums.h \
		cpu.h \
		opcode_handlers.h \
		opcode.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/opcode.o: opcode.c opcode.h \
		motorolatypes.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/opcode_handlers.o: opcode_handlers.c opcode_handlers.h \
		motorolatypes.h \
		opcode.h \
		enums.h \
		utils.h \
		memory.h \
		cpu.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/utils.o: utils.c utils.h \
		motorolatypes.h \
		enums.h \
		memory.h \
		cpu.h \
		opcode_handlers.h \
		opcode.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)

mk_dirs: create

create:
	@${MKDIR} ${OBJDIR}
	@${MKDIR} ${TARGET_DIR}

.PHONY: mk_dirs