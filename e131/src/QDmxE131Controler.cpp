#include "QDmxE131Controler.h"
#include <QNetworkDatagram>

QDmxE131Controler::QDmxE131Controler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent) :
    QDmxGenericNetworkControler(interface, entry, parent),
    _packetizer(new QDmxE131Packetizer)
{

}

QDmxE131Controler::~QDmxE131Controler()
{
    delete _packetizer;
    _packetizer = 0;

    _listenedUniverse.clear();
    _writtenUniverse.clear();
    _outputSocket.clear();
}

void QDmxE131Controler::readDatagram()
{
    if(sender())
    {
        QUdpSocket* socket = qobject_cast<QUdpSocket*>(sender());
        if(socket)
        {
            while(socket->hasPendingDatagrams())
            {
                QNetworkDatagram datagram = socket->receiveDatagram();
                if(datagram.senderAddress().isInSubnet(_address, _entry.prefixLength()))
                {
                    QByteArray rawData = datagram.data();

                    if(_packetizer->checkPacket(rawData))
                    {
                        QByteArray dmx;
                        quint32 u;
                        _packetizer->fillDMXdata(rawData, dmx, u);
                        u--;

                        if(_listenedUniverse.contains(u))
                            emit hasDmx(u, dmx);
                    }
                }
            }
        }
    }
}
bool QDmxE131Controler::listenToUniverse(quint32 u)
{
    if(_listenedUniverse.contains(u))
        return true;

    QSharedPointer<QUdpSocket> inputSocket;
    inputSocket.reset(new QUdpSocket(this));
    inputSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, true);

    if(!inputSocket->bind(QHostAddress::AnyIPv4, E131_PORT, QUdpSocket::ShareAddress))
        return false;

    connect(inputSocket.data(), &QUdpSocket::readyRead, this, &QDmxE131Controler::readDatagram);
    connect(inputSocket.data(), static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
          [=](QAbstractSocket::SocketError socketError){
        qDebug() << "Socket Error! : " << socketError << inputSocket->errorString();
    });

    QHostAddress multicast("239.255.0." + QString::number(u+1));

    if(inputSocket->joinMulticastGroup(multicast, _interface))
        _listenedUniverse.insert(u, inputSocket);
    else
        return false;

    qDebug() << "QDmxE131Plugin : " << multicast << " at entry " << _address;

    return true;
}

bool QDmxE131Controler::ignoreListenedUniverse(quint32 u)
{
    _listenedUniverse.remove(u);

    return true;
}

bool QDmxE131Controler::writeToUniverse(quint32 u)
{
    if(_writtenUniverse.contains(u))
        return true;

    if(_writtenUniverse.size() == 0)
    {
        _outputSocket.reset(new QUdpSocket(this));
        _outputSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, true);
        connect(_outputSocket.data(), static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
              [=](QAbstractSocket::SocketError socketError){
            qDebug() << "Socket Error! : " << socketError << _outputSocket->errorString();
        });
        _outputSocket->bind(QHostAddress::AnyIPv4, E131_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        _outputSocket->setMulticastInterface(_interface);
    }

    if(!socketIsOk())
        return false;

    _writtenUniverse.append(u);

    return true;
}

bool QDmxE131Controler::ignoreWrittenUniverse(quint32 u)
{
    _writtenUniverse.removeAll(u);

    if(_writtenUniverse.size() == 0)
        _outputSocket.clear();

    return true;
}

void QDmxE131Controler::write(quint32 u, QByteArray data)
{
    if(_writtenUniverse.contains(u) && data.length() <= 512)
    {
        QByteArray dmxPacket;

        _packetizer->setupE131Dmx(dmxPacket, u+1, E131_PRIORITY_DEFAULT, data);

        if(socketIsOk())
            _outputSocket->writeDatagram(dmxPacket, _broadcast, E131_PORT);
    }
}
