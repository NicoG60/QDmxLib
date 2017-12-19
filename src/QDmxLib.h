#ifndef QDMXLIB_H
#define QDMXLIB_H

#include <QObject>
#include <QDir>
#include "qdmxlib_global.h"
#include "QDmxIO.h"

typedef QSharedPointer<QDmxIO> QDmxIO_ptr;

class QDMXLIBSHARED_EXPORT QDmxLib : public QObject
{
    Q_OBJECT

public:
    QDmxLib(QObject* parent = 0);
    ~QDmxLib();
    void setPlugDir(QString path);
    QStringList getPlugList();
    void refreshActivePlugins();

private:
    void deletePlugins();

private:
    QDir _plugDir;
    QHash<QString, QDmxIO_ptr> _plugList;
};

#endif // QDMXLIB_H
