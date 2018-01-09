#ifndef QDMXARTNETCONTROLER_H
#define QDMXARTNETCONTROLER_H

#include "QDmxE131Packetizer.h"
#include <network/QDmxGenericNetworkControler.h>
#include <QUdpSocket>

#define E131_PORT 5568

class QDmxE131Controler : public QDmxGenericNetworkControler
{
    Q_OBJECT
public:
    explicit QDmxE131Controler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent = nullptr);
    ~QDmxE131Controler();

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
    bool socketIsOk() { return _outputSocket && _outputSocket->state() == QUdpSocket::BoundState; }

private:
    QSharedPointer<QUdpSocket> _outputSocket;

    QHash<quint32, QSharedPointer<QUdpSocket>> _listenedUniverse;
    QList<quint32> _writtenUniverse;

    QDmxE131Packetizer* _packetizer;
};

typedef QSharedPointer<QDmxE131Controler> QDmxE131Controler_ptr;

#endif // QDMXARTNETCONTROLER_H
