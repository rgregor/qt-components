INCLUDEPATH += $$PWD
#DEFINES += QS_LOG_LINE_NUMBERS
#DEFINES += QS_LOG_DISABLE
SOURCES += $$PWD/QsLogDest.cpp \
    $$PWD/QsLog.cpp \
    $$PWD/QsDebugOutput.cpp

HEADERS += $$PWD/QSLogDest.h \
    $$PWD/QsLog.h \
    $$PWD/QsDebugOutput.h \
    $$PWD/QsLogLevel.h \
    $$PWD/QsLogDisableForThisFile.h
