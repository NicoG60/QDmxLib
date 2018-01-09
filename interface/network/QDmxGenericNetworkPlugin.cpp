#include "QDmxGenericNetworkPlugin.h"

QDmxGenericNetworkPlugin::QDmxGenericNetworkPlugin(QObject *parent) :
    QDmxIO(parent)
{
}

QDmxGenericNetworkPlugin::~QDmxGenericNetworkPlugin()
{ 
    foreach (QDmxGenericNetworkControler_ptr ctrl, _controlerList)
        ctrl.clear();
}

void QDmxGenericNetworkPlugin::init()
{
    rescanDevices();
}

//===== DEVICE

void QDmxGenericNetworkPlugin::rescanDevices()
{
    QMap<quint32, QDmxGenericNetworkControler_ptr> toDelete = _controlerList;
    _controlerList.clear();

    foreach(QNetworkInterface iface, QNetworkInterface::allInterfaces())
    {
        foreach(QNetworkAddressEntry entry, iface.addressEntries())
        {
            //for each ip address of this computer, if it is a valid address for that protocol
            if(entry.ip().protocol() != QAbstractSocket::IPv6Protocol && !entry.ip().isLoopback())
            {
                quint32 id = entry.ip().toIPv4Address();

                //If the controler already exists
                if(toDelete.contains(id))
                {
                    //Re-insert into the controler list and remove from the list to delete
                    _controlerList.insert(id, toDelete.value(id));
                    toDelete.remove(id);
                }
                else
                {
                    QDmxGenericNetworkControler_ptr tmp;
                    tmp.reset(getNewControler(iface, entry));
                    connect(tmp.data(), &QDmxGenericNetworkControler::hasDmx, this, &QDmxGenericNetworkPlugin::dmxRecieve);
                    _controlerList.insert(id, tmp);
                }
            }
        }
    }

    //At the end, we normally have the existing controller in the controlerList end the disapeared in the toDeleteList
    //So we can delete those ones
    QMapIterator<quint32, QDmxGenericNetworkControler_ptr> it(toDelete);
    while(it.hasNext())
    {
        it.next();
        _openedInput.remove(it.key());
        _openedOutput.remove(it.key());
    }

    toDelete.clear();
}

QMap<quint32, QString> QDmxGenericNetworkPlugin::getDevices() const
{
    QMap<quint32, QString> r;
    QMapIterator<quint32, QDmxGenericNetworkControler_ptr> it(_controlerList);

    while(it.hasNext())
    {
        it.next();
        r.insert(it.key(), it.value()->getAddrString());
    }

    return r;
}

//===== INPUTS
bool QDmxGenericNetworkPlugin::openInput(quint32 device, quint32 port)
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

    if(!_controlerList.value(device)->listenToUniverse(port))
    {
        _lastError = _controlerList.value(device)->errorString();
        return false;
    }

    _openedInput.insert(device, port);

    return true;
}

bool QDmxGenericNetworkPlugin::closeInput(quint32 device, quint32 port)
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

    if(!_controlerList.value(device)->ignoreListenedUniverse(port))
    {
        _lastError = _controlerList.value(device)->errorString();
        return false;
    }

    _openedInput.remove(device, port);

    return true;
}

void QDmxGenericNetworkPlugin::dmxRecieve(quint32 universe, const QByteArray& data)
{
    if(sender())
    {
        QDmxGenericNetworkControler* ptr = qobject_cast<QDmxGenericNetworkControler*>(sender());
        quint32 device = 0;
        foreach (QDmxGenericNetworkControler_ptr ctrl, _controlerList) {
            if(ctrl == ptr)
                device = _controlerList.key(ctrl);
        }

        if(device > 0 && inputIsOpened(device, universe))
            emit dmxInput(device, universe, data);
        else
            _lastError = "wrong sender";
    }
    else
        _lastError = "wrong call of the function";
}

//===== OUTPUTS
bool QDmxGenericNetworkPlugin::openOutput(quint32 device, quint32 port)
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

    if(!_controlerList.value(device)->writeToUniverse(port))
    {
        _lastError = _controlerList.value(device)->errorString();
        return false;
    }

    _openedOutput.insert(device, port);

    return true;
}

bool QDmxGenericNetworkPlugin::closeOutput(quint32 device, quint32 port)
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

    if(!outputIsOpened(device, port))
    {
        _lastError = "already closed";
        return false;
    }

    if(!_controlerList.value(device)->ignoreWrittenUniverse(port))
    {
        _lastError = _controlerList.value(device)->errorString();
        return false;
    }

    _openedOutput.remove(device, port);

    return true;
}

void QDmxGenericNetworkPlugin::writeDmx(quint32 device, quint32 port, QByteArray data)
{
    if(deviceExists(device))
        if(outputExists(device, port))
            if(outputIsOpened(device, port))
                _controlerList.value(device)->write(port, data);
}
