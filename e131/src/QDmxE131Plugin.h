#ifndef QDMXARTNETPLUGIN_H
#define QDMXARTNETPLUGIN_H

#include "QDmxE131Controler.h"
#include <network/QDmxGenericNetworkPlugin.h>

class QDmxE131Plugin : public QDmxGenericNetworkPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QDmxPlugin_iid)
    Q_INTERFACES(QDmxIO)

public:
    QDmxE131Plugin(QObject* parent = 0) : QDmxGenericNetworkPlugin(parent) {}

    //===== GENERAL
    virtual QString name() const { return "E1.31 - sACN"; }

protected:
    virtual QDmxGenericNetworkControler* getNewControler(QNetworkInterface iface, QNetworkAddressEntry entry)
    {
        return new QDmxE131Controler(iface, entry);
    }
};

#endif // QDMXARTNETPLUGIN_H
