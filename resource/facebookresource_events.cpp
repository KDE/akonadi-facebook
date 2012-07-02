/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>
   Copyright 2011 Roeland Jago Douma <unix@rullzer.com>

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
#include "facebookresource.h"
#include <config.h>
#include "settings.h"
#include "settingsdialog.h"
#include "timestampattribute.h"

#include <libkfacebook/alleventslistjob.h>
#include <libkfacebook/eventjob.h>

#include <Akonadi/AttributeFactory>
#include <Akonadi/EntityDisplayAttribute>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ChangeRecorder>

using namespace Akonadi;

static const char * eventMimeType = "application/x-vnd.akonadi.calendar.event";

void FacebookResource::eventListFetched( KJob* job )
{
  Q_ASSERT( !mIdle );
  Q_ASSERT( mCurrentJobs.indexOf(job) != -1 );
  KFacebook::AllEventsListJob * const listJob = dynamic_cast<KFacebook::AllEventsListJob*>( job );
  Q_ASSERT( listJob );
  mCurrentJobs.removeAll(job);

  if ( listJob->error() ) {
    abortWithError( i18n( "Unable to get events from server: %1", listJob->errorString() ),
                    listJob->error() == KFacebook::FacebookJob::AuthenticationProblem );
  } else {
    QStringList eventIds;
    foreach( const KFacebook::EventInfoPtr &event, listJob->allEvents() ) {
      eventIds.append( event->id() );
    }
    if ( eventIds.isEmpty() ) {
      itemsRetrievalDone();
      finishEventsFetching();
      return;
    }
    KFacebook::EventJob * const eventJob = new KFacebook::EventJob( eventIds, Settings::self()->accessToken() );
    mCurrentJobs << eventJob;
    connect( eventJob, SIGNAL(result(KJob*)), this, SLOT(detailedEventListJobFinished(KJob*)) );
    eventJob->start();
  }
}

void FacebookResource::detailedEventListJobFinished( KJob* job )
{
  Q_ASSERT( !mIdle );
  Q_ASSERT( mCurrentJobs.indexOf(job) != -1 );
  KFacebook::EventJob * const eventJob = dynamic_cast<KFacebook::EventJob*>( job );
  Q_ASSERT( eventJob );
  mCurrentJobs.removeAll(job);

  if ( job->error() ) {
    abortWithError( i18n( "Unable to get list of events from server: %1", eventJob->errorText() ) );
  } else {
    setItemStreamingEnabled( true );

    Item::List eventItems;
    foreach ( const KFacebook::EventInfoPtr &eventInfo, eventJob->eventInfo() ) {
      Item event;
      event.setRemoteId( eventInfo->id() );
      event.setPayload<IncidencePtr>( eventInfo->asEvent() );
      event.setMimeType( eventMimeType );
      eventItems.append( event );
    }
    itemsRetrieved( eventItems );
    itemsRetrievalDone();
    finishEventsFetching();
  }
}

void FacebookResource::finishEventsFetching()
{
  emit percent(100);
  // TODO: Use an actual number here
  emit status( Idle, i18n( "All events fetched from server." ) );
  resetState();
}

