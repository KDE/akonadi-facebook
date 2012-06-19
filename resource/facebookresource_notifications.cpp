/* Copyright 2012 Martin Klapetek <martin.klapetek@gmail.com>

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
#include "timestampattribute.h"

#include <libkfacebook/postjob.h>
#include <libkfacebook/notificationslistjob.h>
#include <libkfacebook/notificationinfo.h>

#include <Akonadi/AttributeFactory>
#include <Akonadi/EntityDisplayAttribute>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <KLocalizedString>
#include <akonadi/changerecorder.h>


using namespace Akonadi;

void FacebookResource::notificationsListFetched( KJob *job ) {
    Q_ASSERT( !mIdle );
    NotificationsListJob * const listJob = dynamic_cast<NotificationsListJob*>( job );
    Q_ASSERT( listJob );
    mCurrentJobs.removeAll(job);

    if ( listJob->error() ) {
        abortWithError( i18n( "Unable to get notifications from server: %1", listJob->errorString() ),
                        listJob->error() == FacebookJob::AuthenticationProblem );
    } else {
        setItemStreamingEnabled( true );

        Item::List notificationItems;
        kDebug() << "Going into foreach";
        foreach( const NotificationInfoPtr &notificationInfo, listJob->notifications() ) {
          Item notification;
          notification.setRemoteId( notificationInfo.data()->id() );
          notification.setMimeType( "text/x-vnd.akonadi.socialnotification" );
          notification.setPayload<NotificationInfoPtr>( notificationInfo );
          notificationItems.append(notification);;
        }

        itemsRetrieved( notificationItems );
        itemsRetrievalDone();
        finishPostsFetching();
    }

}

void FacebookResource::finishNotificationsFetching()
{
    emit percent(100);
    emit status( Idle, i18n( "All notifications fetched from server." ) );
    resetState();
}