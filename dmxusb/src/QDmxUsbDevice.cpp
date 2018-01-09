#include "QDmxUsbDevice.h"

#ifdef LIBFTDI1
#include "Interfaces/QDmxFTDIInterface.h"
#endif
#ifdef FTD2XX
#include "Interfaces/QDmxFTD2XXInterface.h"
#endif

QDmxUsbDevice::QDmxUsbDevice(QDmxUsbInterface* iface, QObject *parent) :
    QThread(parent),
    _iface(iface)
{

}

QDmxUsbDevice::~QDmxUsbDevice()
{

}

QMap<quint32, QDmxUsbDevice *> QDmxUsbDevice::devices()
{
    QMap<quint32, QDmxUsbDevice*> r;

    QList<QDmxUsbInterface*> interfaceList;
#ifdef LIBFTDI1
    interfaceList << QDmxFTDIInterface::interfaces();
#endif

#ifdef FTD2XX
    interfaceList << QDmxFTD2XXInterface::interfaces();
#endif

    foreach (QDmxUsbInterface* iface, interfaceList) {
        qDebug() << iface->name() << iface->vendorID() << iface->productID();
    }

    return r;
}
