/*
  Inspired from QLC Plus sources

  Copyright (c) Massimo Callegari
*/
#ifndef E131PACKETIZER_H
#define E131PACKETIZER_H

#include <QHostAddress>
#include <QByteArray>
#include <QString>
#include <QHash>

#define E131_PRIORITY_DEFAULT 100

class QDmxE131Packetizer
{
    /*********************************************************************
     * Initialization
     *********************************************************************/
public:
    QDmxE131Packetizer();
    ~QDmxE131Packetizer();

public:
    /*********************************************************************
     * Sender functions
     *********************************************************************/

    /** Prepare an E1.31 DMX packet */
    void setupE131Dmx(QByteArray& data, const int& universe, const int& priority, const QByteArray &values);

    /*********************************************************************
     * Receiver functions
     *********************************************************************/

    /** Verify the validity of an E1.31 packet and store the opCode in 'code' */
    bool checkPacket(QByteArray& data);

    bool fillDMXdata(QByteArray& data, QByteArray& dmx, quint32 &universe);

private:
    QByteArray m_commonHeader;
    QHash<int, uchar> m_sequence;
};

#endif
