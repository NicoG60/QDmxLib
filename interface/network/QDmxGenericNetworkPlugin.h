#ifndef QDMXGENERICNETWORKPLUGIN_H
#define QDMXGENERICNETWORKPLUGIN_H

#include "QDmxGenericNetworkControler.h"
#include "../QDmxIO.h"

class QDmxGenericNetworkPlugin : public QDmxIO
{
    Q_OBJECT

public:
    QDmxGenericNetworkPlugin(QObject* parent = 0);
    virtual ~QDmxGenericNetworkPlugin();

    //===== GENERAL
    virtual void init();
    virtual QString name() const = 0;

    //===== DEVICE
public slots:
    virtual void rescanDevices();
public:
    virtual QMap<quint32, QString> getDevices() const;
    virtual bool deviceExists(quint32 device) const                 { return _controlerList.contains(device); }

    //===== INPUTS
    virtual quint32 getInputCount(quint32 device) const             { if(deviceExists(device)) return _controlerList.value(device)->getNbreInputPort(); return 0; }
    virtual bool inputExists(quint32 device, quint32 port) const    { return port < getInputCount(device); }
    virtual bool openInput(quint32 device, quint32 port);
    virtual bool closeInput(quint32 device, quint32 port);

private slots:
    void dmxRecieve(quint32 universe, const QByteArray& data);

    //===== OUTPUTS
public:
    virtual quint32 getOutputCount(quint32 device) const            { if(deviceExists(device)) return _controlerList.value(device)->getNbreOutputPort(); return 0; }
    virtual bool outputExists(quint32 device, quint32 port) const   { return port < getOutputCount(device); }
    virtual bool openOutput(quint32 device, quint32 port);
    virtual bool closeOutput(quint32 device, quint32 port);

public slots:
    virtual void writeDmx(quint32 device, quint32 port, QByteArray data);

protected:
	virtual QDmxGenericNetworkControler* getNewControler(QNetworkInterface iface, QNetworkAddressEntry entry) = 0;

private:
    QMap<quint32, QDmxGenericNetworkControler_ptr> _controlerList;
};

#endif // QDMXGENERICNETWORKPLUGIN_H
