TEMPLATE = lib
LANGUAGE = C++
TARGET   = QDmxE131

QT      += network
QT      -= gui

CONFIG      += plugin

win32:QMAKE_LFLAGS += -shared

CONFIG(debug, debug|release){
    unix: target.path = /Users/nicolas/Programmation/plugin
    win32:  target.path = E:/Prog/plugin
    INSTALLS   += target
}
CONFIG += network_interface

include(../../interface/interface.pri)

HEADERS += \
    QDmxE131Plugin.h \
    QDmxE131Controler.h \
    QDmxE131Packetizer.h

SOURCES += \
    QDmxE131Controler.cpp \
    QDmxE131Packetizer.cpp
