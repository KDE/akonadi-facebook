/*  Copyright (C) 2012  Martin Klapetek <martin.klapetek@gmail.com>

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

#include "akonadi_serializer_socialnotification.h"

#include "akonadi_serializer_statusitem.h"
#include "libkfacebook/postinfo.h"
#include <libkfacebook/notificationinfo.h>
#include <../akonadi-facebook/libkfacebook/userinfo.h>

#include <QtCore/qplugin.h>

#include <akonadi/item.h>
#include <qjson/serializer.h>
#include <qjson/parser.h>

#include <KDebug>

using namespace Akonadi;

bool SerializerPluginSocialNotification::deserialize(Item& item, const QByteArray& label, QIODevice& data, int version)
{
    Q_UNUSED(version)

    if (label != Item::FullPayload)
        return false;

    KFacebook::NotificationInfo *object = new KFacebook::NotificationInfo();

    //FIXME: Use   QJson::QObjectHelper::qvariant2qobject( item.toMap(), postInfo.data() );
    QJson::Parser parser;
    QVariantMap map = parser.parse(data.readAll()).toMap();

    object->setId(map["id"].toString());
    object->setFrom(map["from"].toMap());
    object->setTo(map["to"].toMap());
    object->setCreatedTimeString(map["created_time"].toString());
    object->setUpdatedTimeString(map["updated_time"].toString());
    object->setTitle(map["title"].toString());
    object->setLink(map["link"].toString());
    object->setApplication(map["application"].toMap());
    object->setUnread(map["unread"].toBool());

    KFacebook::NotificationInfoPtr notificationItem(object);
    item.setMimeType( "text/x-vnd.akonadi.socialnotification" );
    item.setPayload< KFacebook::NotificationInfoPtr >(notificationItem);

    return true;
}

void SerializerPluginSocialNotification::serialize(const Item& item, const QByteArray& label, QIODevice& data, int& version)
{
    Q_UNUSED(label)
    Q_UNUSED(version)

    if (!item.hasPayload< KFacebook::NotificationInfoPtr >())
        return;

    KFacebook::NotificationInfoPtr notificationInfo = item.payload< KFacebook::NotificationInfoPtr >();

    QVariantMap map;

    map["id"] = notificationInfo.data()->id();

    QVariantMap fromMap;
    if (!notificationInfo.data()->from().isNull()) {
        fromMap["name"] = notificationInfo.data()->from().data()->name();
        fromMap["id"] = notificationInfo.data()->from().data()->id();
    }

    map["from"] = fromMap;

    QVariantMap toMap;
    if (!notificationInfo.data()->to().isNull()) {
        toMap["name"] = notificationInfo.data()->to().data()->name();
        toMap["id"] = notificationInfo.data()->to().data()->id();
    }

    map["to"] = toMap;
    map["created_time"] = notificationInfo.data()->createdTimeString();
    map["update_time"] = notificationInfo.data()->updatedTimeString();
    map["title"] = notificationInfo.data()->title();
    map["link"] = notificationInfo.data()->link();

    QVariantMap appMap;
    if (!notificationInfo.data()->application().isNull()) {
        appMap["name"] = notificationInfo.data()->application().data()->name();
        appMap["id"] = notificationInfo.data()->application().data()->id();
    }

    map["app"] = appMap;
    map["unread"] = notificationInfo.data()->unread();

    QJson::Serializer serializer;

    data.write(serializer.serialize(map));
}

Q_EXPORT_PLUGIN2( akonadi_serializer_socialnotification, Akonadi::SerializerPluginSocialNotification )

