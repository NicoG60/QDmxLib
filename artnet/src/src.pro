TEMPLATE = lib
LANGUAGE = C++
TARGET   = QDmxArtnet

QT      += network
QT      -= gui

CONFIG      += plugin

win32:QMAKE_LFLAGS += -shared

CONFIG(debug, debug|release){
    target.path = /Users/nicolas/Programmation/plugin
    INSTALLS   += target
}

CONFIG += network_interface

include(../../interface/interface.pri)

HEADERS += QDmxArtnetPlugin.h \
    QDmxArtnetControler.h \
    QDmxArtnetPacketizer.h

SOURCES += \
    QDmxArtnetControler.cpp \
    QDmxArtnetPacketizer.cpp
