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

#include "QsLog.h"
#include "QsLogDest.h"
#include <QMutex>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QtGlobal>

namespace QsLogging
{
typedef QList<Destination*> DestinationList;

const char detail::traceMessage = '0';
const char detail::debugMessage = '1';
const char detail::infoMessage = '2';
const char detail::warnMessage = '3';
const char detail::errorMessage = '4';
const char detail::fatalMessage = '5';

static const char TraceString[] = "TRACE";
static const char DebugString[] = "DEBUG";
static const char InfoString[]  = "INFO";
static const char WarnString[]  = "WARN";
static const char ErrorString[] = "ERROR";
static const char FatalString[] = "FATAL";

static const QString fmtDateTime("yyyy-MM-ddThh:mm:ss.zzz");

static const char* LevelToText(char aLevel)
{
   switch( aLevel )
   {
   case detail::traceMessage:
      return TraceString;
   case detail::debugMessage:
      return DebugString;
   case detail::infoMessage:
      return InfoString;
   case detail::warnMessage:
      return WarnString;
   case detail::errorMessage:
      return ErrorString;
   case detail::fatalMessage:
      return FatalString;
   default:
      return InfoString;
   }
}

class LoggerImpl
{
public:
   LoggerImpl() :
      mOldHandler(0),
      mLevel(InfoLevel)
   {

   }
   QMutex logMutex;
   QtMsgHandler mOldHandler;
   Level mLevel;
   DestinationList mDestList;
};

Logger::Logger() :
   d(new LoggerImpl)
{
}

Logger::~Logger()
{
   delete d;
}

Logger& Logger::instance()
{
   static Logger staticLog;
   return staticLog;
}

//! Only install the handler if someone has added at least a destination to 
//! our log. 
void Logger::addDestination(Destination* destination)
{
   if( !d->mOldHandler )
      d->mOldHandler = qInstallMsgHandler(&Logger::messageHandler);
   d->mDestList.push_back(destination);
}

void Logger::setLoggingLevel(Level newLevel)
{
   d->mLevel = newLevel;
}

Level Logger::loggingLevel() const
{
   return d->mLevel;
}

//! sends the message to all the destinations
void Logger::write(const QString& message)
{
   for(DestinationList::iterator it = d->mDestList.begin(),
       endIt = d->mDestList.end();it != endIt;++it)
   {
      (*it)->write(message);
   }
}

//! the first character of the message is the message type
//! The qt message type is ignored.
//! Do not call any qt functions from this function, it may cause an infinite loop!
void Logger::messageHandler(QtMsgType qtType, const char* message)
{
   Q_UNUSED(qtType);
   if( !message )
      return;

   Logger& logger = Logger::instance();
   const char msgType = message[0];
   const char* const msg = 
      (msgType >= detail::traceMessage
      && msgType <= detail::fatalMessage ? message + 1 : message);
   const char* const levelName = LevelToText(msgType);

   const QString sCompleteMessage(QString("%1 %2 %3")
      .arg(levelName, 5)
      .arg(QDateTime::currentDateTime().toString(fmtDateTime))
      .arg(msg)
      );

   QMutexLocker lock(&logger.d->logMutex);
   logger.write(sCompleteMessage);
}

} // end namespace
