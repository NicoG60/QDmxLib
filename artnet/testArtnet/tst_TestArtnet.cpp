#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <QDmxIO.h>

class TestArtnet : public QObject
{
    Q_OBJECT

public:
    TestArtnet();

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

TestArtnet::TestArtnet()
{
    plug = 0;
}

void TestArtnet::initTestCase()
{
#ifdef Q_OS_WIN
    QCoreApplication::addLibraryPath("E:/Prog/plugin");
#else
    QCoreApplication::addLibraryPath("/Users/nicolas/Programmation/plugin/");
#endif
}

void TestArtnet::testLoad()
{
    QPluginLoader loader("libQDmxArtnet");
    QVERIFY(loader.load());
    plug = qobject_cast<QDmxIO*>(loader.instance());
    QVERIFY(plug);
}

void TestArtnet::testInit()
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

void TestArtnet::testName()
{
    if(plug)
        QCOMPARE(plug->name(), QString("Art-Net"));
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testDevice()
{
    if(plug)
    {
        QVERIFY2(plug->getDevices().size() > 0, "there is no device");
        id = plug->getDevices().keys().first();
        QVERIFY2(plug->deviceExists(id), "the ethernet interface is not connected");
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testInputCountAndExist()
{
    if(plug)
    {
        QCOMPARE((int)plug->getInputCount(id), 4);
        QVERIFY(plug->inputExists(id, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testOpenInput()
{
    if(plug)
    {
        QVERIFY(plug->openInput(id, 0));
        QVERIFY(plug->inputIsOpened(id, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testDmxInput()
{
    if(plug)
    {
        QSignalSpy spy(plug, SIGNAL(dmxInput(quint32,quint32,QByteArray)));
        QVERIFY(spy.wait());

        QList<QVariant> args = spy.takeFirst();
        QVERIFY(args.at(0).type() == QVariant::UInt);
        QVERIFY(args.at(1).type() == QVariant::UInt);
        QVERIFY(args.at(2).type() == QVariant::ByteArray);
        qDebug() << args.at(0).toInt() << args.at(1).toInt();
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::closeInput()
{
    if(plug)
    {
        if(!plug->closeInput(id, 0))
        {
            qDebug() << plug->errorString();
            QFAIL("failed");
        }
        QVERIFY(!plug->inputIsOpened(id, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testOutputCountAndExist()
{
    if(plug)
    {
        QCOMPARE((int)plug->getOutputCount(id), 4);
        QVERIFY(plug->outputExists(id, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testOpenOutput()
{
    if(plug)
    {
        QVERIFY(plug->openOutput(id, 0));
        QVERIFY(plug->outputIsOpened(id, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::testDmxOutput()
{
    if(plug)
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
        QSKIP("plug is not loaded");
}

void TestArtnet::closeOutput()
{
    if(plug)
    {
        if(!plug->closeOutput(id, 0))
        {
            qDebug() << plug->errorString();
            QSKIP("failed");
        }
        QVERIFY(!plug->outputIsOpened(id, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestArtnet::cleanupTestCase()
{
}



QTEST_MAIN(TestArtnet)

#include "tst_TestArtnet.moc"
