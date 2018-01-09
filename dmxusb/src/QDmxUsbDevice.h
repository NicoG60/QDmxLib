#ifndef QDMXUSBDEVICE_H
#define QDMXUSBDEVICE_H

#include <QObject>
#include "QDmxUsbInterface.h"

class QDmxUsbDevice : public QThread
{
    Q_OBJECT

public:
    QDmxUsbDevice(QDmxUsbInterface* iface, QObject* parent = 0);
    ~QDmxUsbDevice();

    static QMap<quint32, QDmxUsbDevice *> devices();

private:
    QDmxUsbInterface* _iface;
};

#endif // QDMXUSBDEVICE_H
