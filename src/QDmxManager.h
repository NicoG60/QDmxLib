#ifndef QDMXLIB_H
#define QDMXLIB_H

#include <QObject>
#include <QDir>
#include "qdmxlib_global.h"
#include "QDmxUniverse.h"
#include "QDmxIO.h"

class QDMXLIBSHARED_EXPORT QDmxManager : public QObject
{
    Q_OBJECT

public:
    ~QDmxManager();
    static QDmxManager* instance()
    {
        if(_instance)
            return _instance;
        QMutexLocker locker(&_mutex);
        if(!_instance)
            _instance = new QDmxManager;

        return _instance;
    }

    void setPlugDir(QString path);
    QStringList getPlugList();
    void refreshActivePlugins();

    //==== PLUGINS
    QStringList getDevices(QString plugName);
    int getInputPortCount(QString plugName, int device);
    int getOutputPortCount(QString plugName, int device);
    bool patch(uint universe, QString inPlug, int inDevice, int inPort, QString outPlug, int outDevice, int outPort);
    bool unpatch(uint universe);
    void unpatchAll();

signals:
    void dmxInput(uint u, QByteArray data);

public slots:
    void writeDmx(uint u, QByteArray data);

private slots:
    void dmxRecieve(uint u, QByteArray data);

protected:
    QDmxManager();

private:
    static QDmxManager* _instance;
    static QMutex _mutex;
    QDir _plugDir;
    QHash<QString, QDmxIO_ptr> _plugList;
    QHash<uint, QDmxUniverse*> _patch;
};

#endif // QDMXLIB_H
