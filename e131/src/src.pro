TEMPLATE = lib
LANGUAGE = C++
TARGET   = QDmxE131

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

HEADERS += \
    QDmxE131Plugin.h \
    QDmxE131Controler.h \
    QDmxE131Packetizer.h

SOURCES += \
    QDmxE131Controler.cpp \
    QDmxE131Packetizer.cpp
