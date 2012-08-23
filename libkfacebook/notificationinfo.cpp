/* Copyright 2012 Martin Klapetek <martin.klapetek@gmail.com>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   (at your option) version 3 or, at the discretion of KDE e.V.
   (which shall act as a proxy as in section 14 of the GPLv3), any later version.

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

using namespace KFacebook;

void NotificationInfo::setId(const QString &id)
{
    m_id = id;
}

QString NotificationInfo::id() const
{
    return m_id;
}

void NotificationInfo::setFrom(const QVariantMap &from)
{
    m_from = UserInfoPtr (new UserInfo());
    QJson::QObjectHelper::qvariant2qobject(from, m_from.data());
}

UserInfoPtr NotificationInfo::from() const
{
    return m_from;
}

void NotificationInfo::setTo(const QVariantMap &to)
{
    m_to = UserInfoPtr (new UserInfo());
    QJson::QObjectHelper::qvariant2qobject(to, m_to.data());
}

UserInfoPtr NotificationInfo::to() const
{
    return m_to;
}

void NotificationInfo::setCreatedTimeString(const QString &time)
{
    m_createdTime = time;
}

QString NotificationInfo::createdTimeString() const
{
    return m_createdTime;
}

KDateTime NotificationInfo::createdTime() const
{
    return facebookTimeToKDateTime(m_createdTime);
}

void NotificationInfo::setUpdatedTimeString(const QString &time)
{
    m_updatedTime = time;
}

QString NotificationInfo::updatedTimeString() const
{
    return m_updatedTime;
}

KDateTime NotificationInfo::updatedTime() const
{
    return facebookTimeToKDateTime(m_updatedTime);
}

void NotificationInfo::setTitle(const QString &title)
{
    m_title = title;
}

QString NotificationInfo::title() const
{
    return m_title;
}

void NotificationInfo::setLink(const QString &link)
{
    m_link = link;
}

QString NotificationInfo::link() const
{
    return m_link;
}

void NotificationInfo::setApplication(const QVariantMap &app)
{
    m_app = AppInfoPtr (new AppInfo());
    QJson::QObjectHelper::qvariant2qobject(app, m_app.data());
}

AppInfoPtr NotificationInfo::application() const
{
    return m_app;
}

void NotificationInfo::setUnread(bool unread)
{
    m_unread = unread;
}

bool NotificationInfo::unread() const
{
    return m_unread;
}
