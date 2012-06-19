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

#include "notificationinfo.h"
#include "userinfo.h"
#include "appinfo.h"
#include "util.h"

void NotificationInfo::setId(const QString& id)
{
  mId = id;
}

QString NotificationInfo::id() const
{
  return mId;
}

void NotificationInfo::setFrom(const QVariantMap& from)
{
  mFrom = UserInfoPtr (new UserInfo());
  QJson::QObjectHelper::qvariant2qobject(from, mFrom.data());
}

UserInfoPtr NotificationInfo::from() const
{
  return mFrom;
}

void NotificationInfo::setTo(const QVariantMap& to)
{
  mTo = UserInfoPtr (new UserInfo());
  QJson::QObjectHelper::qvariant2qobject(to, mTo.data());
}

UserInfoPtr NotificationInfo::to() const
{
  return mTo;
}

void NotificationInfo::setCreatedTimeString(const QString& time)
{
  mCreatedTime = time;
}

QString NotificationInfo::createdTimeString() const
{
  return mCreatedTime;
}

KDateTime NotificationInfo::createdTime() const
{
  return facebookTimeToKDateTime(mCreatedTime);
}

void NotificationInfo::setUpdatedTimeString(const QString& time)
{
  mUpdatedTime = time;
}

QString NotificationInfo::updatedTimeString() const
{
  return mUpdatedTime;
}

KDateTime NotificationInfo::updatedTime() const
{
  return facebookTimeToKDateTime(mUpdatedTime);
}

void NotificationInfo::setTitle(const QString& title)
{
  mTitle = title;
}

QString NotificationInfo::title() const
{
  return mTitle;
}

void NotificationInfo::setLink(const QString& link)
{
  mLink = link;
}

QString NotificationInfo::link() const
{
  return mLink;
}

void NotificationInfo::setApplication(const QVariantMap& app)
{
  mApp = AppInfoPtr (new AppInfo());
  QJson::QObjectHelper::qvariant2qobject(app, mApp.data());
}

AppInfoPtr NotificationInfo::application() const
{
  return mApp;
}

void NotificationInfo::setUnread(bool unread)
{
  mUnread = unread;
}

bool NotificationInfo::unread() const
{
  return mUnread;
}
