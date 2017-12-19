#ifndef QDMXIO_H
#define QDMXIO_H

#include <QObject>
#include <QMultiHash>

class QDmxIO : public QObject
{
    Q_OBJECT

public:
    QDmxIO(QObject* parent = 0);
    virtual ~QDmxIO() {}

    //===== GENERAL
    virtual void init();
    virtual QString name();
    QString errorString() { return _lastError; }

    //===== DEVICE
    virtual QStringList getDevices();

    //===== INPUTS
    virtual int getInputCount(QString device);
    virtual int getInputCount(int device);
    virtual bool openInput(QString device, int port);
    virtual bool openInput(int device, int port);
    virtual bool closeInput(QString device, int port);
    virtual bool closeInput(int device, int port);

    bool inputIsOpened(int device, int port);

signals:
    void dmxInput(int device, int port, QByteArray data);

    //===== OUTPUTS
public:
    virtual int getOutputCount(QString device);
    virtual int getOutputCount(int device);
    virtual bool openOutput(QString device, int port);
    virtual bool openOutput(int device, int port);
    virtual bool closeOutput(QString device, int port);
    virtual bool closeOutput(int device, int port);

    bool outputIsOpened(int device, int port);

public slots:
    virtual void writeDmx(int device, int port, QByteArray data);

protected:
    QMultiHash<int,int> _openedInput;
    QMultiHash<int,int> _openedOutput;
    QString _lastError;
};

#define QDmxPlugin_iid "org.qdmxlib.QDmxIO"

Q_DECLARE_INTERFACE(QDmxIO, QDmxPlugin_iid)

#endif // QDMXIO_H
