#ifndef QDMXFTDIINTERFACE_H
#define QDMXFTDIINTERFACE_H

#include "../QDmxUsbInterface.h"
#include <ftdi.h>

class QDmxFTDIInterface : public QDmxUsbInterface
{
public:
    QDmxFTDIInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id = 0);
    ~QDmxFTDIInterface();

    static QList<QDmxUsbInterface*> interfaces();

    virtual QDmxUsbInterface::Type type() { return QDmxUsbInterface::libFTDI; }

    virtual QString typeString() { return QString("libFTDI"); }

    virtual bool open();
    virtual bool openByPID(const int FTDIPID);
    virtual bool close();
    virtual bool isOpen() const;
    virtual bool reset();
    virtual bool setLineProperties();
    virtual bool setBaudRate();
    virtual bool setFlowControl();
    virtual bool clearRts();
    virtual bool purgeBuffers();
    virtual bool setBreak(bool on);
    virtual bool write(const QByteArray& data);
    virtual QByteArray read(int size, uchar* buffer = NULL);
    virtual uchar readByte(bool* ok = NULL);

private:
    ftdi_context _ftdi;
};

#endif // QDMXFTDIINTERFACE_H
