#include "QDmxIO.h"

QDmxIO::QDmxIO(QObject *parent) :
    QObject(parent)
{

}

void QDmxIO::init()
{

}

QString QDmxIO::name()
{
    return "Dummy";
}

//===== DEVICE
QStringList QDmxIO::getDevices()
{
    return QStringList();
}

bool QDmxIO::deviceExists(int device)
{
    Q_UNUSED(device)
    return false;
}

//===== INPUTS
int QDmxIO::getInputCount(int device)
{
    Q_UNUSED(device)
    return 0;
}

bool QDmxIO::inputExists(int device, int port)
{
    return port > 0 && port < getInputCount(device);
}

bool QDmxIO::openInput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return false;
}

bool QDmxIO::closeInput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return false;
}

bool QDmxIO::inputIsOpened(int device, int port)
{
    return _openedInput.contains(device, port);
}

//===== OUTPUTS
int QDmxIO::getOutputCount(int device)
{
    Q_UNUSED(device)
    return 0;
}

bool QDmxIO::outputExists(int device, int port)
{
    return port > 0 && port < getInputCount(device);
}


bool QDmxIO::openOutput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return false;
}

bool QDmxIO::closeOutput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return false;
}

bool QDmxIO::outputIsOpened(int device, int port)
{
    return _openedOutput.contains(device, port);
}

void QDmxIO::writeDmx(int device, int port, QByteArray data)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    Q_UNUSED(data)
}
