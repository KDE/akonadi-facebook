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


#include "notificationslistjob.h"

#include <KDebug>

using namespace KFacebook;

NotificationsListJob::NotificationsListJob( const QString &accessToken )
: ListJobBase("/me/notifications", accessToken)
{
    // Fetch also read notification
    addQueryItem("include_read", "1");
}


void NotificationsListJob::handleItem( const QVariant &item )
{
  NotificationInfoPtr notificationInfo( new NotificationInfo() );
  QJson::QObjectHelper::qvariant2qobject( item.toMap(), notificationInfo.data() );
  mNotifications.append(notificationInfo);
}

int NotificationsListJob::numEntries() const
{
  return mNotifications.size();
}

QList< NotificationInfoPtr > NotificationsListJob::notifications() const
{
  return mNotifications;
}
