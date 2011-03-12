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
#include "messagejob.h"

#include <KDebug>
#include <qjson/qobjecthelper.h>

MessageJob::MessageJob( const QString& messageId, const QString& accessToken )
  : FacebookGetJob( '/' + messageId, accessToken)
{
}

MessageInfoPtr MessageJob::messageInfo() const
{
  return mMessageInfo;
}

void MessageJob::handleData( const QVariant &data)
{
  MessageInfoPtr msgInfo( new MessageInfo() );
  QJson::QObjectHelper::qvariant2qobject( data.toMap(), msgInfo.data() );

  if (data.toMap().contains("comments")) {
    const QVariantList comments = data.toMap()["comments"].toMap()["data"].toList();
    foreach(const QVariant comment, comments) {
      MessageReplyInfoPtr reply( new MessageReplyInfo() );
      QJson::QObjectHelper::qvariant2qobject( comment.toMap(), reply.data() );
      msgInfo->addReply(reply);
    }
  }

  mMessageInfo = msgInfo;
/*
  UserInfoPtr friendInfo( new UserInfo() );
  QJson::QObjectHelper::qvariant2qobject( data.toMap(), friendInfo.data() );
  const QVariant location = data.toMap()["location"];
  handleLocation(friendInfo, location);
  const QVariant work = data.toMap()["work"];
  handleWork(friendInfo, work);
  const QVariant partner = data.toMap()["significant_other"];
  handlePartner(friendInfo, partner);
  return friendInfo; */
}

#include "messagejob.moc"
