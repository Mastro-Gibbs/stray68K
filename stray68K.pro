TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/assembler/assembler.c \
    src/assembler/dictionary.c \
    src/assembler/lexical.c \
    src/assembler/semantic.c \
    src/assembler/strcmpci.c \
    src/assembler/syntactic.c \
    src/emulator/cpu.c \
    src/emulator/emulator.c \
    src/emulator/handler.c \
    src/emulator/ram.c \
    src/emulator/utils.c \
    src/emulator/JSON.c \
    src/main.c \

HEADERS += \
    src/emulator/JSON.h \
    src/assembler/assembler.h \
    src/assembler/clowncommon.h \
    src/assembler/dictionary.h \
    src/assembler/lexical.h \
    src/assembler/lexical.l \
    src/assembler/semantic.h \
    src/assembler/strcmpci.h \
    src/assembler/syntactic.h \
    src/assembler/syntactic.y \
    src/emulator/cpu.h \
    src/emulator/emulator.h \
    src/emulator/enums.h \
    src/emulator/handler.h \
    src/emulator/motorolatypes.h \
    src/emulator/ram.h \
    src/stray_m68k.h \
    src/emulator/utils.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

