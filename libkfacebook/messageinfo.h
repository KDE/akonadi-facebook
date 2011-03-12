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
#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <config.h>
#include "libkfacebook_export.h"

#include <KMime/Message>
#include <KDateTime>
#include <QObject>

class LIBKFACEBOOK_EXPORT MessageReplyInfo : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString id WRITE setId READ id)
  Q_PROPERTY(QString message WRITE setMessage READ message)
  Q_PROPERTY(QString created_times WRITE setCreatedTime READ createdTimeAsString)

  public:
    void setId(const QString &id);
    QString id() const;

    void setFrom(const QString &name, const QString &id);
    QString from() const;
    QString fromId() const;

    void setMessage(const QString &message);
    QString message() const;

    void setCreatedTime(const QString &created_time);
    QString createdTimeAsString() const;
    KDateTime createdTime() const;

  private:
    QString mId;
    QString mFrom;
    QString mFromId;
    QString mMessage;
    KDateTime mCreatedTime;
};

typedef QSharedPointer< MessageReplyInfo > MessageReplyInfoPtr;

class LIBKFACEBOOK_EXPORT MessageInfo : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id WRITE setId READ id)
  Q_PROPERTY(QString subject WRITE setSubject READ subject)
  Q_PROPERTY(QString message WRITE setMessage READ message)
  Q_PROPERTY(QString updated_time WRITE setUpdatedTime READ updatedTimeAsString)
  
  public:
    KMime::Message::Ptr asMessage() const;

    void setId(const QString &id);
    QString id() const;

    void setSubject(const QString &subject);
    QString subject() const;

    void setMessage(const QString &message);
    QString message() const;

    void setUpdatedTime(const QString &date);
    QString updatedTimeAsString() const;
    KDateTime updatedTime() const;

    KDateTime createdTime() const;

    void setFrom(const QString &name, const QString &id);
    QString from() const;
    QString fromId() const;

    void addReply(const MessageReplyInfoPtr reply);
    QList<MessageReplyInfoPtr> replies() const;

  private:
    QString mId;
    QString mSubject;
    QString mMessage;
    KDateTime mUpdatedTime;
    KDateTime mCreatedTime;
    QString mFrom;
    QString mFromId;

    QList<MessageReplyInfoPtr> mReplies;

};

typedef QSharedPointer<MessageInfo> MessageInfoPtr;

#endif
