TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cpu.cpp

HEADERS += \
    cpu.h \
    opcode.h
