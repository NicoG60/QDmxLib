#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDmxLib.h>

class TestDmxLib : public QObject
{
    Q_OBJECT

public:
    TestDmxLib();

private Q_SLOTS:
    void testCase1();

private:
    QDmxLib lib;
};

TestDmxLib::TestDmxLib()
{
    lib.setPlugDir("/Users/nicolas/Programmation/plugin/");
}

void TestDmxLib::testCase1()
{
    lib.refreshActivePlugins();
}

QTEST_MAIN(TestDmxLib)

#include "tst_TestDmxLib.moc"
