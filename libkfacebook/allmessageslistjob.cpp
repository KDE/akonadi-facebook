/* Copyright 2011 Roeland Jago Douma <unix@rullzer.com>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   ( at your option ) version 3 or, at the discretion of KDE e.V.
   ( which shall act as a proxy as in section 14 of the GPLv3 ), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#include "allmessageslistjob.h"

#include "messageslistjob.h"

#include <KDebug>
#include <KUrl>

AllMessagesListJob::AllMessagesListJob( const QString& accessToken )
  : mAccessToken( accessToken )
{
}

QList< MessageInfoPtr > AllMessagesListJob::allMessages() const
{
  return mMessages;
}

bool AllMessagesListJob::doKill()
{
  if (mCurrentJob) {
    mCurrentJob->kill( KJob::Quietly );
  }
  return KJob::doKill();
}

void AllMessagesListJob::setLowerLimit( const KDateTime& lowerLimit )
{
  mLowerLimit = lowerLimit;
}

void AllMessagesListJob::start()
{
  Q_ASSERT( mLowerLimit.isValid() );
  Q_ASSERT( !mCurrentJob );
  mCurrentJob = new MessagesListJob( mAccessToken );

  mCurrentJob->addQueryItem("limit", "0");
  mCurrentJob->addQueryItem("since", QString::number( mLowerLimit.toTime_t() ));

  connect( mCurrentJob, SIGNAL(result(KJob*)),
           this, SLOT(messagesListJobFinished(KJob*)) );
  mCurrentJob->start();
}

void AllMessagesListJob::messagesListJobFinished( KJob* job )
{
  Q_ASSERT( job == mCurrentJob );
  MessagesListJob * const listJob = dynamic_cast<MessagesListJob*>( job );
  Q_ASSERT( listJob );
  if ( job->error() ) {
    setError( listJob->error() );
    setErrorText( listJob->errorString() );
    emitResult();
  } else {
    kDebug() << "Got" << listJob->messages().size() << "messages from our subjob.";
    mMessages.append( listJob->messages() );
    mCurrentJob = 0;
    emitResult();
  }
}
