#include "QtTestUtil/QtTestUtil.h"
#include "QsLog.h"
#include "QsLogDest.h"
#include <QHash>
#include <QtGlobal>

// A destination that tracks log messages
class MockDestination : public QsLogging::Destination
{
public:
    virtual void write(const QString &message, QsLogging::Level level)
    {
        Message m;
        m.text = message;
        m.level = level;
        mMessages.push_back(m);
        ++mCountByLevel[level];
    }

    void clear()
    {
        mMessages.clear();
        mCountByLevel.clear();
    }

    int messageCount() const
    {
        return mMessages.count();
    }

    int messageCountForLevel(QsLogging::Level level) const
    {
        return mCountByLevel.value(level);
    }

    bool hasMessage(const QString &messageContent, QsLogging::Level level) const
    {
        Q_FOREACH (const Message &m, mMessages) {
            if (m.level == level && m.text.contains(messageContent))
                return true;
        }

        return false;
    }

private:
    struct Message
    {
        Message() : level(QsLogging::TraceLevel) {}
        QString text;
        QsLogging::Level level;
    };

    QHash<QsLogging::Level,int> mCountByLevel;
    QList<Message> mMessages;
};

// Autotests for QsLog
class TestLog : public QObject
{
    Q_OBJECT
public:
    TestLog()
        : mockDest1(new MockDestination)
        , mockDest2(new MockDestination)
    {
    }

private slots:
    void initTestCase();
    void testAllLevels();
    void testMessageText();
    void testLevelChanges();

private:
    QScopedPointer<MockDestination> mockDest1;
    QScopedPointer<MockDestination> mockDest2;
};

void TestLog::initTestCase()
{
    using namespace QsLogging;
    QCOMPARE(Logger::instance().loggingLevel(), InfoLevel);
    Logger::instance().setLoggingLevel(TraceLevel);
    QCOMPARE(Logger::instance().loggingLevel(), TraceLevel);
    Logger::instance().addDestination(mockDest1.data());
    Logger::instance().addDestination(mockDest2.data());
}

void TestLog::testAllLevels()
{
    mockDest1->clear();
    mockDest2->clear();

    QLOG_TRACE() << "trace level";
    QLOG_DEBUG() << "debug level";
    QLOG_INFO() << "info level";
    QLOG_WARN() << "warn level";
    QLOG_ERROR() << "error level";
    QLOG_FATAL() << "fatal level";

    using namespace QsLogging;
    QCOMPARE(mockDest1->messageCount(), 6);
    QCOMPARE(mockDest1->messageCountForLevel(TraceLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(DebugLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(InfoLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(WarnLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(ErrorLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(FatalLevel), 1);
    QCOMPARE(mockDest2->messageCount(), 6);
    QCOMPARE(mockDest2->messageCountForLevel(TraceLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(DebugLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(InfoLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(WarnLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(ErrorLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(FatalLevel), 1);
}

void TestLog::testMessageText()
{
    mockDest1->clear();

    QLOG_DEBUG() << "foobar";
    QLOG_WARN() << "eiszeit";
    QLOG_FATAL() << "ruh-roh!";
    using namespace QsLogging;
    QVERIFY(mockDest1->hasMessage("foobar", DebugLevel));
    QVERIFY(mockDest1->hasMessage("eiszeit", WarnLevel));
    QVERIFY(mockDest1->hasMessage("ruh-roh!", FatalLevel));
    QCOMPARE(mockDest1->messageCount(), 3);
}

void TestLog::testLevelChanges()
{
    mockDest1->clear();
    mockDest2->clear();

    using namespace QsLogging;
    Logger::instance().setLoggingLevel(WarnLevel);
    QCOMPARE(Logger::instance().loggingLevel(), WarnLevel);

    QLOG_TRACE() << "one";
    QLOG_DEBUG() << "two";
    QLOG_INFO() << "three";
    QCOMPARE(mockDest1->messageCount(), 0);
    QCOMPARE(mockDest2->messageCount(), 0);

    QLOG_WARN() << "warning";
    QLOG_ERROR() << "error";
    QLOG_FATAL() << "fatal";
    QCOMPARE(mockDest1->messageCountForLevel(WarnLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(ErrorLevel), 1);
    QCOMPARE(mockDest1->messageCountForLevel(FatalLevel), 1);
    QCOMPARE(mockDest1->messageCount(), 3);
    QCOMPARE(mockDest2->messageCountForLevel(WarnLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(ErrorLevel), 1);
    QCOMPARE(mockDest2->messageCountForLevel(FatalLevel), 1);
    QCOMPARE(mockDest2->messageCount(), 3);
}

QTTESTUTIL_REGISTER_TEST(TestLog);
#include "TestLog.moc"
