QT -= gui
TARGET = concurrent_log
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
DEFINES += QS_LOG_LINE_NUMBERS
INCLUDEPATH += ../../
SOURCES += ../../QsLogDest.cpp \
    ../../QsLog.cpp \
    ../../QsDebugOutput.cpp \
    concurrent_log.cpp
HEADERS += ../../QSLogDest.h \
    ../../QsLog.h \
    ../../QsDebugOutput.h
