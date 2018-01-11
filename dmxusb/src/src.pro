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

macx: {
    CONFIG += QtSerial
    CONFIG += libftdi1-macx
    #CONFIG += FTD2XX-macx
}

win32: {
    CONFIG += QtSerial
    #CONFIG += libftdi1-win
    CONFIG += FTD2XX-win
}

include(../../interface/interface.pri)

HEADERS += \
    QDmxUsbPlugin.h \
    QDmxUsbDevice.h \
    QDmxUsbInterface.h \
    Devices/QDmxEnttecOpen.h

SOURCES += \
    QDmxUsbPlugin.cpp \
    QDmxUsbDevice.cpp \
    QDmxUsbInterface.cpp \
    Devices/QDmxEnttecOpen.cpp

CONFIG(libftdi1-macx) {
    CONFIG += libftdi1

    LIBS += -L$$PWD/../../thirdPartyLib/macx/libftdi1/lib -lftdi1
    LIBS += -L$$PWD/../../thirdPartyLib/macx/libusb-1.0/lib -lusb-1.0
    INCLUDEPATH += $$PWD/../../thirdPartyLib/macx/libftdi1/include
    INCLUDEPATH += $$PWD/../../thirdPartyLib/macx/libusb-1.0/include
}

CONFIG(libftdi1-win) {
    CONFIG += libftdi1

    LIBS += -LE:/Prog/libftdi1-1.4/lib -lftdi1
    LIBS += -LE:/Prog/libusb/MinGW32/static -lusb-1.0
    INCLUDEPATH += E:/Prog/libftdi1-1.4/include
    INCLUDEPATH += E:/Prog/libusb/include/libusb-1.0
}

CONFIG(libftdi1) {
    HEADERS += Interfaces/QDmxFTDIInterface.h
    SOURCES += Interfaces/QDmxFTDIInterface.cpp

    DEFINES += LIBFTDI1
}

CONFIG(FTD2XX-macx) {
    CONFIG += FTD2XX

    LIBS += -L$$PWD/../../thirdPartyLib/macx/libftd2xx/lib -lftd2xx
    INCLUDEPATH += $$PWD/../../thirdPartyLib/macx/libftd2xx/include
}

CONFIG(FTD2XX-win) {
    CONFIG += FTD2XX

    LIBS += -LE:/Prog/ftd2xx/amd64 -lftd2xx
    INCLUDEPATH += E:/Prog/ftd2xx
}

CONFIG(FTD2XX) {
    HEADERS += Interfaces/QDmxFTD2XXInterface.h
    SOURCES += Interfaces/QDmxFTD2XXInterface.cpp

    DEFINES += FTD2XX
}

CONFIG(QtSerial)
{
    QT += serialport
    HEADERS += Interfaces/QDmxQtSerialInterface.h
    SOURCES += Interfaces/QDmxQtSerialInterface.cpp

    DEFINES += QTSERIAL
}
