#include "QDmxFTD2XXInterface.h"

QDmxFTD2XXInterface::QDmxFTD2XXInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id) :
    QDmxUsbInterface(serial, name, vendor, VID, PID, id),
    _status(FT_OK),
    _handle(0)
{
}

QDmxFTD2XXInterface::~QDmxFTD2XXInterface()
{
    if(isOpen())
        close();
}

QList<QDmxUsbInterface*> QDmxFTD2XXInterface::interfaces(QList<QDmxUsbInterface *> found)
{
    QList<QDmxUsbInterface*> r;

    DWORD nbreDev = 0;
    FT_STATUS status = 0;

    //create device list
    if((status = FT_CreateDeviceInfoList(&nbreDev)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(status);
        return r;
    }

    qDebug() << nbreDev << "devs founds";

    //browse device list
    for(uint i = 0; i < nbreDev; i++)
    {
        QString vendor, description, serial;
        quint16 vid, pid;

        //If it can get info (so if it can work with this app, not belong to another)
        if((status = getInterfaceInfo(i, vendor, description, serial, vid, pid)) != FT_OK)
        {
            qDebug() << Q_FUNC_INFO << errorString(status);
            continue;
        }

        qDebug() << "Dev" << i << ":" << vendor << description << serial << vid << pid;

        //If it is a valid interface and it is not already found, then add it.
        if(validInterface(vid, pid))
        {
            bool exists = false;
            for(int i = 0; i < found.length() && !exists; i++)
                exists |= found[i]->checkInfo(serial, description, vendor);

            if(!exists)
                r << new QDmxFTD2XXInterface(serial, description, vendor, vid, pid, i);
        }
    }

    return r;
}

bool QDmxFTD2XXInterface::open()
{
    if(isOpen())
        return true;

    if((_status = FT_Open(id(), &_handle)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::openByPID(const int FTDIPID)
{
    Q_UNUSED(FTDIPID)
    return open();
}

bool QDmxFTD2XXInterface::close()
{
    if(!isOpen())
        return true;

    if((_status = FT_Close(_handle)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    _handle = 0;

    return true;
}

bool QDmxFTD2XXInterface::isOpen() const
{
    return _handle != 0;
}

bool QDmxFTD2XXInterface::reset()
{
    if((_status = FT_ResetDevice(_handle)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::setLineProperties()
{
    if((_status = FT_SetDataCharacteristics(_handle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_NONE)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::setBaudRate()
{
    if((_status = FT_SetBaudRate(_handle, 250000)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::setFlowControl()
{
    if((_status = FT_SetFlowControl(_handle, FT_FLOW_NONE, 0, 0)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::clearRts()
{
    if((_status = FT_ClrRts(_handle)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::purgeBuffers()
{
    if((_status = FT_Purge(_handle, FT_PURGE_RX | FT_PURGE_TX)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::setBreak(bool on)
{
    if(on)  _status = FT_SetBreakOn(_handle);
    else    _status = FT_SetBreakOff(_handle);

    if(_status != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

bool QDmxFTD2XXInterface::write(const QByteArray& data)
{
    DWORD bytesWritten;

    if((_status = FT_Write(_handle, (LPVOID)data.data(), data.size(), &bytesWritten)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return false;
    }

    return true;
}

QByteArray QDmxFTD2XXInterface::read(int size, uchar* buffer)
{
    /**
     * TODO = FT_Read does not returned until the number of byte passed has been read. Have to check FT_GetStatus to know how many bytes we have to read;
     */
    QByteArray r;
    uchar* mBuffer;
    DWORD bytesRead;

    if(!buffer)
        mBuffer = (uchar*)malloc(sizeof(uchar)*size);
    else
        mBuffer = buffer;

    if((_status = FT_Read(_handle, mBuffer, size, &bytesRead)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        return r;
    }

    for(uint i = 0; i < bytesRead; i++)
        r.append((char)mBuffer[i]);

    if(!buffer)
        delete mBuffer;

    return r;
}

uchar QDmxFTD2XXInterface::readByte(bool* ok)
{
    uchar r;
    DWORD byteRead;

    if((_status = FT_Read(_handle, &r, 1, &byteRead)) != FT_OK)
    {
        qDebug() << Q_FUNC_INFO << errorString(_status);
        *ok = false;
        return 0;
    }

    *ok = true;

    return r;
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
