#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <QDmxIO.h>

class TestE131 : public QObject
{
    Q_OBJECT

public:
    TestE131();

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
};

TestE131::TestE131()
{
    plug = 0;
}

void TestE131::initTestCase()
{
    QCoreApplication::addLibraryPath("/Users/nicolas/Programmation/plugin/");
}

void TestE131::testLoad()
{
    QPluginLoader loader("libQDmxE131");
    QVERIFY(loader.load());
    plug = qobject_cast<QDmxIO*>(loader.instance());
    QVERIFY(plug);
}

void TestE131::testInit()
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

void TestE131::testName()
{
    if(plug)
        QCOMPARE(plug->name(), QString("E1.31 - sACN"));
    else
        QSKIP("plug is not loaded");
}

void TestE131::testDevice()
{
    if(plug)
    {
        QVERIFY2(plug->getDevices().size() > 0, "there is no device");
        QVERIFY2(plug->deviceExists(0), "the ethernet interface is not connected");
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::testInputCountAndExist()
{
    if(plug)
    {
        QVERIFY(plug->getInputCount(0) == 4);
        QVERIFY(plug->inputExists(0, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::testOpenInput()
{
    if(plug)
    {
        QVERIFY(plug->openInput(0, 0));
        QVERIFY(plug->inputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::testDmxInput()
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

void TestE131::closeInput()
{
    if(plug)
    {
        if(!plug->closeInput(0, 0))
        {
            qDebug() << plug->errorString();
            QFAIL("failed");
        }
        QVERIFY(!plug->inputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::testOutputCountAndExist()
{
    if(plug)
    {
        QVERIFY(plug->getOutputCount(0) == 4);
        QVERIFY(plug->outputExists(0, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::testOpenOutput()
{
    if(plug)
    {
        QVERIFY(plug->openOutput(0, 0));
        QVERIFY(plug->outputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::testDmxOutput()
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

void TestE131::closeOutput()
{
    if(plug)
    {
        if(!plug->closeOutput(0, 0))
        {
            qDebug() << plug->errorString();
            QSKIP("failed");
        }
        QVERIFY(!plug->outputIsOpened(0, 0));
    }
    else
        QSKIP("plug is not loaded");
}

void TestE131::cleanupTestCase()
{
}



QTEST_MAIN(TestE131)

#include "tst_TestE131.moc"
