#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T09:48:29
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = CPP2InfluxDB
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

QMAKE_CXXFLAGS += --coverage
QMAKE_LFLAGS += --coverage

TEMPLATE = app

INCLUDEPATH += include/ \
               mezorian/DateTimePP/include


SOURCES += main.cpp \
    mezorian/DateTimePP/src/DateTimePP.cpp \
    mezorian/DateTimePP/src/DateTimePPArithmetics.cpp \
    mezorian/DateTimePP/src/DateTimePPCurrentTime.cpp \
    mezorian/DateTimePP/src/DateTimePPDateTimeInfo.cpp \
    mezorian/DateTimePP/src/DateTimePPGeneralMisc.cpp \
    mezorian/DateTimePP/src/DateTimePPOperator.cpp \
    mezorian/DateTimePP/src/DateTimePPUnixTime.cpp \
    open-pete/Log-Writer/src/LogWriter.cpp \
    open-pete/Log-Writer/src/SLevel.cpp \
    src/DataBuffer.cpp \
    src/CPP2InfluxDB.cpp \
    src/HTTPRequest.cpp

HEADERS += \
    include/config.h \
    include/DataBuffer.h \
    include/CPP2InfluxDB.h \
    include/HTTPRequest.h \
    include/catch.hpp \
    mezorian/DateTimePP/include/DateTimePP.h \
    open-pete/Log-Writer/include/LogWriter.h \
    open-pete/Log-Writer/include/SLevel.h

LIBS += -lcurl
