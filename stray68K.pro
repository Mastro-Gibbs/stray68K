TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ARCH.c \
        assembler/assembler.c \
        assembler/dictionary.c \
        assembler/lexical.c \
        assembler/semantic.c \
        assembler/strcmpci.c \
        assembler/syntactic.c \
        cpu.c \
        loader.c \
        main.c \
        memory.c \
        opcode.c \
        opcode_handlers.c \
        utils.c

HEADERS += \
    ARCH.h \
    assembler/assembler.h \
    assembler/clowncommon.h \
    assembler/dictionary.h \
    assembler/lexical.h \
    assembler/lexical.l \
    assembler/semantic.h \
    assembler/strcmpci.h \
    assembler/syntactic.h \
    assembler/syntactic.y \
    cpu.h \
    enums.h \
    loader.h \
    memory.h \
    motorolatypes.h \
    opcode.h \
    opcode_handlers.h \
    strayemu.h \
    utils.h

DISTFILES += \
    assembler/CMakeLists.txt \
    assembler/LICENCE.txt \
    assembler/Makefile
