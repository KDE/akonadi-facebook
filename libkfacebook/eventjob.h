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
#ifndef EVENTJOB_H
#define EVENTJOB_H

#include "facebookjobs.h"
#include "eventinfo.h"

class LIBKFACEBOOK_EXPORT EventJob : public FacebookGetJob
{
  Q_OBJECT
  public:
    EventJob( const QStringList &eventIds, const QString &accessToken );
    EventJob( const QString &eventId, const QString &accessToken );
    QList<EventInfoPtr> eventInfo() const;

  protected:
    virtual void handleData( const QVariant& data );

  private:
    QStringList eventFields() const;
    EventInfoPtr handleSingleEvent( const QVariant& data );

    QList<EventInfoPtr> mEventInfo;
    bool mMultiQuery;
};

#endif
