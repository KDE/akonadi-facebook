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
#include "facebookdeletejob.h"

#include <qjson/parser.h>

#include <KIO/Job>
#include <KDebug>
#include <KLocale>

FacebookDeleteJob::FacebookDeleteJob( const QString& id, const QString& accessToken )
  : mAccessToken( accessToken ),
    mId( id )
{
  setCapabilities(KJob::Killable);
}

bool FacebookDeleteJob::doKill()
{
  if (mJob) {
    mJob->kill(KJob::Quietly);
  }
  return KJob::doKill();
}

void FacebookDeleteJob::start()
{
  KUrl url;
  url.setProtocol("https");
  url.setHost("graph.facebook.com");
  url.setPath("/" + mId);

  url.addQueryItem("access_token", mAccessToken);
  url.addQueryItem("method", "delete");

  kDebug() << "Starting delete: " << url;
  KIO::StoredTransferJob * const job = KIO::storedHttpPost( QByteArray(), url, KIO::HideProgressInfo );
  mJob = job;
  connect( job, SIGNAL(result(KJob*)), this, SLOT(deleteJobFinished(KJob*)) );
  job->start();
}

void FacebookDeleteJob::deleteJobFinished( KJob *job )
{
  KIO::StoredTransferJob *deleteJob = dynamic_cast<KIO::StoredTransferJob *>( job );
  Q_ASSERT( deleteJob );
  if ( deleteJob->error() ) { 
    setError( deleteJob->error() );
    setErrorText( KIO::buildErrorString( error(), deleteJob->errorText() ) );
    kWarning() << "Job error: " << deleteJob->errorString();
  } else {
    kDebug() << "Got data: " << QString::fromAscii( deleteJob->data().data() );
  }

  emitResult();
  mJob = 0;
}

#include "facebookdeletejob.moc"
