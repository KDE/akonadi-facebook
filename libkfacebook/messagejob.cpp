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

  // From
  const QVariantMap from = data.toMap()["from"].toMap();
  msgInfo->setFrom(from["name"].toString(), from["id"].toString());

  // To
  const QVariantList recipients = data.toMap()["to"].toMap()["data"].toList();
  foreach(const QVariant recipient, recipients) {
    RecipientPtr to (new Recipient);
    to->name = recipient.toMap()["name"].toString();
    to->id = recipient.toMap()["id"].toString();
    msgInfo->addRecipient(to);
  }

  if (data.toMap().contains("comments")) {
    const QVariantList comments = data.toMap()["comments"].toMap()["data"].toList();
    foreach(const QVariant comment, comments) {
      MessageReplyInfoPtr reply( new MessageReplyInfo( msgInfo ) );
      QJson::QObjectHelper::qvariant2qobject( comment.toMap(), reply.data() );

      // From
      const QVariantMap replyFrom = comment.toMap()["from"].toMap();
      reply->setFrom(replyFrom["name"].toString(), replyFrom["id"].toString());

      msgInfo->addReply(reply);
    }
  }

  mMessageInfo = msgInfo;
}

#include "messagejob.moc"
