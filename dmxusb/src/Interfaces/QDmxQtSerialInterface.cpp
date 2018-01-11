#include "QDmxQtSerialInterface.h"

QDmxQtSerialInterface::QDmxQtSerialInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id) :
    QDmxUsbInterface(serial, name, vendor, VID, PID, id),
    _port(nullptr)
{
}

QDmxQtSerialInterface::~QDmxQtSerialInterface()
{
    if(isOpen())
        close();
}

QList<QDmxUsbInterface*> QDmxQtSerialInterface::interfaces(QList<QDmxUsbInterface *> found)
{
    QList<QDmxUsbInterface*> r;
    int id = 0;

    foreach (QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        if(!validInterface(port.vendorIdentifier(), port.productIdentifier()))
        {
            id++;
            continue;
        }

        bool exists = false;
        for(int i = 0; i < found.length() && !exists; i++)
            exists |= found[i]->checkInfo(port.serialNumber(), port.description(), port.manufacturer());

        if(!exists)
        {
            QDmxQtSerialInterface* iface = new QDmxQtSerialInterface(port.serialNumber(), port.description(), port.manufacturer(), port.vendorIdentifier(), port.productIdentifier(), id);
            iface->setInfo(port);
            r << iface;
        }

        id++;
    }

    return r;
}

bool QDmxQtSerialInterface::open()
{
    if(isOpen())
        return true;

    _port = new QSerialPort(_portInfo);
    if(!_port)
    {
        qDebug() << Q_FUNC_INFO << "cannot create QSerialPort Object";
        return false;
    }

    if(!_port->open(QIODevice::ReadWrite))
    {
        qDebug() << Q_FUNC_INFO << "can't open the device" << _port->errorString();
        delete _port;
        _port = nullptr;
        return false;
    }

    _port->setReadBufferSize(1026);

    return true;
}

bool QDmxQtSerialInterface::openByPID(const int FTDIPID)
{
    Q_UNUSED(FTDIPID)
    return open();
}

bool QDmxQtSerialInterface::close()
{
    if(!isOpen())
        return true;

    _port->close();
    delete _port;
    _port = nullptr;

    return true;
}

bool QDmxQtSerialInterface::isOpen() const
{
    return _port != nullptr;
}

bool QDmxQtSerialInterface::reset()
{
    if(_port)
        return _port->clear();

    return false;
}

bool QDmxQtSerialInterface::setLineProperties()
{
    if(!_port)
        return false;

    if(!_port->setDataBits(QSerialPort::Data8))
        return false;

    if(!_port->setStopBits(QSerialPort::TwoStop))
        return false;

    if(!_port->setParity(QSerialPort::NoParity))
        return false;

    return true;
}

bool QDmxQtSerialInterface::setBaudRate()
{
    if(_port)
        return _port->setBaudRate(250000);

    return false;
}

bool QDmxQtSerialInterface::setFlowControl()
{
    if(_port)
        return _port->setFlowControl(QSerialPort::NoFlowControl);

    return false;
}

bool QDmxQtSerialInterface::clearRts()
{
    if(_port)
        return _port->setRequestToSend(false);

    return false;
}

bool QDmxQtSerialInterface::purgeBuffers()
{
    return reset();
}

bool QDmxQtSerialInterface::setBreak(bool on)
{
    if(_port)
        return _port->setBreakEnabled(on);

    return false;
}

bool QDmxQtSerialInterface::write(const QByteArray& data)
{
    if(_port)
        return _port->write(data) >= 0;

    return false;
}

QByteArray QDmxQtSerialInterface::read(int size, uchar* buffer)
{
    Q_UNUSED(buffer)

    if(_port)
    {
        if(_port->waitForReadyRead(10))
            return _port->read(size);
    }

    return QByteArray();
}

uchar QDmxQtSerialInterface::readByte(bool* ok)
{
    if(_port)
    {
        if(_port->waitForReadyRead(10))
        {
            QByteArray read = _port->read(1);
            if(read.size() > 0)
            {
                *ok = true;
                return (uchar)read.at(0);
            }
        }
    }

    *ok = false;
    return 0;
}
