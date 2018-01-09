#include "QDmxUsbPlugin.h"

QDmxUsbPlugin::QDmxUsbPlugin(QObject *parent) :
    QDmxIO(parent)
{

}

QDmxUsbPlugin::~QDmxUsbPlugin()
{

}

void QDmxUsbPlugin::init()
{
    rescanDevices();
}

void QDmxUsbPlugin::rescanDevices()
{
    qDeleteAll(_deviceList);
    _deviceList.clear();

    _deviceList = QDmxUsbDevice::devices();
}
