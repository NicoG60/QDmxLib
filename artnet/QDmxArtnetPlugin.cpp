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

    foreach (QDmxArtnetControler_ptr artnet, _controlerList)
        artnet.clear();
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
            if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                bool exists = false;

                for(int i = 0; i < _controlerList.length(); i++)
                    exists |= _controlerList.at(i)->isAddress(entry);

                if(!exists)
                {
                    QDmxArtnetControler_ptr tmp;
                    tmp.reset(new QDmxArtnetControler(iface, entry));
                    tmp->moveToThread(_worker);
                    connect(tmp.data(), &QDmxArtnetControler::hasDmx, this, &QDmxArtnetPlugin::dmxRecieve);
                    tmp->init();
                    _controlerList.append(tmp);
                }
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

bool QDmxArtnetPlugin::deviceExists(int device)
{
    return device >= 0 && device < _controlerList.length();
}

//===== INPUTS
int QDmxArtnetPlugin::getInputCount(int device)
{
    if(deviceExists(device))
        return _controlerList.at(device)->getNbreInputPort();
    return 0;
}

bool QDmxArtnetPlugin::inputExists(int device, int port)
{
    return port >= 0 && port < getInputCount(device);
}

bool QDmxArtnetPlugin::openInput(int device, int port)
{
    if(!deviceExists(device))
    {
        _lastError = "wrong device id";
        return false;
    }

    if(!inputExists(device, port))
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

bool QDmxArtnetPlugin::closeInput(int device, int port)
{
    if(!deviceExists(device))
    {
        _lastError = "wrong device id";
        return false;
    }

    if(!inputExists(device, port))
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
        QDmxArtnetControler_ptr ptr;
        ptr.reset(qobject_cast<QDmxArtnetControler*>(sender()));
        int device = _controlerList.indexOf(ptr);

        if(device >= 0)
            emit dmxInput(device, universe, data);
        else
            _lastError = "wrong sender";
    }
    else
        _lastError = "wrong call of the function";
}

//===== OUTPUTS
int QDmxArtnetPlugin::getOutputCount(int device)
{
    if(deviceExists(device))
        return _controlerList.at(device)->getNbreOutputPort();
    return 0;
}

bool QDmxArtnetPlugin::outputExists(int device, int port)
{
    return port >= 0 && port < getOutputCount(device);
}

bool QDmxArtnetPlugin::openOutput(int device, int port)
{
    if(!deviceExists(device))
    {
        _lastError = "wrong device id";
        return false;
    }

    if(!outputExists(device, port))
    {
        _lastError = "wrong port id";
        return false;
    }

    if(outputIsOpened(device, port))
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

bool QDmxArtnetPlugin::closeOutput(int device, int port)
{
    if(!deviceExists(device))
    {
        _lastError = "wrong device id";
        return false;
    }

    if(!outputExists(device, port))
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
    if(deviceExists(device))
        if(outputExists(device, port))
            QMetaObject::invokeMethod(_controlerList[device].data(), "write", Qt::QueuedConnection, Q_ARG(int, port), Q_ARG(QByteArray, data));
}
