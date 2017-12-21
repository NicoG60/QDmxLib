#include "QDmxManager.h"
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>

QDmxManager* QDmxManager::_instance = nullptr;
QMutex QDmxManager::_mutex;

QDmxManager::QDmxManager() :
    QObject()
{
}

QDmxManager::~QDmxManager()
{
    unpatchAll();
}

void QDmxManager::setPlugDir(QString path)
{
    _plugDir = QDir(path);
    QCoreApplication::addLibraryPath(_plugDir.absolutePath());
}

QStringList QDmxManager::getPlugList()
{
    return _plugList.keys();
}

void QDmxManager::refreshActivePlugins()
{
    foreach (QFileInfo fileInfo, _plugDir.entryInfoList(QDir::Files))
    {
        QString plugName = fileInfo.baseName();
        if(!_plugList.contains(plugName))
        {
            QPluginLoader loader(plugName);
            if(loader.load())
            {
                qDebug() << "ok : " << plugName;
                QDmxIO_ptr io;
                io.reset(qobject_cast<QDmxIO*>(loader.instance()));
                if(io)
                {
                    io->init();
                    _plugList.insert(plugName, io);
                }
                else
                    loader.unload();
            }
        }
    }
}

QStringList QDmxManager::getDevices(QString plugName)
{
    QDmxIO_ptr io = _plugList.value(plugName, nullptr);
    if(io)
        return io->getDevices();
    else
        return QStringList();
}

int QDmxManager::getInputPortCount(QString plugName, int device)
{
    QDmxIO_ptr io = _plugList.value(plugName, nullptr);
    if(io)
        return io->getInputCount(device);
    else
        return -1;
}

int QDmxManager::getOutputPortCount(QString plugName, int device)
{
    QDmxIO_ptr io = _plugList.value(plugName, nullptr);
    if(io)
        return io->getOutputCount(device);
    else
        return -1;
}

bool QDmxManager::patch(uint universe, QString inPlug, int inDevice, int inPort, QString outPlug, int outDevice, int outPort)
{
    if(_patch.contains(universe))
        return false;

    QDmxIO_ptr in = _plugList.value(inPlug, nullptr);

    if(!in)
        return false;

    if(!in->deviceExists(inDevice))
        return false;

    if(!in->inputExists(inDevice, inPort))
        return false;

    if(in->inputIsOpened(inDevice, inPort))
        return false;

    QDmxIO_ptr out = _plugList.value(outPlug, nullptr);

    if(!out)
        return false;

    if(!out->deviceExists(outDevice))
        return false;

    if(!out->inputExists(outDevice, outPort))
        return false;

    if(out->inputIsOpened(outDevice, outPort))
        return false;

    if(!in->openInput(inDevice, inPort))
        return false;

    if(!out->openOutput(outDevice, outPort))
        return false;

    QDmxUniverse* u = new QDmxUniverse(universe, in, inDevice, inPort, out, outDevice, outPort);
    connect(u, &QDmxUniverse::dmxInput, this, &QDmxManager::dmxRecieve);

    _patch.insert(universe, u);

    return true;
}

bool QDmxManager::unpatch(uint universe)
{
    QDmxUniverse* u = _patch.value(universe, nullptr);

    if(!u)
        return false;

    disconnect(u, &QDmxUniverse::dmxInput, this, &QDmxManager::dmxRecieve);

    bool r = u->unpatch();

    _patch.remove(universe);
    delete u;
    return r;
}

void QDmxManager::unpatchAll()
{
    foreach(uint u, _patch.keys())
        unpatch(u);
}

void QDmxManager::writeDmx(uint u, QByteArray data)
{
    if(_patch.contains(u))
        _patch.value(u)->writeDmx(data);
}

void QDmxManager::dmxRecieve(uint u, QByteArray data)
{
    emit dmxInput(u, data);
}
