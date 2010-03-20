// Copyright (c) 2010, Razvan Petru
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice, this
//   list of conditions and the following disclaimer in the documentation and/or other
//   materials provided with the distribution.
// * The name of the contributors may not be used to endorse or promote products
//   derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef QSLOG_H
#define QSLOG_H

#include <QtDebug>
class QString;

namespace QsLogging
{
class Destination;
enum Level
{
   TraceLevel,
   DebugLevel,
   InfoLevel,
   WarnLevel,
   ErrorLevel,
   FatalLevel
};

class LoggerImpl;
class Logger
{
public:
   static Logger& instance();
   //! adds a message destination
   void addDestination(Destination* destination);
   //! logging at a level < 'level' will not be taken into consideration
   void setLoggingLevel(Level newLevel);
   //! the default level is INFO
   Level loggingLevel() const;

private:
   Logger();
   Logger(const Logger&);
   ~Logger();
   Logger& operator=(const Logger&);

   void write(const QString& message);
   static void messageHandler(QtMsgType qtType, const char* message);

   LoggerImpl* d;
};

struct detail
{
   static const char traceMessage;
   static const char debugMessage;
   static const char infoMessage;
   static const char warnMessage;
   static const char errorMessage;
   static const char fatalMessage;
};

} // end namespace

//! Logging macros: define QS_LOG_LINE_NUMBERS to get the file and line number
//! in the log output.
#ifndef QS_LOG_LINE_NUMBERS
   #define QLOG_TRACE() \
   if( QsLogging::Logger::instance().loggingLevel() > QsLogging::TraceLevel ); \
      else qCritical() << QsLogging::detail::traceMessage
   #define QLOG_DEBUG() \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::DebugLevel ); \
      else qCritical() << QsLogging::detail::debugMessage
   #define QLOG_INFO()  \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::InfoLevel ); \
      else qCritical() << QsLogging::detail::infoMessage
   #define QLOG_WARN()  \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::WarnLevel ); \
      else qCritical() << QsLogging::detail::warnMessage
   #define QLOG_ERROR() \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::ErrorLevel ); \
      else qCritical() << QsLogging::detail::errorMessage
   #define QLOG_FATAL() qCritical() << QsLogging::detail::fatalMessage
#else
   #define QLOG_TRACE() \
   if( QsLogging::Logger::instance().loggingLevel() > QsLogging::TraceLevel ); \
      else qDebug() << QsLogging::detail::traceMessage << __FILE__ << '@' << __LINE__
   #define QLOG_DEBUG() \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::DebugLevel ); \
      else qDebug() << QsLogging::detail::debugMessage << __FILE__ << '@' << __LINE__
   #define QLOG_INFO()  \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::InfoLevel ); \
      else qDebug() << QsLogging::detail::infoMessage << __FILE__) << '@' << __LINE__
   #define QLOG_WARN()  \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::WarnLevel ); \
      else qWarning() << QsLogging::detail::warnMessage << __FILE__ << '@' << __LINE__
   #define QLOG_ERROR() \
      if( QsLogging::Logger::instance().loggingLevel() > QsLogging::ErrorLevel ); \
      else qCritical() << QsLogging::detail::errorMessage << __FILE__ << '@' << __LINE__
   #define QLOG_FATAL() qCritical() << QsLogging::detail::fatalMessage << __FILE__ << '@' << __LINE__
#endif

#endif // QSLOG_H
