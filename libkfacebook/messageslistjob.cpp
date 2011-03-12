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
#include "messageslistjob.h"

#include <KDebug>
#include <qjson/qobjecthelper.h>

MessagesListJob::MessagesListJob( const QString& accessToken )
  : FacebookGetJob( "/me/inbox", accessToken )
{
  setFields( QStringList() << "id" << "updated_time" );
}

QList< MessageInfoPtr > MessagesListJob::messages() const
{
  return mMessages;
}

void MessagesListJob::handleData( const QVariant& root )
{
  const QVariant data = root.toMap()["data"];
  foreach( const QVariant &message, data.toList() ) {
    MessageInfoPtr messageInfo( new MessageInfo() );
    QJson::QObjectHelper::qvariant2qobject( message.toMap(), messageInfo.data() );
    mMessages.append( messageInfo );
  }
}


