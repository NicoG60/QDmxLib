TEMPLATE = lib
LANGUAGE = C++
TARGET   = QDmxUsb

QT      -= gui

CONFIG      += plugin

win32:QMAKE_LFLAGS += -shared

CONFIG(debug, debug|release){
    target.path = /Users/nicolas/Programmation/plugin
    INSTALLS   += target
}

unix: {
    CONFIG += libftdi1
}

win32: {
    CONFIG += FTD2xx
}

include(../../interface/interface.pri)

HEADERS += \
    QDmxUsbPlugin.h \
    QDmxUsbDevice.h \
    QDmxUsbInterface.h

SOURCES += \
    QDmxUsbPlugin.cpp \
    QDmxUsbDevice.cpp \
    QDmxUsbInterface.cpp

libftdi1 {
    HEADERS += Interfaces/QDmxFTDIInterface.h
    SOURCES += Interfaces/QDmxFTDIInterface.cpp

    LIBS += -L/opt/local/lib -lftdi1
    LIBS += -L/opt/local/lib -lusb-1.0
    INCLUDEPATH += /opt/local/include/libftdi1
    INCLUDEPATH += /opt/local/include/libusb-1.0

    DEFINES += LIBFTDI1
}
