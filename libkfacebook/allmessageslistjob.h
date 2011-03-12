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
#ifndef ALLEMESSAGESLISTJOB_H
#define ALLEMESSAGESLISTJOB_H

#include "messageinfo.h"
#include "libkfacebook_export.h"
#include "facebookjobs.h"

#include <KJob>
#include <QPointer>

class MessagesListJob;

class LIBKFACEBOOK_EXPORT AllMessagesListJob : public KJob
{
  Q_OBJECT
  public:
    explicit AllMessagesListJob( const QString &accessToken );
    void setLowerLimit( const KDateTime &lowerLimit );
    QList<MessageInfoPtr> allMessages() const;
    virtual void start();

  protected slots:
    void messagesListJobFinished( KJob * job );

  protected:
    virtual bool doKill();

  private:
    KDateTime mLowerLimit;
    QPointer<MessagesListJob> mCurrentJob;
    QString mAccessToken;
    QList<MessageInfoPtr> mMessages;
};

#endif
