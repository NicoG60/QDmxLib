#ifndef QDMXARTNETCONTROLER_H
#define QDMXARTNETCONTROLER_H

#include "QDmxArtnetPacketizer.h"

#include <QObject>
#include <QNetworkAddressEntry>
#include <QUdpSocket>
#include <QMutex>
#include <QWaitCondition>

#define ARTNET_PORT 6454

typedef QSharedPointer<QDmxArtnetControler> QDmxArtnetControler_ptr;

class QDmxArtnetControler : public QObject
{
    Q_OBJECT
public:
    explicit QDmxArtnetControler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent = nullptr);
    ~QDmxArtnetControler();

    QString errorString() { return _lastError; }

    bool isAddress(QNetworkAddressEntry e) const;

    void init();
    QString getAddrString() const;
    int getNbreInputPort() const { return 4; }
    int getNbreOutputPort() const { return 4; }

    bool listenToUniverse(int u);
    bool ignoreListenedUniverse(int u);

    bool writeToUniverse(int u);
    bool ignoreWrittenUniverse(int u);

public slots:
    void write(int u, QByteArray data);

signals:
    void hasDmx(int universe, QByteArray data);

private slots:
    void createSocket();
    void readDatagram();

private:
    bool connectSocket();
    bool disconnectSocket();
    void sendPollReply();

private:
    QNetworkInterface _interface;
    QNetworkAddressEntry _entry;
    QHostAddress _address;

    QString _lastError;

    QUdpSocket* _s;

    QMutex _mutex;
    QWaitCondition _wait;

    QList<int> _listenedUniverse;
    QList<int> _writtenUniverse;

    QDmxArtNetPacketizer* _packetizer;
};

#endif // QDMXARTNETCONTROLER_H
