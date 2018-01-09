HEADERS += $$PWD/QDmxIO.h

network_interface {
    HEADERS += $$PWD/network/QDmxGenericNetworkPlugin.h
    HEADERS += $$PWD/network/QDmxGenericNetworkControler.h

    SOURCES += $$PWD/network/QDmxGenericNetworkPlugin.cpp
    SOURCES += $$PWD/network/QDmxGenericNetworkControler.cpp
}

INCLUDEPATH += $$PWD
