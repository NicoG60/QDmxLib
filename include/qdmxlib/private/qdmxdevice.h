#ifndef QDMXDEVICE_H
#define QDMXDEVICE_H

#include <QObject>

class QDmxDriver;
class QDmxManager;
class QDmxDevicePrivate;
class Q_DECL_EXPORT QDmxDevice : public QObject
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(QDmxDevice)

    friend class QDmxDriver;
    friend class QDmxManager;

public:
    QDmxDevice(QDmxDriver* parent = nullptr);
    ~QDmxDevice() override = default;

    virtual QString name() const { return "dummy"; }

    QDmxDriver* driver() const;
    QDmxManager* manager() const;

    bool isStarted() const;

    quint8 inputCount() const;
    quint8 outputCount() const;

    virtual QByteArray readInputData(quint8 port);
    virtual QByteArray readOutputData(quint8 port);

protected slots:
    bool start();
    bool stop();

    virtual void setData(quint8 port, quint16 channel, quint8 data);
    virtual void setData(quint8 port, quint16 channel, const QByteArray& data);
    virtual void setData(quint8 port, const QByteArray& data);

signals:
    void inputDataChanged(quint8 port, const QByteArray& data);
    void startedChanged(bool started);

protected:
    QDmxDevice(QDmxDevicePrivate& d, QDmxDriver* parent);

    virtual bool startHook() { return true; }
    virtual bool stopHook() { return true; }
};

class QDmxDummyDevicePrivate;
class QDmxDummyDevice : public QDmxDevice
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(QDmxDummyDevice)

public:
    QDmxDummyDevice(QDmxDriver* parent = nullptr);
};

#endif // QDMXDEVICE_H
