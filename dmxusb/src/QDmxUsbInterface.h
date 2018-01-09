#ifndef QDMXUSBINTERFACE_H
#define QDMXUSBINTERFACE_H

#include <QtCore>

class QDmxUsbInterface
{
public:
    QDmxUsbInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id = 0);
    virtual ~QDmxUsbInterface() {}

    /** Get the device's USB serial number */
    QString serial() const { return _serial; }

    /** Get the device's USB name */
    QString name() const { return _name; }

    /** Get the device's USB vendor name */
    QString vendor() const { return _vendor; }

    /** Get the device's USB vendor ID */
    quint16 vendorID() const { return _vendorID; }

    /** Get the device's USB product ID */
    quint16 productID() const { return _productID; }

    /** Get the device's FTD2XX ID number */
    quint32 id() const { return _id; }

    /** Virtual method to retrieve the original USB
     *  bus location of the device.
     *  Used only in Linux to perform a sysfs lookup */
    //virtual quint8 busLocation();

private:
    QString _serial;
    QString _name;
    QString _vendor;
    quint16 _vendorID;
    quint16 _productID;
    quint32 _id;

    /************************************************************************
     * Widget enumeration
     ************************************************************************/
public:
    static const int FTDIVID = 0x0403;      //! FTDI Vendor ID
    static const int ATMELVID = 0x03EB;     //! Atmel Vendor ID
    static const int MICROCHIPVID = 0x04D8; //! Microchip Vendor ID
    static const int FTDIPID = 0x6001;      //! FTDI Product ID
    static const int DMX4ALLPID = 0xC850;   //! DMX4ALL FTDI Product ID
    static const int NANODMXPID = 0x2018;   //! DMX4ALL Nano DMX Product ID
    static const int EUROLITEPID = 0xFA63;  //! Eurolite USB DMX Product ID
    static const int ELECTROTASPID = 0x0000;//! ElectroTAS USB DMX Product ID

    /** Driver types */
    enum Type
    {
        libFTDI = 0,
        FTD2xx,
        QtSerial
    };

    /**
     * Check if an interface is supported
     *
     * @return true if supported, false if unsupported
     */
    static bool validInterface(quint16 vendor, quint16 product);

    bool checkInfo(QString &serial, QString &name, QString &vendor);

    /************************************************************************
     * DMX/Serial Interface Methods
     ************************************************************************/
public:
    virtual QDmxUsbInterface::Type type() = 0;

    virtual QString typeString() = 0;

    /** Open the device */
    virtual bool open() = 0;

    /** Open the device using a specific Product ID */
    virtual bool openByPID(const int FTDIPID) = 0;

    /** Close the device */
    virtual bool close() = 0;

    /** Check if the device is open */
    virtual bool isOpen() const = 0;

    /** Reset the communications line */
    virtual bool reset() = 0;

    /** Setup communications line for 8N2 traffic */
    virtual bool setLineProperties() = 0;

    /** Set 250kbps baud rate */
    virtual bool setBaudRate() = 0;

    /** Disable flow control */
    virtual bool setFlowControl() = 0;

    /** Clear the RTS bit */
    virtual bool clearRts() = 0;

    /** Purge TX & RX buffers */
    virtual bool purgeBuffers() = 0;

    /** Toggle communications line BREAK condition on/off */
    virtual bool setBreak(bool on) = 0;

    /** Write data to a previously-opened line */
    virtual bool write(const QByteArray& data) = 0;

    /** Read data from a previously-opened line. Optionally provide own data buffer. */
    virtual QByteArray read(int size, uchar* buffer = NULL) = 0;

    /** Read exactly one byte. $ok tells if a byte was read or not. */
    virtual uchar readByte(bool* ok = NULL) = 0;
};

#endif // QDMXUSBINTERFACE_H
