#include "QsLog.h"
#include "QsLogDest.h"
#include <QtCore/QCoreApplication>
#include <QDir>

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   // init the logging mechanism
   QsLogging::Logger& logger = QsLogging::Logger::instance();
   logger.setLoggingLevel(QsLogging::TraceLevel);
   const QString sLogPath(QDir(a.applicationDirPath()).filePath("qslog.txt"));
   QsLogging::DestinationPtr fileDestination(
      QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
   QsLogging::DestinationPtr debugDestination(
      QsLogging::DestinationFactory::MakeDebugOutputDestination() );
   logger.addDestination(debugDestination.get());
   logger.addDestination(fileDestination.get());

   QLOG_INFO() << "Program started";
   QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on" << qVersion();

   QLOG_TRACE() << "Here's a" << QString("trace") << "message";
   QLOG_DEBUG() << "Here's a" << static_cast<int>(QsLogging::DebugLevel) << "message";
   QLOG_WARN()  << "Uh-oh!";
   QLOG_ERROR() << "An error has occurred";
   QLOG_FATAL() << "Fatal error!";

   const int ret = 0; //a.exec();
   QLOG_INFO() << "Program exited with return code" << ret;
   return ret;
}
