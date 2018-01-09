#include "QDmxUsbDevice.h"

#ifdef LIBFTDI1
#include "Interfaces/QDmxFTDIInterface.h"
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

    foreach (QDmxUsbInterface* iface, interfaceList) {
        qDebug() << iface->name() << iface->vendorID() << iface->productID();
    }

    return r;
}
