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
    mezorian/DateTimePP/test/ArithmeticsTest.cpp \
    mezorian/DateTimePP/test/CurrentTimeTest.cpp \
    mezorian/DateTimePP/test/DateTimeInfoTest.cpp \
    mezorian/DateTimePP/test/DateTimePPTest.cpp \
    mezorian/DateTimePP/test/GeneralMiscTest.cpp \
    mezorian/DateTimePP/test/OperatorTest.cpp \
    mezorian/DateTimePP/test/UnixTimeTest.cpp \
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
    mezorian/DateTimePP/include/DateTimePP.h \
    open-pete/Log-Writer/include/LogWriter.h \
    open-pete/Log-Writer/include/SLevel.h

LIBS += -lcurl
