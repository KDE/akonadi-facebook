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

GetLikesJob::GetLikesJob(const QString& postId, const QString& accessToken) : FacebookGetJob("/fql", accessToken), mLikeCount(0), mUserLikes(false), mCanLike(true)
{
	mPostId = postId;
	QString query = QString("SELECT likes FROM stream WHERE post_id = \"%1\"").arg(mPostId);
	addQueryItem("q", query);
}


void GetLikesJob::handleData(const QVariant& data)
{
	QVariantMap dataMap = data.toMap();
	
	if (!dataMap.isEmpty())
	{
		  QVariantList dataList = dataMap["data"].toList();
		
		if (!dataList.isEmpty())
		{
			  QVariantMap map = dataList[0].toMap();
			
			if (!map.isEmpty()) 
			{ 
				  QVariantMap likeMap = map["likes"].toMap();
				
				if (!likeMap.isEmpty())
				{
					mLikeCount = likeMap["count"].toUInt();
					mUserLikes = likeMap["user_likes"].toBool();
					mCanLike = likeMap["can_like"].toBool();
					mHref = likeMap["href"].toString();
				}
			}
		}
	}
}

uint GetLikesJob::likeCount()
{
	return mLikeCount;
}

bool GetLikesJob::userLikes()
{
	return mUserLikes;
}

bool GetLikesJob::canLike()
{
	return mCanLike;
}

QString GetLikesJob::href()
{
	return mHref;
}
