#ifndef QDMXUNIVERSE_H
#define QDMXUNIVERSE_H

#include <QObject>
#include "QDmxIO.h"

class QDmxManager;

class QDmxUniverse : public QObject
{
    Q_OBJECT

    friend class QDmxManager;

public:
    ~QDmxUniverse();

protected:
    explicit QDmxUniverse(uint id, QDmxIO_ptr in, int inDevice, int inPort, QDmxIO_ptr out, int outDevice, int outPort, QObject *parent = nullptr);

signals:
    void dmxInput(uint id, QByteArray data);

public slots:
    void writeDmx(QByteArray data);

private slots:
    void dmxRecieve(int device, int port, QByteArray data);

protected:
    bool unpatch();

private:
    uint _id;
    QDmxIO_ptr _input;
    int _inDevice;
    int _inPort;
    QDmxIO_ptr _output;
    int _outDevice;
    int _outPort;
};

#endif // QDMXUNIVERSE_H
