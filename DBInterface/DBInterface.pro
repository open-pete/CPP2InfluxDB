#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T09:48:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = DBInterface
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    src/DataBuffer.cpp \
    src/dbinterface.cpp \
    src/logwriter.cpp \
    src/slevel.cpp \
    src/HTTPRequest.cpp

HEADERS += \
    include/config.h \
    include/DataBuffer.h \
    include/dbinterface.h \
    include/logwriter.h \
    include/slevel.h \
    include/HTTPRequest.h
