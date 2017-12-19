#include "QDmxArtnetPlugin.h"

QDmxArtnetPlugin::QDmxArtnetPlugin(QObject *parent) :
    QDmxIO(parent),
    _worker(nullptr)
{
}

QDmxArtnetPlugin::~QDmxArtnetPlugin()
{
    if(_worker)
    {
        _worker->quit();
        _worker->wait();
        _worker->deleteLater();
    }

    qDeleteAll(_controlerList);
}

void QDmxArtnetPlugin::init()
{

    if(!_worker)
    {
        _worker = new QThread;
        _worker->start();
    }

    foreach(QNetworkInterface iface, QNetworkInterface::allInterfaces())
    {
        foreach(QNetworkAddressEntry entry, iface.addressEntries())
        {
            bool exists = false;

            for(int i = 0; _controlerList.length(); i++)
                exists |= _controlerList.at(i)->isAddress(entry);

            if(!exists)
            {
                QDmxArtnetControler* tmp = new QDmxArtnetControler(iface, entry);
                tmp->moveToThread(_worker);
                connect(tmp, &QDmxArtnetControler::hasDmx, this, &QDmxArtnetPlugin::dmxRecieve);
                tmp->init();
                _controlerList.append(tmp);
            }
        }
    }
}

//===== DEVICE
QStringList QDmxArtnetPlugin::getDevices()
{
    QStringList r;

    for(int i = 0; i < _controlerList.length(); i++)
        r << _controlerList.at(i)->getAddrString();

    return r;
}

//===== INPUTS
int QDmxArtnetPlugin::getInputCount(QString device)
{
    for(int i = 0; i < _controlerList.length(); i++)
        if(_controlerList.at(i)->getAddrString() == device)
            return getInputCount(i);
    return 0;
}

int QDmxArtnetPlugin::getInputCount(int device)
{
    if(device < _controlerList.length())
        return _controlerList.at(device)->getNbreInputPort();
    return 0;
}

bool QDmxArtnetPlugin::openInput(QString device, int port)
{
    for(int i = 0; i < _controlerList.length(); i++)
        if(_controlerList.at(i)->getAddrString() == device)
            return openInput(i, port);

    _lastError = "wrong device name";
    return false;
}

bool QDmxArtnetPlugin::openInput(int device, int port)
{
    if(device >= _controlerList.length() || device < 0)
    {
        _lastError = "wrong device id";
        return false;
    }

    if(port > getInputCount(device) || port < 0)
    {
        _lastError = "wrong port id";
        return false;
    }

    if(inputIsOpened(device, port))
    {
        _lastError = "already opened";
        return false;
    }

    if(!_controlerList.at(device)->listenToUniverse(port))
    {
        _lastError = _controlerList.at(device)->errorString();
        return false;
    }

    _openedInput.insert(device, port);

    return true;
}

bool QDmxArtnetPlugin::closeInput(QString device, int port)
{
    for(int i = 0; i < _controlerList.length(); i++)
        if(_controlerList.at(i)->getAddrString() == device)
            return closeInput(i, port);

    _lastError = "wrong device name";
    return false;
}

bool QDmxArtnetPlugin::closeInput(int device, int port)
{
    if(device >= _controlerList.length() || device < 0)
    {
        _lastError = "wrong device id";
        return false;
    }

    if(port > getInputCount(device) || port < 0)
    {
        _lastError = "wrong port id";
        return false;
    }

    if(!inputIsOpened(device, port))
    {
        _lastError = "already closed";
        return false;
    }

    if(!_controlerList.at(device)->ignoreListenedUniverse(port))
    {
        _lastError = _controlerList.at(device)->errorString();
        return false;
    }

    _openedInput.remove(device, port);

    return true;
}

void QDmxArtnetPlugin::dmxRecieve(int universe, QByteArray data)
{
    if(sender())
    {
        int device = _controlerList.indexOf(qobject_cast<QDmxArtnetControler*>(sender()));

        if(device >= 0)
            emit dmxInput(device, universe, data);
        else
            _lastError = "wrong sender";
    }
    else
        _lastError = "wrong call of the function";
}

//===== OUTPUTS
int QDmxArtnetPlugin::getOutputCount(QString device)
{
    for(int i = 0; i < _controlerList.length(); i++)
        if(_controlerList.at(i)->getAddrString() == device)
            return getOutputCount(i);
    return 0;
}

int QDmxArtnetPlugin::getOutputCount(int device)
{
    if(device < _controlerList.length())
        return _controlerList.at(device)->getNbreOutputPort();
    return 0;
}

bool QDmxArtnetPlugin::openOutput(QString device, int port)
{
    for(int i = 0; i < _controlerList.length(); i++)
        if(_controlerList.at(i)->getAddrString() == device)
            return openOutput(i, port);

    _lastError = "wrong device name";
    return false;
}

bool QDmxArtnetPlugin::openOutput(int device, int port)
{
    if(device >= _controlerList.length() || device < 0)
    {
        _lastError = "wrong device id";
        return false;
    }

    if(port > getInputCount(device) || port < 0)
    {
        _lastError = "wrong port id";
        return false;
    }

    if(inputIsOpened(device, port))
    {
        _lastError = "already opened";
        return false;
    }

    if(!_controlerList.at(device)->writeToUniverse(port))
    {
        _lastError = _controlerList.at(device)->errorString();
        return false;
    }

    _openedOutput.insert(device, port);

    return true;
}

bool QDmxArtnetPlugin::closeOutput(QString device, int port)
{
    for(int i = 0; i < _controlerList.length(); i++)
        if(_controlerList.at(i)->getAddrString() == device)
            return closeOutput(i, port);

    _lastError = "wrong device name";
    return false;
}

bool QDmxArtnetPlugin::closeOutput(int device, int port)
{
    if(device >= _controlerList.length() || device < 0)
    {
        _lastError = "wrong device id";
        return false;
    }

    if(port > getInputCount(device) || port < 0)
    {
        _lastError = "wrong port id";
        return false;
    }

    if(!inputIsOpened(device, port))
    {
        _lastError = "already closed";
        return false;
    }

    if(!_controlerList.at(device)->ignoreWrittenUniverse(port))
    {
        _lastError = _controlerList.at(device)->errorString();
        return false;
    }

    _openedOutput.remove(device, port);

    return true;
}

void QDmxArtnetPlugin::writeDmx(int device, int port, QByteArray data)
{
    if(device < _controlerList.length())
        if(port < getOutputCount(device))
            QMetaObject::invokeMethod(_controlerList[device], "write", Qt::QueuedConnection, Q_ARG(int, port), Q_ARG(QByteArray, data));
}
