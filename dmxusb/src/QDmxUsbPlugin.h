#ifndef QDMXUSBPLUGIN_H
#define QDMXUSBPLUGIN_H

#include <QDmxIO.h>
#include <QDmxUsbDevice.h>

class QDmxUsbPlugin : public QDmxIO
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QDmxPlugin_iid)
    Q_INTERFACES(QDmxIO)

public:
    QDmxUsbPlugin(QObject* parent = 0);
    ~QDmxUsbPlugin();

    //===== GENERAL
    virtual void init();
    virtual QString name() const { return "Dmx USB"; }

    //===== DEVICE
public slots:
    virtual void rescanDevices();
public:
    virtual QMap<quint32, QString> getDevices() const { return QMap<quint32, QString>(); }
    virtual bool deviceExists(quint32 device) const { return false; }

    //===== INPUTS
    virtual quint32 getInputCount(quint32 device) const { return 0; }
    virtual bool inputExists(quint32 device, quint32 port) const { return false; }
    virtual bool openInput(quint32 device, quint32 port) { return false; }
    virtual bool closeInput(quint32 device, quint32 port) { return false; }

private slots:
    void dmxRecieve(quint32 universe, const QByteArray& data) {}

    //===== OUTPUTS
public:
    virtual quint32 getOutputCount(quint32 device) const { return 0; }
    virtual bool outputExists(quint32 device, quint32 port) const { return false; }
    virtual bool openOutput(quint32 device, quint32 port) { return false; }
    virtual bool closeOutput(quint32 device, quint32 port) { return false; }

public slots:
    virtual void writeDmx(quint32 device, quint32 port, QByteArray data) {}

private:
    QMap<quint32, QDmxUsbDevice*> _deviceList;
};

#endif // QDMXUSBPLUGIN_H
