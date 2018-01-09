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
    virtual QMap<quint32, QString> getDevices() const {}
    virtual bool deviceExists(quint32 device) const {}

    //===== INPUTS
    virtual quint32 getInputCount(quint32 device) const {}
    virtual bool inputExists(quint32 device, quint32 port) const {}
    virtual bool openInput(quint32 device, quint32 port) {}
    virtual bool closeInput(quint32 device, quint32 port) {}

private slots:
    void dmxRecieve(quint32 universe, const QByteArray& data) {}

    //===== OUTPUTS
public:
    virtual quint32 getOutputCount(quint32 device) const {}
    virtual bool outputExists(quint32 device, quint32 port) const {}
    virtual bool openOutput(quint32 device, quint32 port) {}
    virtual bool closeOutput(quint32 device, quint32 port) {}

public slots:
    virtual void writeDmx(quint32 device, quint32 port, QByteArray data) {}

private:
    QMap<quint32, QDmxUsbDevice*> _deviceList;
};

#endif // QDMXUSBPLUGIN_H
