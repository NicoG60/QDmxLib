#include "QDmxArtnetControler.h"
#include <QNetworkDatagram>

QDmxArtnetControler::QDmxArtnetControler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent) :
    QObject(parent),
    _interface(interface),
    _entry(entry),
    _address(entry.ip()),
    _s(0),
    _packetizer(new QDmxArtNetPacketizer)
{

}

QDmxArtnetControler::~QDmxArtnetControler()
{
    if(_s)
    {
        _s->close();
        _s->deleteLater();
    }

    delete _packetizer;
}

bool QDmxArtnetControler::isAddress(QNetworkAddressEntry e) const
{
    return _entry == e;
}

void QDmxArtnetControler::init()
{
    _mutex.lock();
    QMetaObject::invokeMethod(this, "createSocket", Qt::QueuedConnection);
    _wait.wait(&_mutex);
    _mutex.unlock();
}

QString QDmxArtnetControler::getAddrString() const
{
    return _entry.ip().toString();
}

void QDmxArtnetControler::createSocket()
{
    if(!_s)
    {
        _s = new QUdpSocket;
        connect(_s, &QUdpSocket::readyRead, this, &QDmxArtnetControler::readDatagram);
        connect (_s, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                             [=](QAbstractSocket::SocketError socketError){ Q_UNUSED(socketError) qDebug() << _s->errorString(); });
        _s->bind(ARTNET_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        if(socketIsOk())
            sendPollReply();
    }
    _wait.wakeAll();
}

void QDmxArtnetControler::readDatagram()
{
    while(_s->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = _s->receiveDatagram();
        if(datagram.senderAddress().isInSubnet(_address, _entry.prefixLength()))
        {
            QByteArray rawData = datagram.data();

            int code;
            if(_packetizer->checkPacketAndCode(rawData, code))
            {
                if(code == ARTNET_POLL)
                    sendPollReply();
                if(code == ARTNET_DMX)
                {
                    QByteArray dmx;
                    quint32 u;
                    _packetizer->fillDMXdata(rawData, dmx, u);

                    if(_listenedUniverse.contains(u))
                        emit hasDmx(u, dmx);
                }
            }
        }
    }
}

bool QDmxArtnetControler::socketIsOk()
{
    return _s && _s->state() == QUdpSocket::BoundState;
}

bool QDmxArtnetControler::disconnectSocket()
{
    if(_s)
        _s->close();

    return true;
}

void QDmxArtnetControler::sendPollReply()
{
    QByteArray data;
    ArtNetNodeInfo info;
    info.longName = "QDmxLib - Artnet plugin";
    info.shortName = "QDmxLib";
    _packetizer->setupArtNetPollReply(data, info, _address, _interface.hardwareAddress());
    if(socketIsOk())
    {
        int r = _s->writeDatagram(data, _entry.broadcast(), ARTNET_PORT);
        if(r < 0)
        {
            qDebug() << "Artnet ArtPollReply Error";
            qDebug() << _s->error();
            qDebug() << _s->errorString();
        }
    }
}

bool QDmxArtnetControler::listenToUniverse(int u)
{
    bool r = socketIsOk();
    if(r)
    {
        if(!_listenedUniverse.contains(u))
            _listenedUniverse << u;
    }
    return r;
}

bool QDmxArtnetControler::ignoreListenedUniverse(int u)
{
    if(_listenedUniverse.contains(u))
        _listenedUniverse.removeAll(u);

    return true;
}

bool QDmxArtnetControler::writeToUniverse(int u)
{
    bool r = socketIsOk();
    if(r)
    {
        if(!_writtenUniverse.contains(u))
            _writtenUniverse << u;
    }
    return r;
}

bool QDmxArtnetControler::ignoreWrittenUniverse(int u)
{
    if(_writtenUniverse.contains(u))
        _writtenUniverse.removeAll(u);

    return true;
}

void QDmxArtnetControler::write(int u, QByteArray data)
{
    if(_writtenUniverse.contains(u) && data.length() <= 512)
    {
        QByteArray dmxPacket;

        _packetizer->setupArtNetDmx(dmxPacket, u, data);

        if(socketIsOk())
        {
            int r = _s->writeDatagram(dmxPacket, _entry.broadcast(), ARTNET_PORT);
            if(r < 0)
            {
                qDebug() << "Artnet Send Dmx Error";
                qDebug() << _s->error();
                qDebug() << _s->errorString();
            }
        }
    }
}
