 /* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

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

#include "getlikesjob.h"

using namespace KFacebook;

GetLikesJob::GetLikesJob(const QString &postId, const QString &accessToken)
    : FacebookGetJob("/fql", accessToken),
      m_likeCount(0),
      m_userLikes(false),
      m_canLike(true)
{
    m_postId = postId;
    QString query = QString("SELECT likes FROM stream WHERE post_id = \"%1\"").arg(m_postId);
    addQueryItem("q", query);
}

void GetLikesJob::handleData(const QVariant& data)
{
    QVariantMap dataMap = data.toMap();

    if (!dataMap.isEmpty()) {
        QVariantList dataList = dataMap["data"].toList();

        if (!dataList.isEmpty()) {
            QVariantMap map = dataList[0].toMap();

            if (!map.isEmpty()) {
                QVariantMap likeMap = map["likes"].toMap();

                if (!likeMap.isEmpty()) {
                    m_likeCount = likeMap["count"].toUInt();
                    m_userLikes = likeMap["user_likes"].toBool();
                    m_canLike = likeMap["can_like"].toBool();
                    m_href = likeMap["href"].toString();
                }
            }
        }
    }
}

uint GetLikesJob::likeCount()
{
    return m_likeCount;
}

bool GetLikesJob::userLikes()
{
    return m_userLikes;
}

bool GetLikesJob::canLike()
{
    return m_canLike;
}

QString GetLikesJob::href()
{
    return m_href;
}
