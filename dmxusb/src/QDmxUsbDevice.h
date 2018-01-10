#ifndef QDMXUSBDEVICE_H
#define QDMXUSBDEVICE_H

#include <QThread>
#include "QDmxUsbInterface.h"

class QDmxUsbDevice : public QThread
{
    Q_OBJECT
/*******************
 *  GENERAL
 *******************/
public:
    QDmxUsbDevice(QDmxUsbInterface* iface, QObject* parent = 0);
    ~QDmxUsbDevice();

    /** Device types */
    enum Type
    {
        ProRXTX,    //! Enttec Pro device using the TX/RX features of the dongle
        OpenTX,     //! Enttec Open device (only TX)
        ProMk2,     //! Enttec Pro Mk2 device using 2 TX, 1 RX, 1 MIDI TX and 1 MIDI RX ports
        UltraPro,   //! DMXKing Ultra Pro device using 2 TX and 1RX ports
        DMX4ALL,    //! DMX4ALL device (only TX)
        VinceTX,    //! Vince USB-DMX512 device using the TX side of the dongle
        Eurolite    //! Eurolite USB DMX512 Pro device
    };

    /** Get the type of the device */
    virtual Type type() const = 0;

    /** Get the QDmxInterface instance */
    QDmxUsbInterface* interface() const;

    /** Get the QDmxInterface driver in use as a string */
    QString interfaceTypeString() const;

    /** change internal driver */
    bool forceInterfaceDriver(QDmxUsbInterface::Type type);

    /** Get list of all connected devices */
    static QMap<quint32, QDmxUsbDevice *> devices();

protected:
    virtual void run() = 0;

private:
    QDmxUsbInterface* _iface;

/*******************
 * OPEN & CLOSE
 *******************/
public:
    /**
     * @return the number of input ports
     */
    virtual quint32 getNbreInputPort();

    /**
     * @return the number of output ports
     */
    virtual quint32 getNbreOutputPort();

    /**
     * Open the given input or output port. Configures the interface to interact with this port properly
     * @return true on success
     */
    virtual bool open(quint32 port, bool input = false);

    /**
     * Close the given input or output port. release the interface if not needed anymore
     * @return true on success
     */
    virtual bool close(quint32 port, bool input = false);

protected:
    QList<quint32> _openedInput;
    QList<quint32> _openedOutput;

    /********************************************************************
     * Serial & name
     ********************************************************************/
public:
    /**
     * @return device's serial number in string form
     */
    virtual QString serial() const { return _iface->serial(); }

    /**
     * @return device's name
     */
    virtual QString name() const { return _iface->name(); }

    /**
     * @return device's unique name as: "<name> (S/N: <serial>)"
     */
    virtual QString uniqueName() const { return QString("%1 (S/N: %2)").arg(name()).arg(serial()); }

    /** Set the real device name extracted from serial using label 78 */
    void setRealName(QString devName);

    /** retrieve the real device name read from label 78 */
    virtual QString realName() const;

    /**
     * @return device's vendor
     */
    virtual QString vendor() const;

    /**
     * Get any additional information pertaining to the device (can be empty)
     */
    virtual QString additionalInfo() const { return QString(); }

private:
    QString m_realName;
};

#endif // QDMXUSBDEVICE_H
