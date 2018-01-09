/*
  Q Light Controller Plus
  ESPNetpacketizer.cpp

  Copyright (c) Massimo Callegari

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "QDmxESPNetPacketizer.h"

#include <QStringList>
#include <QDebug>

QDmxESPNetPacketizer::QDmxESPNetPacketizer()
{
}

QDmxESPNetPacketizer::~QDmxESPNetPacketizer()
{
}

/*********************************************************************
 * Sender functions
 *********************************************************************/

void QDmxESPNetPacketizer::setupESPNetPoll(QByteArray& data)
{
    data.clear();
    data.append('E');
    data.append('S');
    data.append('P');
    data.append('P');
    data.append(0x01); // Type 1 = Full info
}

void QDmxESPNetPacketizer::setupESPNetPollReply(QByteArray &data, ESPNetNodeInfo &info)
{
    data.clear();
    //Head
    data.append('E');
    data.append('S');
    data.append('P');
    data.append('R');

    //MAC Addr
    QStringList MAC = info.mac.split(":");
    foreach (QString couple, MAC)
    {
        bool ok;
        data.append((char)couple.toInt(&ok, 16));
    }

    //Type
    char typeMSB = info.type >> 8;
    char typeLSB = info.type & 0x00FF;
    data.append(typeMSB);
    data.append(typeLSB);

    //Firmware version
    data.append(info.version);

    //clear DIP Switch.
    data.append('\0');

    //Name
    QByteArray name("QDmxLib");
    data.append(name.leftJustified(10, '\0', true));

    //Options
    data.append('\0');
    data.append('\0');
    data.append(0x01);
    data.append('\0');
}

void QDmxESPNetPacketizer::setupESPNetACK(QByteArray &data)
{
    data.clear();
    //Head
    data.append('E');
    data.append('S');
    data.append('A');
    data.append('P');

    data.append('\0');
    data.append('\0');
}

void QDmxESPNetPacketizer::setupESPNetDmx(QByteArray& data, const quint8 &universe, const QByteArray &values)
{
    data.clear();
    //Head
    data.append('E');
    data.append('S');
    data.append('D');
    data.append('D');

    //Universe
    data.append(universe);

    //Start Code
    data.append('\0');

    //Data Type
    data.append(0x01);

    //Data Size
    data.append(0x01);
    data.append('\0');

    data.append(values);
}

/*********************************************************************
 * Receiver functions
 *********************************************************************/

bool QDmxESPNetPacketizer::checkPacketAndCode(QByteArray const& data, int &code)
{
    /* An ESPNet header must be at least 5 bytes long */
    if (data.length() < 5)
        return false;

    /* Check header keyword presence */
    if(data.left(4) == "ESPP")
        code = ESPP;
    else if(data.left(4) == "ESPR")
        code = ESPR;
    else if(data.left(4) == "ESAP")
        code = ESAP;
    else if(data.left(4) == "ESDD")
        code = ESDD;
    else if(data.left(4) == "ESZZ")
        code = ESZZ;
    else
        return false;

    return true;
}

bool QDmxESPNetPacketizer::fillPollReplyInfo(QByteArray const& data, ESPNetNodeInfo& info)
{
    if (data.isNull())
        return false;

    QStringList mac;
    QByteArray rawMAC = data.mid(4,6);

    for(int i = 0; i < rawMAC.length(); i++)
        mac.append(QString::number(rawMAC[i], 16));

    info.mac = mac.join(':');
    info.type = (data[10] << 8) + data[11];
    info.version = data[12];

    return true;
}

bool QDmxESPNetPacketizer::fillDMXdata(QByteArray const& data, QByteArray &dmx, quint32 &universe)
{
    if (data.isNull())
        return false;

    dmx.clear();
    universe = data.at(5);

    unsigned int msb = (data.at(7)&0xff);
    unsigned int lsb = (data.at(8)&0xff);
    int length = (msb << 8) | lsb;

    //qDebug() << "length: " << length;
    dmx.append(data.mid(9, length));
    return true;
}

