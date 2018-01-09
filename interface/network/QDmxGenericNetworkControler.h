#ifndef QDMXGENERICNETWORKCONTROLER_H
#define QDMXGENERICNETWORKCONTROLER_H

#include <QObject>
#include <QNetworkAddressEntry>

class QDmxGenericNetworkControler : public QObject
{
    Q_OBJECT
public:
    explicit QDmxGenericNetworkControler(QNetworkInterface interface, QNetworkAddressEntry entry, QObject *parent = nullptr);
    ~QDmxGenericNetworkControler() {}

    QString errorString() { return _lastError; }

    bool isAddress(QNetworkAddressEntry e) const { return _entry == e; }
    bool isAddress(QHostAddress a) const { return _address == a; }

    QString getAddrString() const { return _address.toString(); }
    virtual quint32 getNbreInputPort() const = 0;
    virtual quint32 getNbreOutputPort() const = 0;

    virtual bool listenToUniverse(quint32 u) = 0;
    virtual bool ignoreListenedUniverse(quint32 u) = 0;

    virtual bool writeToUniverse(quint32 u) = 0;
    virtual bool ignoreWrittenUniverse(quint32 u) = 0;

public slots:
    virtual void write(quint32 u, QByteArray data) = 0;

signals:
    void hasDmx(quint32 universe, const QByteArray& data);

protected:
    QNetworkInterface _interface;
    QNetworkAddressEntry _entry;
    QHostAddress _address;
    QHostAddress _broadcast;
    QString _mac;

    QString _lastError;
};

typedef QSharedPointer<QDmxGenericNetworkControler> QDmxGenericNetworkControler_ptr;

#endif // QDMXGENERICNETWORKCONTROLER_H
