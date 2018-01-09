#ifndef QDMXARTNETPLUGIN_H
#define QDMXARTNETPLUGIN_H

#include <network/QDmxGenericNetworkPlugin.h>
#include "QDmxArtnetControler.h"

class QDmxArtnetPlugin : public QDmxGenericNetworkPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QDmxPlugin_iid)
    Q_INTERFACES(QDmxIO)

public:
    QDmxArtnetPlugin(QObject* parent = 0) : QDmxGenericNetworkPlugin(parent) {}

    //===== GENERAL
    virtual QString name() const { return "Art-Net"; }

protected:
    virtual QDmxGenericNetworkControler* getNewControler(QNetworkInterface iface, QNetworkAddressEntry entry)
    {
        return new QDmxArtnetControler(iface, entry);
    }
};

#endif // QDMXARTNETPLUGIN_H
