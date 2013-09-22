#This project file links with QsLog dynamically and outputs a shared object.

QT -= gui

TARGET = log_example_shared
TEMPLATE = lib

DEFINES += EXAMPLE_IS_SHARED_LIBRARY
SOURCES += log_example_shared.cpp
HEADERS += log_example_shared.h
INCLUDEPATH += $$PWD/../

LIBS += -L$$PWD/../build-QsLogShared \
        -lQsLog

DESTDIR = $$PWD/build-QsLogExample
