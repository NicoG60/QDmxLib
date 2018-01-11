#include "QDmxUsbInterface.h"

QDmxUsbInterface::QDmxUsbInterface(const QString &serial, const QString &name, const QString &vendor, quint16 VID, quint16 PID, quint32 id) :
    _serial(serial),
    _name(name),
    _vendor(vendor),
    _vendorID(VID),
    _productID(PID),
    _id(id)
{

}

bool QDmxUsbInterface::validInterface(quint16 vendor, quint16 product)
{
    if (vendor != QDmxUsbInterface::FTDIVID &&
        vendor != QDmxUsbInterface::ATMELVID &&
        vendor != QDmxUsbInterface::MICROCHIPVID)
            return false;

    if (product != QDmxUsbInterface::FTDIPID &&
        product != QDmxUsbInterface::DMX4ALLPID &&
        product != QDmxUsbInterface::NANODMXPID &&
        product != QDmxUsbInterface::EUROLITEPID &&
        product != QDmxUsbInterface::ELECTROTASPID)
            return false;

    return true;
}

bool QDmxUsbInterface::checkInfo(const QString &serial, const QString &name, const QString &vendor)
{
    if (_serial == serial &&
        _name == name &&
        _vendor == vendor)
        return true;
    return false;
}
