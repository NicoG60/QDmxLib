TEMPLATE = lib
LANGUAGE = C++
TARGET   = QDmxUsb

QT      -= gui

CONFIG      += plugin

win32:QMAKE_LFLAGS += /shared

CONFIG(debug, debug|release){
    unix: target.path = /Users/nicolas/Programmation/plugin
    win32:  target.path = E:/Prog/plugin
    INSTALLS   += target
}

unix: {
    CONFIG += libftdi1-unix
}

win32: {
    #CONFIG += libftdi1-win
    CONFIG += FTD2XX
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

CONFIG(libftdi1-unix) {
    HEADERS += Interfaces/QDmxFTDIInterface.h
    SOURCES += Interfaces/QDmxFTDIInterface.cpp

    LIBS += -L/opt/local/lib -lftdi1
    LIBS += -L/opt/local/lib -lusb-1.0
    INCLUDEPATH += /opt/local/include/libftdi1
    INCLUDEPATH += /opt/local/include/libusb-1.0

    DEFINES += LIBFTDI1
}

CONFIG(libftdi1-win) {
    HEADERS += Interfaces/QDmxFTDIInterface.h
    SOURCES += Interfaces/QDmxFTDIInterface.cpp

    LIBS += -LE:/Prog/libftdi1-1.4/lib -lftdi1
    LIBS += -LE:/Prog/libusb/MinGW32/static -lusb-1.0
    INCLUDEPATH += E:/Prog/libftdi1-1.4/include
    INCLUDEPATH += E:/Prog/libusb/include/libusb-1.0

    DEFINES += LIBFTDI1
}

CONFIG(FTD2XX) {
    HEADERS += Interfaces/QDmxFTD2XXInterface.h
    SOURCES += Interfaces/QDmxFTD2XXInterface.cpp

    LIBS += -LE:/Prog/ftd2xx/amd64 -lftd2xx
    INCLUDEPATH += E:/Prog/ftd2xx

    DEFINES += FTD2XX
}
