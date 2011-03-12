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
#include "messageinfo.h"

#include "util.h"

#include <KDebug>
#include <KLocalizedString>
#include <KPIMUtils/LinkLocator>

void MessageReplyInfo::setId(const QString &id)
{
  mId = id;
}

QString MessageReplyInfo::id() const
{
  return mId;
}

void MessageReplyInfo::setFrom(const QString &name, const QString &id)
{
  mFrom = name;
  mFromId = id;
}

QString MessageReplyInfo::from() const
{
  return mFrom;
}

QString MessageReplyInfo::fromId() const
{
  return mFromId;
}

void MessageReplyInfo::setMessage(const QString &message)
{
  mMessage = message;
}

QString MessageReplyInfo::message() const
{
  return mMessage;
}

void MessageReplyInfo::setCreatedTime(const QString &created_time)
{
  mCreatedTime = KDateTime::fromString(created_time, KDateTime::ISODate);
}

QString MessageReplyInfo::createdTimeAsString() const
{
  return mCreatedTime.toString();
}

KDateTime MessageReplyInfo::createdTime() const
{
  return mCreatedTime;
}


KMime::Message::Ptr MessageInfo::asMessage() const
{
  KMime::Message *msg = new KMime::Message();

  msg->setBody( message().toAscii() );
  msg->date()->fromUnicodeString( updatedTime().toString(KDateTime::RFCDateDay), "utf-8" );
  msg->contentType()->fromUnicodeString( "text/plain", "utf-8" );
  msg->subject()->fromUnicodeString( subject(), "utf-8" );
  msg->from()->fromUnicodeString( "you@facebook", "utf-8" );

  msg->assemble();

  return KMime::Message::Ptr(msg);
}

void MessageInfo::setId(const QString &id)
{
  mId = id;
}

QString MessageInfo::id() const
{
  return mId;
}

void MessageInfo::setSubject(const QString &subject)
{
  mSubject = subject;
}

QString MessageInfo::subject() const
{
  return mSubject;
}

void MessageInfo::setMessage(const QString &message)
{
  mMessage = message;
}

QString MessageInfo::message() const
{
  return mMessage;
}

void MessageInfo::setUpdatedTime(const QString &date)
{
  mUpdatedTime = KDateTime::fromString(date, KDateTime::ISODate);
}

QString MessageInfo::updatedTimeAsString() const
{
  return mUpdatedTime.toString();
}

KDateTime MessageInfo::updatedTime() const
{
  return mUpdatedTime;
}

void MessageInfo::setFrom(const QString &name, const QString &id)
{
  mFrom = name;
  mFromId = id;
}

QString MessageInfo::from() const
{
  return mFrom;
}

QString MessageInfo::fromId() const
{
  return mFromId;
}

void MessageInfo::addReply(const MessageReplyInfoPtr reply)
{
  mReplies << reply;
}

QList<MessageReplyInfoPtr> MessageInfo::replies() const
{
  return mReplies;
}



