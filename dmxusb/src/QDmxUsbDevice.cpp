#include "QDmxUsbDevice.h"

#ifdef LIBFTDI1
#include "Interfaces/QDmxFTDIInterface.h"
#endif
#ifdef FTD2XX
#include "Interfaces/QDmxFTD2XXInterface.h"
#endif
#ifdef QTSERIAL
#include "Interfaces/QDmxQtSerialInterface.h"
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

#ifdef FTD2XX
    interfaceList << QDmxFTD2XXInterface::interfaces(interfaceList);
#endif

#ifdef LIBFTDI1
    interfaceList << QDmxFTDIInterface::interfaces(interfaceList);
#endif

#ifdef QTSERIAL
    interfaceList << QDmxQtSerialInterface::interfaces(interfaceList);
#endif

    //for each found interface
    foreach (QDmxUsbInterface* iface, interfaceList)
    {
        qDebug() << iface->name() << iface->vendorID() << iface->productID();


    }

    return r;
}

bool QDmxUsbDevice::open(quint32 port, bool input)
{
    //If the port number is not correct
    if((input && (port >= getNbreInputPort())) || (!input && (port >= getNbreOutputPort())))
        return false;

    //If it is already opened, retrun true
    if((input && _openedInput.contains(port)) || (!input && _openedOutput.contains(port)))
        return true;

    //If interface is not already opened
    if(!_iface->isOpen())
    {
        //Try to open the interface
        if(type() ==  QDmxUsbDevice::DMX4ALL)
        {
            if(!_iface->openByPID(QDmxUsbInterface::DMX4ALLPID))
                return false;
        }
        else
        {
            if(!_iface->open())
                return false;
        }

        //configure the port
        if(!_iface->reset() &&
                !_iface->setLineProperties() &&
                !_iface->setFlowControl() &&
                !_iface->setBaudRate() &&
                !_iface->purgeBuffers())
        {
            close(port, input);
            return false;
        }
    }

    if(input)
        _openedInput << port;
    else
        _openedOutput << port;

    return true;
}

bool QDmxUsbDevice::close(quint32 port, bool input)
{
    //If the port number is not correct
    if((input && (port >= getNbreInputPort())) || (!input && (port >= getNbreOutputPort())))
        return false;

    //delete the port number from the list
    if(input && _openedInput.contains(port))
        _openedInput.removeAll(port);
    else if(!input && _openedOutput.contains(port))
        _openedOutput.removeAll(port);
    else
        qDebug() << "port already closed";

    //If no port opened, close the interface
    if(_openedInput.size() == 0 && _openedOutput.size() == 0)
    {
        qDebug() << "All ports closed. Close the interface too";

        if(_iface->isOpen())
            return _iface->close();
        else
            return true;
    }

    return true;
}
