#ifndef QDMXQTSERIALINTERFACE_H
#define QDMXQTSERIALINTERFACE_H

#include "../QDmxUsbInterface.h"
#include <QtSerialPort>

class QDmxQtSerialInterface : public QDmxUsbInterface
{
public:
    QDmxQtSerialInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id = 0);
    ~QDmxQtSerialInterface();

    static QList<QDmxUsbInterface*> interfaces(QList<QDmxUsbInterface *> found);

    virtual QDmxUsbInterface::Type type() { return QDmxUsbInterface::QtSerial; }

    virtual QString typeString() { return QString("QtSerial"); }

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
    void setInfo(QSerialPortInfo info) { _portInfo = info; }
    QSerialPortInfo _portInfo;
    QSerialPort* _port;
};

#endif // QDMXQTSERIALINTERFACE_H
