#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDmxManager.h>

class TestDmxLib : public QObject
{
    Q_OBJECT

public:
    TestDmxLib();

private Q_SLOTS:
    void initTestCase();
    void refreshPlugins();
    void testPatch();
};

TestDmxLib::TestDmxLib()
{

}

void TestDmxLib::initTestCase()
{
    QDmxManager::instance()->setPlugDir("/Users/nicolas/Programmation/plugin/");
    qDebug() << QCoreApplication::libraryPaths();
}

void TestDmxLib::refreshPlugins()
{
    QDmxManager::instance()->refreshActivePlugins();
    QStringList test;
    test << "libartnet";
    QVERIFY(QDmxManager::instance()->getPlugList() == test);
}

void TestDmxLib::testPatch()
{
    QStringList l = QDmxManager::instance()->getDevices("libartnet");
    qDebug() << l;
    QVERIFY(l.contains("192.168.0.100"));
    qDebug() << QDmxManager::instance()->getInputPortCount("libartnet", 1);
    QVERIFY(QDmxManager::instance()->patch(0, "libartnet", l.indexOf("192.168.0.100"), 0, "libartnet", l.indexOf("192.168.0.100"), 0));
}

QTEST_MAIN(TestDmxLib)

#include "tst_TestDmxLib.moc"
