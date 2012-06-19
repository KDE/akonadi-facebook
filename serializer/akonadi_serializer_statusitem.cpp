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

#include "akonadi_serializer_statusitem.h"
#include "libkfacebook/postinfo.h"
#include "libkfacebook/commentinfo.h"

#include <QtCore/qplugin.h>

#include <akonadi/item.h>
#include <qjson/serializer.h>
#include <qjson/parser.h>

#include <KDebug>

using namespace Akonadi;

bool SerializerPluginStatusItem::deserialize(Item& item, const QByteArray& label, QIODevice& data, int version)
{
    Q_UNUSED(version)

    if (label != Item::FullPayload)
        return false;

    PostInfo *object = new PostInfo();

    //FIXME: Use   QJson::QObjectHelper::qvariant2qobject( item.toMap(), postInfo.data() );
    QJson::Parser parser;
    QVariantMap map = parser.parse(data.readAll()).toMap();

    object->setId(map["id"].toString());
    object->setFrom(map["from"].toMap());
    object->setApplication(map["application"].toMap());
    object->setMessage(map["message"].toString());
    object->setPictureUrl(map["picture"].toString());
    object->setLink(map["link"].toString());
    object->setName(map["name"].toString());
    object->setCaption(map["caption"].toString());
    object->setDescription(map["description"].toString());
    object->setSource(map["source"].toString());
    object->setType(map["type"].toString());
    object->setIcon(map["icon"].toString());
    object->setLikes(map["likes"].toMap());
    object->setStory(map["story"].toString());
    object->setComments(map["comments"].toMap());
    object->setApplication(map["application"].toMap());
    object->setCreatedTimeString(map["created_time"].toString());
    object->setUpdatedTimeString(map["updated_time"].toString());

    PostInfoPtr postItem(object);
    item.setMimeType( "text/x-vnd.akonadi.statusitem" );
    item.setPayload< PostInfoPtr >(postItem);

    return true;
}


void SerializerPluginStatusItem::serialize(const Item& item, const QByteArray& label, QIODevice& data, int& version)
{
    Q_UNUSED(label)
    Q_UNUSED(version)

    if (!item.hasPayload< PostInfoPtr >())
        return;

    PostInfoPtr postinfo = item.payload< PostInfoPtr >();

    QVariantMap map;

    map["id"] = postinfo->id();

    QVariantMap fromMap;
    if (!postinfo->from().isNull()) {
        fromMap["id"] = postinfo->from().data()->id();
        fromMap["name"] = postinfo->from().data()->name();
        fromMap["first_name"] = postinfo->from().data()->firstName();
        fromMap["last_name"] = postinfo->from().data()->lastName();
        fromMap["birthday"] = postinfo->from().data()->birthdayAsString();
        fromMap["website"] = postinfo->from().data()->website();
        fromMap["timezone"] = postinfo->from().data()->timezone();
        fromMap["updated_time"] = postinfo->from().data()->updatedTimeString();
    }

    map["from"] = fromMap;
    map["message"] = postinfo->message();
    map["picture"] = postinfo->pictureUrl();
    map["link"] = postinfo->link();
    map["name"] = postinfo->name();
    map["caption"] = postinfo->caption();
    map["description"] = postinfo->description();
    map["source"] = postinfo->source();
    //map["properties"] =
    map["icon"] = postinfo->icon();
    map["type"] = postinfo->type();

    QVariantMap likesMap;
    if (!postinfo->likes().isNull()) {
        QVariantList likesData;
        foreach(const UserInfoPtr &userinfo, postinfo->likes().data()->data()) {
            QVariantMap likesDataMap;
            likesDataMap["id"] = userinfo.data()->id();
            likesDataMap["name"] = userinfo.data()->name();
//             likesDataMap["first_name"] = userinfo.data()->firstName();
//             likesDataMap["last_name"] = userinfo.data()->lastName();
//             likesDataMap["birthday"] = userinfo.data()->birthdayAsString();
//             likesDataMap["website"] = userinfo.data()->website();
//             likesDataMap["timezone"] = userinfo.data()->timezone();
//             likesDataMap["updated_time"] = userinfo.data()->updatedTimeString();

            likesData.append(likesDataMap);
        }
        likesMap["data"] = likesData;
        likesMap["count"] = postinfo->likes().data()->count();
    }
    map["likes"] = likesMap;
    map["story"] = postinfo->story();

    QVariantMap commentsMap;
    if (!postinfo->comments().isNull()) {
        QVariantList commentsData;
        foreach(const CommentDataPtr &comment, postinfo->comments().data()->data()) {
            QVariantMap commentsDataMap;
            commentsDataMap["id"] = comment.data()->id();

            QVariantMap commentFromMap;
            if (!comment.data()->from().isNull()) {
                commentFromMap["id"] = comment.data()->from().data()->id();
                commentFromMap["name"] = comment.data()->from().data()->name();
            }

            commentsDataMap["from"] = commentFromMap;
            commentsDataMap["message"] = comment.data()->message();
            commentsDataMap["created_time"] = comment.data()->createdTimeString();
            commentsDataMap["likes"] = comment.data()->likes();

            commentsData.append(commentsDataMap);
        }
        commentsMap["data"] = commentsData;
        commentsMap["count"] = postinfo->comments().data()->count();
    }

    map["comments"] = commentsMap;

    QVariantMap appMap;
    if (!postinfo->application().isNull()) {
        appMap["id"] = postinfo->application().data()->id();
        appMap["name"] = postinfo->application().data()->name();
        appMap["description"] = postinfo->application().data()->description();
        appMap["category"] = postinfo->application().data()->category();
        appMap["company"] = postinfo->application().data()->company();
        appMap["icon_url"] = postinfo->application().data()->iconUrl();
        appMap["subcategory"] = postinfo->application().data()->subcategory();
        appMap["link"] = postinfo->application().data()->link();
        appMap["logo_url"] = postinfo->application().data()->logoUrl();
    }

    map["application"] = appMap;
    map["created_time"] = postinfo->createdTimeString();
    map["updated_time"] = postinfo->updatedTimeString();

    //     QVariantList comments;
//     Q_FOREACH(const StatusItemCommentPtr &comment, postinfo->comments()) {
//         QVariantMap commentMap;
// //         commentMap["post_id"] = comment.data()->postId();
//         commentMap["created_time"] = comment.data()->createdTime();
//         commentMap["id"] = comment.data()->commentId();
//         commentMap["message"] = comment.data()->message();
//
//         QVariantMap fromMap;
//         fromMap["id"] = comment.data()->fromId();
//         fromMap["name"] = comment.data()->fromName();
//
//         commentMap["from"] = fromMap;
//
//         comments.append(commentMap);
//     }

//     map["comments"] = comments;
//     map["comment_count"] = postinfo->commentCount();

//     kDebug() << map["comments"];
//     map["likes"] = postinfo->likes();
//     map["
//     QVariantMap origin;
//     origin["streamId"] = postinfo->streamId();
//     map["origin"] = origin;
/*
    map["title"] = postinfo->title();
    map["published"] = postinfo->published().toTime_t();
    map["updated"] = postinfo->updated().toTime_t();

    QVariantMap summary;
    summary["content"] = postinfo->summary();;
    map["summary"] = summary;

    QVariantMap content;
    content["content"] = postinfo->content();
    map["content"] = content;
    map["author"] = postinfo->author();

    QMap< QString, QString > alternatives = postinfo->alternatives();
    QVariantList list;
    foreach (QString key, alternatives.keys()) {
        QVariantMap alternative;
        alternative["type"] = key;
        alternative["href"] = alternatives[key];
        list.append(alternative);
    }
    map["alternate"] = list;

    QStringList categories = postinfo->tags();
    QVariantList cat_list;
    foreach (QString category, categories) {
        cat_list.append(category);
    }
    map["categories"] = cat_list;*/

    QJson::Serializer serializer;

    data.write(serializer.serialize(map));
}

Q_EXPORT_PLUGIN2( akonadi_serializer_statusitem, Akonadi::SerializerPluginStatusItem )

#include "akonadi_serializer_statusitem.moc"