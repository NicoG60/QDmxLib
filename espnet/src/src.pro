TEMPLATE = lib
LANGUAGE = C++
TARGET   = QDmxESPNet

QT      += network
QT      -= gui

CONFIG      += plugin

win32:QMAKE_LFLAGS += -shared

CONFIG(debug, debug|release){
    target.path = /Users/nicolas/Programmation/plugin
    INSTALLS   += target
}

include(../../interface/interface.pri)

CONFIG += network_interface

HEADERS += QDmxESPNetPlugin.h \
    QDmxESPNetControler.h \
    QDmxESPNetPacketizer.h

SOURCES += \
    QDmxESPNetControler.cpp \
    QDmxESPNetPacketizer.cpp
