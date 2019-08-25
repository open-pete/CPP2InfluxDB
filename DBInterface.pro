#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T09:48:29
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = DBInterface
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

INCLUDEPATH += include/


SOURCES += main.cpp \
    open-pete/Log-Writer/src/LogWriter.cpp \
    open-pete/Log-Writer/src/SLevel.cpp \
    src/DataBuffer.cpp \
    src/dbinterface.cpp \
    src/HTTPRequest.cpp

HEADERS += \
    include/config.h \
    include/DataBuffer.h \
    include/dbinterface.h \
    include/HTTPRequest.h \
    include/catch.hpp \
    open-pete/Log-Writer/include/LogWriter.h \
    open-pete/Log-Writer/include/SLevel.h

LIBS += -lcurl
