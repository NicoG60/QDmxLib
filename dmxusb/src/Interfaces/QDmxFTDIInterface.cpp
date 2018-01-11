#include "QDmxFTDIInterface.h"

#include <memory>
#include <libusb.h>

QDmxFTDIInterface::QDmxFTDIInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id) :
    QDmxUsbInterface(serial, name, vendor, VID, PID, id)
{
    memset(&_ftdi, 0 , sizeof(struct ftdi_context));
    ftdi_init(&_ftdi);
}

QDmxFTDIInterface::~QDmxFTDIInterface()
{
    if(isOpen())
        close();
    ftdi_deinit(&_ftdi);
}

QList<QDmxUsbInterface*> QDmxFTDIInterface::interfaces(QList<QDmxUsbInterface *> found)
{
    QList<QDmxUsbInterface*> r;

    //Init FTDI context
    struct ftdi_context* ftdi = ftdi_new();

    if(!ftdi)
        return r;

    libusb_set_debug(ftdi->usb_ctx, LIBUSB_LOG_LEVEL_WARNING);

    //get devices list
    struct ftdi_device_list* devList;

    if(ftdi_usb_find_all(ftdi, &devList, 0, 0) < 0)
    {
        qDebug() << "failed to find : " << ftdi_get_error_string(ftdi);
        ftdi_free(ftdi);
        return r;
    }

    //browse device list
    struct ftdi_device_list* curDev = devList;
    char manu[128], desc[128], serial[128];
    int id = 0;

    while(curDev != nullptr)
    {
        if(ftdi_usb_get_strings(ftdi, curDev->dev, manu, 128, desc, 128, serial, 128) < 0)
        {
            qDebug() << "failed to read strings : " << ftdi_get_error_string(ftdi);
            id++;
            curDev = curDev->next;
            continue;
        }

        qDebug() << manu << " - " << desc << " - " << serial;
        QString sManu(manu), sDesc(desc), sSerial(serial);

        struct libusb_device_descriptor usb_desc;
        libusb_get_device_descriptor(curDev->dev, &usb_desc);

        if(validInterface(usb_desc.idVendor, usb_desc.idProduct))
        {
            bool exists = false;
            for(int i = 0; i < found.length() && !exists; i++)
                exists |= found[i]->checkInfo(sSerial, sDesc, sManu);

            if(!exists)
                r << new QDmxFTDIInterface(sSerial, sDesc, sManu, usb_desc.idVendor, usb_desc.idProduct, id);
        }

        id++;
        curDev = curDev->next;
    }

    ftdi_list_free(&devList);
    ftdi_free(ftdi);
    return r;
}

bool QDmxFTDIInterface::open()
{
    if(isOpen())
        return true;

    const char* ser = (const char*)(serial().toLatin1().data());
    const char* desc = (const char*)(name().toLatin1().data());

    if(ftdi_usb_open_desc(&_ftdi, vendorID(), productID(), desc, ser) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::openByPID(const int FTDIPID)
{
    if(isOpen())
        return true;

    if(ftdi_usb_open(&_ftdi, QDmxUsbInterface::FTDIVID, FTDIPID) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::close()
{
    if(!isOpen())
        return true;

    if(ftdi_usb_close(&_ftdi) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::isOpen() const
{
    return _ftdi.usb_dev != nullptr;
}

bool QDmxFTDIInterface::reset()
{
    if(ftdi_usb_reset(&_ftdi) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::setLineProperties()
{
    if(ftdi_set_line_property(&_ftdi, BITS_8, STOP_BIT_2, NONE) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::setBaudRate()
{
    if(ftdi_set_baudrate(&_ftdi, 250000) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::setFlowControl()
{
    if(ftdi_setflowctrl(&_ftdi, SIO_DISABLE_FLOW_CTRL) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::clearRts()
{
    if(ftdi_setrts(&_ftdi, 0) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::purgeBuffers()
{
    if(ftdi_usb_purge_buffers(&_ftdi) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::setBreak(bool on)
{
    if(ftdi_set_line_property2(&_ftdi, BITS_8, STOP_BIT_2, NONE, on ? BREAK_ON : BREAK_OFF) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

bool QDmxFTDIInterface::write(const QByteArray& data)
{
    if(ftdi_write_data(&_ftdi,(uchar*) data.data(), data.size()) < 0)
    {
        qDebug() << Q_FUNC_INFO << ftdi_get_error_string(&_ftdi);
        return false;
    }

    return true;
}

QByteArray QDmxFTDIInterface::read(int size, uchar* buffer)
{
    uchar* mBuffer;
    if(!buffer)
        mBuffer = (uchar*) malloc(sizeof(uchar) * size);
    else
        mBuffer = buffer;
    Q_ASSERT(buffer != nullptr);

    QByteArray r;

    int read = ftdi_read_data(&_ftdi, mBuffer, size);

    for(int i = 0; i < read; i++)
        r.append((char)mBuffer[i]);

    if(buffer == nullptr) delete mBuffer;

    return r;
}

uchar QDmxFTDIInterface::readByte(bool* ok)
{
    uchar byte = 0;
    int read = ftdi_read_data(&_ftdi, &byte, 1);

    if(ok)
        *ok = (read == 1);

    return byte;
}
