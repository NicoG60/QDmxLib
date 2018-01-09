#include "QDmxArtnetControler.h"
#include <QNetworkDatagram>

QDmxArtnetControler::QDmxArtnetControler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent) :
    QDmxGenericNetworkControler(interface, entry, parent),
    _s(0),
    _packetizer(new QDmxArtNetPacketizer)
{
}

QDmxArtnetControler::~QDmxArtnetControler()
{
    delete _packetizer;
    _packetizer = 0;

    _listenedUniverse.clear();
    _writtenUniverse.clear();

    socketUnneeded();
}

bool QDmxArtnetControler::listenToUniverse(quint32 u)
{
    if(_listenedUniverse.contains(u))
       return true;

    socketNeeded();

    if(!socketIsOk())
        return false;

    _listenedUniverse << u;
    qDebug() << "QDmxArtnetPlugin : listening to universe " << u << " at entry " << _address;

    return true;
}

bool QDmxArtnetControler::ignoreListenedUniverse(quint32 u)
{
    _listenedUniverse.removeAll(u);

    socketUnneeded();

    return true;
}

bool QDmxArtnetControler::writeToUniverse(quint32 u)
{
    if(_writtenUniverse.contains(u))
       return true;

    socketNeeded();

    if(!socketIsOk())
        return false;

    _writtenUniverse << u;
    return true;
}

bool QDmxArtnetControler::ignoreWrittenUniverse(quint32 u)
{
    _writtenUniverse.removeAll(u);

    socketUnneeded();

    return true;
}

void QDmxArtnetControler::write(quint32 u, QByteArray data)
{
    if(_writtenUniverse.contains(u) && data.length() <= 512)
    {
        QByteArray dmxPacket;

        _packetizer->setupArtNetDmx(dmxPacket, u, data);

        if(socketIsOk())
            _s->writeDatagram(dmxPacket, _broadcast, ARTNET_PORT);
    }
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

void QDmxArtnetControler::socketNeeded()
{
    if(socketIsOk())
        return;

    if(!_s)
    {
        _s = new QUdpSocket(this);

        connect(_s, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
              [=](QAbstractSocket::SocketError socketError){
            qDebug() << "Socket Error! : " << socketError << _s->errorString();
        });
        connect(_s, &QUdpSocket::readyRead, this, &QDmxArtnetControler::readDatagram);
    }

    if(_s)
        _s->bind(QHostAddress::AnyIPv4, ARTNET_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    if(socketIsOk())
        sendPollReply();
}

void QDmxArtnetControler::socketUnneeded()
{
    if(_listenedUniverse.size() == 0 && _writtenUniverse.size() == 0)
    {
        delete _s;
        _s = 0;
    }
}

void QDmxArtnetControler::sendPollReply()
{
    QByteArray data;
    ArtNetNodeInfo info;
    info.longName = "QDmxLib - Artnet plugin";
    info.shortName = "QDmxLib";
    _packetizer->setupArtNetPollReply(data, info, _address, _mac);
    if(socketIsOk())
        _s->writeDatagram(data, _broadcast, ARTNET_PORT);
}
