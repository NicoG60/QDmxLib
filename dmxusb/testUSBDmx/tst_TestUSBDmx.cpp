#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <QDmxIO.h>

class TestUSBDmx : public QObject
{
    Q_OBJECT

public:
    TestUSBDmx();

private Q_SLOTS:
    void initTestCase();

    void testLoad();
    void testInit();
    void testName();
    void testDevice();

    void testInputCountAndExist();
    void testOpenInput();
    void testDmxInput();
    void closeInput();

    void testOutputCountAndExist();
    void testOpenOutput();
    void testDmxOutput();
    void closeOutput();

    void cleanupTestCase();


private:
    QDmxIO* plug;
    quint32 id;
};

TestUSBDmx::TestUSBDmx()
{
    plug = 0;
}

void TestUSBDmx::initTestCase()
{
#ifdef Q_OS_WIN
    QCoreApplication::addLibraryPath("E:/Prog/plugin");
#else
    QCoreApplication::addLibraryPath("/Users/nicolas/Programmation/plugin/");
#endif
}

void TestUSBDmx::testLoad()
{
#ifdef Q_OS_WIN
    QPluginLoader loader("QDmxUsb");
#else
    QPluginLoader loader("libQDmxUsb");
#endif
    if(!loader.load())
    {
        qDebug() << loader.errorString();
        QFAIL("not loaded");
    }
    plug = qobject_cast<QDmxIO*>(loader.instance());
    QVERIFY(plug);
}

void TestUSBDmx::testInit()
{
    if(plug)
    {
        plug->init();
        QString error = plug->errorString();
        QVERIFY2(error.isEmpty(), "init error");
    }
    else
        QSKIP("plug is not loaded");
}

void TestUSBDmx::testName()
{
    if(plug)
        QCOMPARE(plug->name(), QString("Dmx USB"));
    else
        QSKIP("plug is not loaded");
}

void TestUSBDmx::testDevice()
{
    /*if(plug)
    {
        QVERIFY2(plug->getDevices().size() > 0, "there is no device");
        QVERIFY2(plug->deviceExists(0), "the ethernet interface is not connected");
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::testInputCountAndExist()
{
    /*if(plug)
    {
        QVERIFY(plug->getInputCount(0) == 255);
        QVERIFY(plug->inputExists(0, 0));
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::testOpenInput()
{
    /*if(plug)
    {
        QVERIFY(plug->openInput(0, 0));
        QVERIFY(plug->inputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::testDmxInput()
{
    /*if(plug)
    {
        QSignalSpy spy(plug, SIGNAL(dmxInput(int,int,QByteArray)));
        QVERIFY(spy.wait());

        QList<QVariant> args = spy.takeFirst();
        QVERIFY(args.at(0).type() == QVariant::Int);
        QVERIFY(args.at(1).type() == QVariant::Int);
        QVERIFY(args.at(2).type() == QVariant::ByteArray);
        qDebug() << args.at(0).toInt() << args.at(1).toInt();
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::closeInput()
{
    /*if(plug)
    {
        if(!plug->closeInput(0, 0))
        {
            qDebug() << plug->errorString();
            QFAIL("failed");
        }
        QVERIFY(!plug->inputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::testOutputCountAndExist()
{
    /*if(plug)
    {
        QVERIFY(plug->getOutputCount(0) == 255);
        QVERIFY(plug->outputExists(0, 0));
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::testOpenOutput()
{
    /*if(plug)
    {
        QVERIFY(plug->openOutput(0, 0));
        QVERIFY(plug->outputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::testDmxOutput()
{
    /*if(plug)
    {
        qDebug() << "output...";
        for(int i = 0; i < 10; i++)
        {
            QByteArray data;
            data.resize(512);

            qDebug() << i;
            plug->writeDmx(0, 0, data);
            QTest::qWait(500);
        }
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::closeOutput()
{
    /*if(plug)
    {
        if(!plug->closeOutput(0, 0))
        {
            qDebug() << plug->errorString();
            QSKIP("failed");
        }
        QVERIFY(!plug->outputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");*/
}

void TestUSBDmx::cleanupTestCase()
{
}



QTEST_MAIN(TestUSBDmx)

#include "tst_TestUSBDmx.moc"
