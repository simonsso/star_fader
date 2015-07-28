#CONFIG += qt debug
CONFIG += qt
TEMPLATE = app
TARGET =

DEPENDPATH  += . src
INCLUDEPATH += . src
LIBS += -lmosquittopp -lmosquitto

target.path = /usr/local/bin/
INSTALLS += target

# Input
SOURCES += main.cpp

SOURCES += MosqConnect.cpp
HEADERS += MosqConnect.h

SOURCES += rpiPWM1.cpp
HEADERS += rpiPWM1.h

SOURCES += iowriter.cpp
HEADERS += iowriter.h

SOURCES += targetvalues.cpp
HEADERS += targetvalues.h
