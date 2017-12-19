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

//===== INPUTS
int QDmxIO::getInputCount(QString device)
{
    Q_UNUSED(device)
    return 0;
}

int QDmxIO::getInputCount(int device)
{
    Q_UNUSED(device)
    return 0;
}

bool QDmxIO::openInput(QString device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::openInput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::closeInput(QString device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::closeInput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::inputIsOpened(int device, int port)
{
    return _openedInput.contains(device, port);
}

//===== OUTPUTS
int QDmxIO::getOutputCount(QString device)
{
    Q_UNUSED(device)
    return 0;
}

int QDmxIO::getOutputCount(int device)
{
    Q_UNUSED(device)
    return 0;
}

bool QDmxIO::openOutput(QString device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::openOutput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::closeOutput(QString device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
}

bool QDmxIO::closeOutput(int device, int port)
{
    Q_UNUSED(device)
    Q_UNUSED(port)
    return true;
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
