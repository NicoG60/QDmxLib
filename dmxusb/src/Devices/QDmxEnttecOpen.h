#ifndef QDMXENTTECOPEN_H
#define QDMXENTTECOPEN_H

#include "../QDmxUsbDevice.h"

class QDmxEnttecOpen : public QDmxUsbDevice
{
    Q_OBJECT

public:
    QDmxEnttecOpen(QDmxUsbInterface* iface, QObject* parent = 0);
};

#endif // QDMXENTTECOPEN_H
