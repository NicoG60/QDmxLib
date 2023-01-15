#ifndef QDMXUSBDEVICE_P_H
#define QDMXUSBDEVICE_P_H

#include "qdmxdevice_p.h"
#include "qdmxusbdevice.h"
#include "qdmxftdibackend_p.h"

class QDmxUsbInterface;
class QDmxUsbDevicePrivate : public QDmxDevicePrivate
{
    Q_DECLARE_PUBLIC(QDmxUsbDevice)

public:
    QDmxUsbDevicePrivate(const QString& name,
                         const QString& serial,
                         const QString& vendor,
                         quint16 vid,
                         quint16 pid,
                         QDmxUsbDevice::Backend backend,
                         QDmxDriver* parent) :
        QDmxDevicePrivate(parent),
        _name(name),
        _officialName(name),
        _serial(serial),
        _vendor(vendor),
        _vendorId(vid),
        _productId(pid)
    {
        switch (backend) {
        case QDmxUsbDevice::LibFTDI:
            _backend = new QDmxFTDIBackend(this);
            break;
        case QDmxUsbDevice::FTD2XX:

            break;
        case QDmxUsbDevice::Serial:

            break;
        default:
            break;
        }
    }

    void init();

    QString _name;
    QString _officialName;
    QDmxUsbDevice::Type _type;
    QString _serial;
    QString _vendor;
    quint16 _vendorId;
    quint16 _productId;
    QDmxUsbBackend* _backend;

    QDmxUsbInterface* _iface = nullptr;
};

#endif // QDMXUSBDEVICE_P_H
