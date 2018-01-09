#include "QDmxFTD2XXInterface.h"

#include <memory>

QDmxFTD2XXInterface::QDmxFTD2XXInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id) :
    QDmxUsbInterface(serial, name, vendor, VID, PID, id)
{
}

QDmxFTD2XXInterface::~QDmxFTD2XXInterface()
{
    if(isOpen())
        close();
}

QList<QDmxUsbInterface*> QDmxFTD2XXInterface::interfaces()
{
    QList<QDmxUsbInterface*> r;

    DWORD nbreDev = 0;
    FT_STATUS status = 0;

    //create device list
    if((status = FT_CreateDeviceInfoList(&nbreDev)) != 0)
    {
        qDebug() << Q_FUNC_INFO << errorString(status);
        return r;
    }

    qDebug() << nbreDev << "devs founds";

    for(uint i = 0; i < nbreDev; i++)
    {
        QString vendor, description, serial;
        quint16 vid, pid;

        if((status = getInterfaceInfo(i, vendor, description, serial, vid, pid)) != 0)
        {
            qDebug() << Q_FUNC_INFO << errorString(status);
            return r;
        }

        qDebug() << "Dev" << i << ":" << vendor << description << serial << vid << pid;

        r << new QDmxFTD2XXInterface(serial, description, vendor, vid, pid);
    }

    return r;
}

bool QDmxFTD2XXInterface::open()
{
    return false;
}

bool QDmxFTD2XXInterface::openByPID(const int FTDIPID)
{
    return false;
}

bool QDmxFTD2XXInterface::close()
{
    return false;
}

bool QDmxFTD2XXInterface::isOpen() const
{
    return false;
}

bool QDmxFTD2XXInterface::reset()
{
    return false;
}

bool QDmxFTD2XXInterface::setLineProperties()
{
    return false;
}

bool QDmxFTD2XXInterface::setBaudRate()
{
    return false;
}

bool QDmxFTD2XXInterface::setFlowControl()
{
    return false;
}

bool QDmxFTD2XXInterface::clearRts()
{
    return false;
}

bool QDmxFTD2XXInterface::purgeBuffers()
{
    return false;
}

bool QDmxFTD2XXInterface::setBreak(bool on)
{
    return false;
}

bool QDmxFTD2XXInterface::write(const QByteArray& data)
{
    return false;
}

QByteArray QDmxFTD2XXInterface::read(int size, uchar* buffer)
{
    return QByteArray();
}

uchar QDmxFTD2XXInterface::readByte(bool* ok)
{
    return 0;
}

QString QDmxFTD2XXInterface::errorString(FT_STATUS status)
{
    switch(status)
    {
    case FT_OK: return "FT_OK";
    case FT_INVALID_HANDLE: return "FT_INVALID_HANDLE";
    case FT_DEVICE_NOT_FOUND: return "FT_DEVICE_NOT_FOUND";
    case FT_DEVICE_NOT_OPENED: return "FT_DEVICE_NOT_OPENED";
    case FT_IO_ERROR: return "FT_IO_ERROR";
    case FT_INSUFFICIENT_RESOURCES: return "FT_INSUFFICIENT_RESOURCES";
    case FT_INVALID_PARAMETER: return "FT_INVALID_PARAMETER";
    case FT_INVALID_BAUD_RATE: return "FT_INVALID_BAUD_RATE";
    case FT_DEVICE_NOT_OPENED_FOR_ERASE: return "FT_DEVICE_NOT_OPENED_FOR_ERASE";
    case FT_DEVICE_NOT_OPENED_FOR_WRITE: return "FT_DEVICE_NOT_OPENED_FOR_WRITE";
    case FT_FAILED_TO_WRITE_DEVICE: return "FT_FAILED_TO_WRITE_DEVICE";
    case FT_EEPROM_READ_FAILED: return "FT_EEPROM_READ_FAILED";
    case FT_EEPROM_WRITE_FAILED: return "FT_EEPROM_WRITE_FAILED";
    case FT_EEPROM_ERASE_FAILED: return "FT_EEPROM_ERASE_FAILED";
    case FT_EEPROM_NOT_PRESENT: return "FT_EEPROM_NOT_PRESENT";
    case FT_EEPROM_NOT_PROGRAMMED: return "FT_EEPROM_NOT_PROGRAMMED";
    case FT_INVALID_ARGS: return "FT_INVALID_ARGS";
    case FT_NOT_SUPPORTED: return "FT_NOT_SUPPORTED";
    case FT_OTHER_ERROR: return "FT_OTHER_ERROR";
    default: return "Unknown error";
    }
}

FT_STATUS QDmxFTD2XXInterface::getInterfaceInfo(DWORD deviceIndex, QString &vendor, QString &description, QString &serial, quint16 &VID, quint16 &PID)
{
    char cVendor[256];
    char cVendorId[256];
    char cDescription[256];
    char cSerial[256];

    FT_HANDLE handle;

    FT_STATUS status = FT_Open(deviceIndex, &handle);
    if (status != FT_OK)
        return status;

    FT_PROGRAM_DATA pData;
    pData.Signature1 = 0;
    pData.Signature2 = 0xFFFFFFFF;
    pData.Version = 0x00000005;
    pData.Manufacturer = cVendor;
    pData.ManufacturerId = cVendorId;
    pData.Description = cDescription;
    pData.SerialNumber = cSerial;
    status = FT_EE_Read(handle, &pData);
    if (status == FT_OK)
    {
        VID = pData.VendorId;
        PID = pData.ProductId;

        if (pData.ProductId == QDmxUsbInterface::DMX4ALLPID)
            vendor = QString("DMX4ALL");
        else
            vendor = QString(cVendor);
        description = QString(cDescription);
        serial = QString(cSerial);
    }

    FT_Close(handle);

    return status;
}
