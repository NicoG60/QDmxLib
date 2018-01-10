#ifndef QDMXFTD2XXINTERFACE_H
#define QDMXFTD2XXINTERFACE_H

#include "../QDmxUsbInterface.h"
#include <ftd2xx.h>

class QDmxFTD2XXInterface : public QDmxUsbInterface
{
public:
    QDmxFTD2XXInterface(const QString& serial, const QString& name, const QString &vendor, quint16 VID, quint16 PID, quint32 id = 0);
    ~QDmxFTD2XXInterface();

    static QList<QDmxUsbInterface*> interfaces();

    virtual QDmxUsbInterface::Type type() { return QDmxUsbInterface::libFTDI; }

    virtual QString typeString() { return QString("FTD2XX"); }

    virtual bool open();
    virtual bool openByPID(const int FTDIPID);
    virtual bool close();
    virtual bool isOpen() const;
    virtual bool reset();
    virtual bool setLineProperties();
    virtual bool setBaudRate();
    virtual bool setFlowControl();
    virtual bool clearRts();
    virtual bool purgeBuffers();
    virtual bool setBreak(bool on);
    virtual bool write(const QByteArray& data);
    virtual QByteArray read(int size, uchar* buffer = NULL);
    virtual uchar readByte(bool* ok = NULL);

private:
    static QString errorString(FT_STATUS status);
    static FT_STATUS getInterfaceInfo(DWORD deviceIndex, QString& vendor, QString& description, QString& serial, quint16 &VID, quint16 &PID);

private:
    FT_STATUS _status;
    FT_HANDLE _handle;
};

#endif // QDMXFTD2XXINTERFACE_H
