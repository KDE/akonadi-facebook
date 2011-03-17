/* Copyright 2011 Thomas McGuire <mcguire@kde.org>

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
#include "eventjob.h"

#include <KDebug>
#include <qjson/qobjecthelper.h>

EventJob::EventJob( const QString& eventId, const QString& accessToken )
  : FacebookGetIdJob(eventId, accessToken)
{
  setFields( eventFields() );
}

EventJob::EventJob( const QStringList& eventIds, const QString& accessToken )
  : FacebookGetIdJob(eventIds, accessToken )
{
  setFields( eventFields() );
}

QStringList EventJob::eventFields() const
{
  QStringList fields;
  fields << "owner"
         << "name"
         << "description"
         << "start_time"
         << "end_time"
         << "location"
         << "venue"
         << "privacy"
         << "updated_time"
         << "noreply"
         << "maybe"
         << "attending"
         << "declined";
  return fields;
}

QList<EventInfoPtr> EventJob::eventInfo() const
{
  return mEventInfo;
}

QList<AttendeeInfoPtr> attendees(const QVariantMap &dataMap, const QString &facebookKey,
                                 Attendee::PartStat status)
{
  QList<AttendeeInfoPtr> retVal;
  const QVariantList list = dataMap.value(facebookKey).toMap().value("data").toList();
  foreach(const QVariant &attendee, list) {
    const QVariantMap map = attendee.toMap();
    AttendeeInfoPtr attendeeInfo( new AttendeeInfo(map["name"].toString(),
                                                   map["id"].toString(), status) );
    retVal << attendeeInfo;
  }
  return retVal;
}

void EventJob::handleSingleData( const QVariant& data )
{
  EventInfoPtr eventInfo( new EventInfo() );
  const QVariantMap dataMap = data.toMap();
  QJson::QObjectHelper::qvariant2qobject( dataMap, eventInfo.data() );
  const QVariant owner = dataMap.value( "owner" );
  if ( !owner.isNull() && owner.isValid() ) {
    eventInfo->setOrganizer( owner.toMap().value( "name" ).toString() );
  }

  eventInfo->addAttendees(attendees(dataMap, "noreply", Attendee::NeedsAction));
  eventInfo->addAttendees(attendees(dataMap, "maybe", Attendee::Tentative));
  eventInfo->addAttendees(attendees(dataMap, "attending", Attendee::Accepted));
  eventInfo->addAttendees(attendees(dataMap, "declined", Attendee::Declined));

  mEventInfo.append(eventInfo);
}

#include "eventjob.moc"
