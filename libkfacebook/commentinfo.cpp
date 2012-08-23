 /* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

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

#include "commentinfo.h"
#include "util.h"

using namespace KFacebook;

void CommentData::setId(const QString &id)
{
    m_id = id;
}

QString CommentData::id() const
{
    return m_id;
}

void CommentData::setFrom(const QVariantMap &from)
{
    m_from = UserInfoPtr(new UserInfo());
    QJson::QObjectHelper::qvariant2qobject(from, m_from.data());
}

UserInfoPtr CommentData::from() const
{
    return m_from;
}

QVariantMap CommentData::fromMap() const
{
    return QJson::QObjectHelper::qobject2qvariant(m_from.data());
}

void CommentData::setMessage(const QString &message)
{
    m_message = message;
}

QString CommentData::message() const
{
    return m_message;
}

void CommentData::setCreatedTimeString(const QString &createdTime)
{
    m_createdTime = createdTime;
}

QString CommentData::createdTimeString() const
{
    return m_createdTime;
}

KDateTime CommentData::createdTime() const
{
    return facebookTimeToKDateTime(m_createdTime);
}

void CommentData::setLikes(const int &likes)
{
    m_likes = likes;
}

int CommentData::likes() const
{
    return m_likes;
}

void CommentInfo::setData(const QVariantList &data)
{
    m_data = QList<CommentDataPtr>();

    foreach (QVariant	v, data) {
        QVariantMap vMap = v.toMap();
        CommentDataPtr commentData (new CommentData());
        QJson::QObjectHelper::qvariant2qobject(vMap, commentData.data());
        m_data << commentData;
    }
}

QList<CommentDataPtr> CommentInfo::data() const
{
    return m_data;
}

QVariantList CommentInfo::dataList() const
{
    QVariantList list;

    foreach(const CommentDataPtr &comment, m_data) {
        list.append(QJson::QObjectHelper::qobject2qvariant(comment.data()));
    }

    return list;
}

void CommentInfo::setCount(const int &count)
{
    m_count = count;
}

int CommentInfo::count() const
{
    return m_count;
}

QString CommentInfo::path() const
{
    return "/comments";
}
