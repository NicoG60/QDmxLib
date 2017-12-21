#ifndef QDMXARTNETPLUGIN_H
#define QDMXARTNETPLUGIN_H

#include "QDmxIO.h"
#include "QDmxArtnetControler.h"

#include <QThread>

class QDmxArtnetPlugin : public QDmxIO
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QDmxPlugin_iid)
    Q_INTERFACES(QDmxIO)

public:
    QDmxArtnetPlugin(QObject* parent = 0);
    virtual ~QDmxArtnetPlugin();

    //===== GENERAL
    virtual void init();
    virtual QString name() { return "Art-Net"; }

    //===== DEVICE
    virtual QStringList getDevices();
    virtual bool deviceExists(int device);

    //===== INPUTS
    virtual int getInputCount(int device);
    virtual bool inputExists(int device, int port);
    virtual bool openInput(int device, int port);
    virtual bool closeInput(int device, int port);

private slots:
    void dmxRecieve(int universe, QByteArray data);

signals:
    void dmxInput(int device, int port, QByteArray data);

    //===== OUTPUTS
public:
    virtual int getOutputCount(int device);
    virtual bool outputExists(int device, int port);
    virtual bool openOutput(int device, int port);
    virtual bool closeOutput(int device, int port);

public slots:
    virtual void writeDmx(int device, int port, QByteArray data);

private:
    QThread* _worker;
    QList<QDmxArtnetControler_ptr> _controlerList;
};

#endif // QDMXARTNETPLUGIN_H
