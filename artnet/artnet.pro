TEMPLATE = lib
LANGUAGE = C++
TARGET   = artnet

QT      += network

CONFIG      += plugin
INCLUDEPATH += ../src
DEPENDPATH  += ../src

win32:QMAKE_LFLAGS += -shared

target.path = $$INSTALLROOT/$$PLUGINDIR
INSTALLS   += target

HEADERS += ../src/QDmxIO.h \
    QDmxArtnetPlugin.h \
    QDmxArtnetControler.h \
    QDmxArtnetPacketizer.h

SOURCES += ../src/QDmxIO.cpp \
    QDmxArtnetPlugin.cpp \
    QDmxArtnetControler.cpp \
    QDmxArtnetPacketizer.cpp
