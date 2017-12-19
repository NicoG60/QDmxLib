#include "QDmxLib.h"
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>

QDmxLib::QDmxLib(QObject *parent) :
    QObject(parent),
    _plugDir("")
{
    refreshActivePlugins();
}

QDmxLib::~QDmxLib()
{
    deletePlugins();
}

void QDmxLib::setPlugDir(QString path)
{
    _plugDir = QDir(path);
    QCoreApplication::addLibraryPath(_plugDir.absolutePath());
}

QStringList QDmxLib::getPlugList()
{
    QStringList r;

    foreach (QFileInfo fileInfo, _plugDir.entryInfoList(QDir::Files))
        r << fileInfo.baseName();

    return r;
}

void QDmxLib::refreshActivePlugins()
{
    foreach(QString plugName, getPlugList())
    {
        if(!_plugList.contains(plugName))
        {
            QPluginLoader loader(plugName);
            if(loader.load())
            {
                qDebug() << "ok : " << plugName;
                QDmxIO_ptr io;
                io.reset(qobject_cast<QDmxIO*>(loader.instance()));
                _plugList.insert(plugName, io);
            }
        }
    }
}

void QDmxLib::deletePlugins()
{
    qDeleteAll(_plugList);
}
