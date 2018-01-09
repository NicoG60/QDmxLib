#include "QDmxGenericNetworkControler.h"

QDmxGenericNetworkControler::QDmxGenericNetworkControler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent) :
    QObject(parent),
    _interface(interface),
    _entry(entry),
    _address(entry.ip())
{
    if (_address == QHostAddress::LocalHost)
    {
        _broadcast = QHostAddress::LocalHost;
        _mac = "11:22:33:44:55:66";
    }
    else
    {
        _broadcast = _entry.broadcast();
        _mac = interface.hardwareAddress();
    }
}