#ifndef QDMXARTNETCONTROLER_H
#define QDMXARTNETCONTROLER_H

#include "QDmxArtnetPacketizer.h"
#include <network/QDmxGenericNetworkControler.h>
#include <QUdpSocket>

#define ARTNET_PORT 6454

class QDmxArtnetControler : public QDmxGenericNetworkControler
{
    Q_OBJECT
public:
    explicit QDmxArtnetControler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent = nullptr);
    ~QDmxArtnetControler();

    virtual quint32 getNbreInputPort() const { return 4; }
    virtual quint32 getNbreOutputPort() const { return 4; }

    virtual bool listenToUniverse(quint32 u);
    virtual bool ignoreListenedUniverse(quint32 u);

    virtual bool writeToUniverse(quint32 u);
    virtual bool ignoreWrittenUniverse(quint32 u);

public slots:
    virtual void write(quint32 u, QByteArray data);

private slots:
    void readDatagram();

private:
    void socketNeeded();
    void socketUnneeded();
    bool socketIsOk() { return _s && _s->state() == QUdpSocket::BoundState; }
    void sendPollReply();

private:
    QUdpSocket* _s;

    QList<quint32> _listenedUniverse;
    QList<quint32> _writtenUniverse;

    QDmxArtNetPacketizer* _packetizer;
};

typedef QSharedPointer<QDmxArtnetControler> QDmxArtnetControler_ptr;

#endif // QDMXARTNETCONTROLER_H
