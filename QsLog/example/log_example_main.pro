#This project links with QsLog dynamically and outputs an executable file.

QT -= gui
TARGET = log_example
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += log_example_main.cpp
INCLUDEPATH += $$PWD/../

LIBS += -L$$PWD/build-QsLogExample \
        -L$$PWD/../build-QsLogShared \
        -llog_example_shared \
        -lQsLog

DESTDIR = $$PWD/build-QsLogExample
