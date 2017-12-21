#include "QDmxUniverse.h"

QDmxUniverse::QDmxUniverse(uint id, QDmxIO_ptr in, int inDevice, int inPort, QDmxIO_ptr out, int outDevice, int outPort, QObject *parent) :
    QObject(parent),
    _id(id),
    _input(in),
    _inDevice(inDevice),
    _inPort(inPort),
    _output(out),
    _outDevice(outDevice),
    _outPort(outPort)
{

}

QDmxUniverse::~QDmxUniverse()
{

}

void QDmxUniverse::writeDmx(QByteArray data)
{
    _output->writeDmx(_outDevice, _outPort, data);
}

void QDmxUniverse::dmxRecieve(int device, int port, QByteArray data)
{
    if(_inDevice == device && _inPort == port)
        emit dmxInput(_id, data);
}

bool QDmxUniverse::unpatch()
{
    return _input->closeInput(_inDevice, _inPort) && _output->closeOutput(_outDevice, _outPort);
}
