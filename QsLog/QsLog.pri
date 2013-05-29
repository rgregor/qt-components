INCLUDEPATH += $$PWD
#DEFINES += QS_LOG_LINE_NUMBERS
#DEFINES += QS_LOG_DISABLE
SOURCES += $$PWD/QsLogDest.cpp \
    $$PWD/QsLog.cpp \
    $$PWD/QsLogDestConsole.cpp \
    $$PWD/QsLogDestFile.cpp

HEADERS += $$PWD/QSLogDest.h \
    $$PWD/QsLog.h \
    $$PWD/QsLogDestConsole.h \
    $$PWD/QsLogLevel.h \
    $$PWD/QsLogDestFile.h
    $$PWD/QsLogDisableForThisFile.h
