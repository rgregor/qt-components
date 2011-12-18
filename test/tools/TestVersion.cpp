#include "QtTestUtil/QtTestUtil.h"
#include "QsVersion.h"
#include <QtGlobal>

class TestVersion : public QObject
{
    Q_OBJECT
public:
    TestVersion();
private slots:
    void initTestCase();
    void testValid();
    void testIntegerInit();
    void testStringInit();
    void testLessThan_data();
    void testLessThan();
    void testGreaterThan_data();
    void testGreaterThan();
    void testCompare();
    void testToString();
};

TestVersion::TestVersion()
{

}

void TestVersion::initTestCase()
{

}

void TestVersion::testValid()
{
    const QsVersion v;
    QCOMPARE(v.isValid(), false);
}

void TestVersion::testIntegerInit()
{
    QsVersion v1(1,0,0);
    QVERIFY(v1.isValid());
    QCOMPARE(v1.majorVersion(), 1);
    QCOMPARE(v1.minorVersion(), 0);
    QCOMPARE(v1.releaseVersion(), 0);
}

void TestVersion::testStringInit()
{
    QsVersion v2("2.1.3");
    QVERIFY(v2.isValid());
    QCOMPARE(v2.majorVersion(), 2);
    QCOMPARE(v2.minorVersion(), 1);
    QCOMPARE(v2.releaseVersion(), 3);
}

void TestVersion::testLessThan_data()
{
    QTest::addColumn<int>("major1");
    QTest::addColumn<int>("minor1");
    QTest::addColumn<int>("release1");
    QTest::addColumn<int>("major2");
    QTest::addColumn<int>("minor2");
    QTest::addColumn<int>("release2");

    QTest::newRow("majors") << 1 << 0 << 0
                            << 2 << 0 << 0;
    QTest::newRow("minors") << 1 << 2 << 4
                            << 1 << 5 << 4;
    QTest::newRow("release") << 1 << 1 << 8
                             << 1 << 1 << 9;
    QTest::newRow("mixed 1") << 1 << 1 << 15
                             << 1 << 2 << 80;
    QTest::newRow("mixed 2") << 1 << 1 << 15
                             << 2 << 0 << 0;
}

void TestVersion::testLessThan()
{
    QFETCH(int, major1);
    QFETCH(int, minor1);
    QFETCH(int, release1);
    QFETCH(int, major2);
    QFETCH(int, minor2);
    QFETCH(int, release2);

    QsVersion v1(major1,minor1,release1);
    QsVersion v2(major2,minor2,release2);

    QVERIFY(v1 < v2);
}

void TestVersion::testGreaterThan_data()
{
    testLessThan_data();
}

void TestVersion::testGreaterThan()
{
    QFETCH(int, major1);
    QFETCH(int, minor1);
    QFETCH(int, release1);
    QFETCH(int, major2);
    QFETCH(int, minor2);
    QFETCH(int, release2);

    QsVersion v1(major1,minor1,release1);
    QsVersion v2(major2,minor2,release2);

    QVERIFY(v2 > v1);
}

void TestVersion::testCompare()
{
    const QsVersion v1(1,4,3);
    const QsVersion v2("1.4.3");

    QCOMPARE(v1,v2);
}

void TestVersion::testToString()
{
    const QsVersion v2(1,2,8);
    QCOMPARE(v2.toString(), QString("1.2.8"));
}

QTTESTUTIL_REGISTER_TEST(TestVersion);
#include "TestVersion.moc"
