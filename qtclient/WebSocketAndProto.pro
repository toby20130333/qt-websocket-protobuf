#-------------------------------------------------
#
# Project created by QtCreator 2016-06-13T18:07:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets websockets

TARGET = WebSocketAndProto
TEMPLATE = app
CONFIG += C++11


#system(protoc -I=$$PWD --cpp_out=$$PWD $$PWD/*.proto)

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lprotobuf

SOURCES += main.cpp\
        widget.cpp \
    echoclient.cpp

HEADERS  += widget.h \
    echoclient.h \
    BDDataFormat.h

FORMS    += widget.ui
SOURCES += \
    *.pb.cc
HEADERS += \
    *.pb.h
