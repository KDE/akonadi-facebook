/* Copyright 2011 Pankaj Bhambhani <pankajb64@gmail.com>

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

#include "postinfo.h"
#include "util.h"

using namespace KFacebook;


void PostInfo::setId(const QString &id)
{
    m_id = id;
}

QString PostInfo::id() const
{
    return m_id;
}

void PostInfo::setFrom(const QVariantMap &from)
{
    m_from = UserInfoPtr (new UserInfo());
    QJson::QObjectHelper::qvariant2qobject(from, m_from.data());
}

UserInfoPtr PostInfo::from() const
{
    return m_from;
}

void PostInfo::setMessage(const QString &message)
{
    m_message = message;
}

QString PostInfo::message() const
{
    return m_message;
}

QString PostInfo::pictureUrl() const
{
    return m_pictureUrl;
}

void PostInfo::setPictureUrl(const QString &pictureUrl)
{
    m_pictureUrl = pictureUrl;
}


void PostInfo::setLink(const QString &link)
{
    m_link = link;
}

QString PostInfo::link() const
{
    return m_link;
}


void PostInfo::setName(const QString &name)
{
    m_name = name;
}

QString PostInfo::name() const
{
    return m_name;
}


void PostInfo::setCaption(const QString &caption)
{
    m_caption = caption;
}

QString PostInfo::caption() const
{
    return m_caption;
}

void PostInfo::setDescription(const QString &description)
{
    m_description = description;
}

QString PostInfo::description() const
{
    return m_description;
}

void PostInfo::setSource(const QString &source)
{
    m_source = source;
}

QString PostInfo::source() const
{
    return m_source;
}

void PostInfo::setProperties(const QVariantList &properties)
{
    m_properties = QList<PropertyInfoPtr>();

    foreach (const QVariant &v, properties) {
        QVariantMap vMap = v.toMap();
        PropertyInfoPtr propertyInfo(new PropertyInfo());
        QJson::QObjectHelper::qvariant2qobject(vMap, propertyInfo.data());
        m_properties << propertyInfo;
    }
}

QList<PropertyInfoPtr> PostInfo::properties() const
{
    return m_properties;
}

void PostInfo::setIcon(const QString &icon)
{
    m_icon = icon;
}

QString PostInfo::icon() const
{
    return m_icon;
}

void PostInfo::setType(const QString &type)
{
    m_type = type;
}

QString PostInfo::type() const
{
    return m_type;
}

void PostInfo::setLikes(const QVariantMap &likes)
{
    m_likes = LikeInfoPtr(new LikeInfo());
    QJson::QObjectHelper::qvariant2qobject(likes, m_likes.data());
}

LikeInfoPtr PostInfo::likes() const
{
    return m_likes;
}

QVariantMap PostInfo::likesMap() const
{
    if (!m_likes.isNull()) {
        return QJson::QObjectHelper::qobject2qvariant(m_likes.data());
    }

    return QVariantMap();
}

void PostInfo::setStory(const QString &story)
{
    m_story = story;
}

QString PostInfo::story() const
{
    return m_story;
}

void PostInfo::setComments(const QVariantMap &comments)
{
    m_comments  = CommentInfoPtr (new CommentInfo());
    QJson::QObjectHelper::qvariant2qobject(comments, m_comments.data());
}

CommentInfoPtr PostInfo::comments() const
{
    return m_comments;
}

QVariantMap PostInfo::commentsMap() const
{
    if (!m_comments.isNull()) {
        return QJson::QObjectHelper::qobject2qvariant(m_comments.data());
    }

    return QVariantMap();
}

void PostInfo::setApplication(const QVariantMap &application)
{
    m_application = AppInfoPtr(new AppInfo());
    QJson::QObjectHelper::qvariant2qobject(application, m_application.data());
}

AppInfoPtr PostInfo::application() const
{
    return m_application;
}

void PostInfo::setCreatedTimeString(const QString &createdTime)
{
    m_createdTime = createdTime;
}

QString PostInfo::createdTimeString() const
{
    return m_createdTime;
}

KDateTime PostInfo::createdTime() const
{
    return facebookTimeToKDateTime(m_createdTime);
}

void PostInfo::setUpdatedTimeString(const QString &updatedTime)
{
    m_updatedTime = updatedTime;
}

QString PostInfo::updatedTimeString() const
{
    return m_updatedTime;
}

KDateTime PostInfo::updatedTime() const
{
    return facebookTimeToKDateTime(m_updatedTime);
}
