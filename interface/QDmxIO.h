#ifndef QDMXIO_H
#define QDMXIO_H

class QDmxIO;

#include <QObject>
#include <QMultiHash>
#include <QSharedPointer>
#include <QSettings>

/*
 * This is the interface of the QDmxLib plugin.
 * A plugin must implement all pure methods to work with the lib.
 * Some rules for the implementation :
 * - A plugin have to work on a maximum of desktop plateform. This include in priority Windows, Mac OS and Linux.
 * - A plugin have to use the minimum of ressources and use it only if it's necessary.
 * - A plugin have to clear all its ressources on his destruction.
 */

class QDmxIO : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief default construcor
     * Default constructor. A plugin can use it to initialize some variables but don't allocate any ressources from it.
     * A plugin simply can't have specific constructor because there is no way to call it.
     * A second init method is here to do the real initialization.
     */
    QDmxIO(QObject* parent = 0) : QObject(parent) {;}

    /**
     * @brief destructor
     * De-initialize the plugin, all general ressources must be cleared.
     * Each plugin have to implement its own destructor.
     */
    virtual ~QDmxIO() {}

    //===== GENERAL
    /**
     * @brief init the plugin
     * This method do a general initialization. It have to be as economic as possible with allocated ressources.
     */
    virtual void init() = 0;

    /**
     * @brief return the name of the plugin
     * @return name
     */
    virtual QString name() const = 0;

    /**
     * @brief return a human readable error message when it happens.
     * @return error string
     */
    QString errorString() { QString r = _lastError; _lastError.clear(); return r; }

    //===== DEVICE

public slots:
    /**
     * @brief this method looks for the devices and fill the device map. A device must have the same id during all the plugin lifetime. If an existing device become unreachable, the methods has to close the device and delete it.
     */
    virtual void rescanDevices() = 0;

public:
    /**
     * @brief return a map of the available devices associating there unique id with a human readable name. From this map, the user can select the device he wants to work with.
     * @return device map.
     */
    virtual QMap<quint32, QString> getDevices() const = 0;

    /**
     * @brief check if a device exists.
     * @param device : the device id from the device map
     * @return  true if it exists, else : false.
     */
    virtual bool deviceExists(quint32 device) const = 0;

    //===== INPUTS
    /**
     * @brief return the number of input port that can be useb by a specific device. a port id is contained between 0 and this number-1.
     * @param device : the device id from the device map
     * @return the number of ports.
     */
    virtual quint32  getInputCount(quint32 device) const = 0;

    /**
     * @brief check if an input exists
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it exists, else : false.
     */
    virtual bool inputExists(quint32 device, quint32 port) const = 0;

    /**
     * @brief open the specified input. The ressources specific to this input must be allocated here and not before.
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it can be opened, else : false
     */
    virtual bool openInput(quint32 device, quint32 port) = 0;

    /**
     * @brief close the specified input. The ressources specific to this input must be cleared here and not after.
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it can be closed, else : false
     */
    virtual bool closeInput(quint32 device, quint32 port) = 0;

    /**
     * @brief check if a specific input is opened or not.
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it is opened, else : false
     */
    bool inputIsOpened(quint32 device, quint32 port) const { return _openedInput.contains(device, port); }

signals:
    /**
     * @brief signal emited when dmx data from an opened input port is recieved.
     * @param device : the device id from the device map
     * @param port : the port number
     * @param data : the dmx data
     */
    void dmxInput(quint32 device, quint32 port, QByteArray data);

    //===== OUTPUTS
public:
    /**
     * @brief return the number of output port that can be useb by a specific device. a port id is contained between 0 and this number-1.
     * @param device : the device id from the device map
     * @return the number of ports.
     */
    virtual quint32  getOutputCount(quint32 device) const = 0;

    /**
     * @brief check if an output exists
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it exists, else : false.
     */
    virtual bool outputExists(quint32 device, quint32 port) const = 0;

    /**
     * @brief open the specified output. The ressources specific to this output must be allocated here and not before.
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it can be opened, else : false
     */
    virtual bool openOutput(quint32 device, quint32 port) = 0;

    /**
     * @brief close the specified output. The ressources specific to this output must be cleared here and not after.
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it can be closed, else : false
     */
    virtual bool closeOutput(quint32 device, quint32 port) = 0;

    /**
     * @brief check if a specific output is opened or not.
     * @param device : the device id from the device map
     * @param port : the port number
     * @return true if it is opened, else : false
     */
    bool outputIsOpened(quint32 device, quint32 port) const { return _openedOutput.contains(device, port); }

public slots:
    /**
     * @brief slots to call when an output is needed. For serial devices, the plugin have to handle the repetition of the data over the serial line. this method must be call only when data change.
     * @param device : the device id from the device map
     * @param port : the port number
     * @param data : the dmx data
     */
    virtual void writeDmx(quint32 device, quint32 port, QByteArray data) = 0;

protected:
    QMultiHash<quint32,quint32> _openedInput;
    QMultiHash<quint32,quint32> _openedOutput;
    QString _lastError;
};

typedef QSharedPointer<QDmxIO> QDmxIO_ptr;

#define QDmxPlugin_iid "org.qdmxlib.QDmxIO"

Q_DECLARE_INTERFACE(QDmxIO, QDmxPlugin_iid)

#endif // QDMXIO_H
