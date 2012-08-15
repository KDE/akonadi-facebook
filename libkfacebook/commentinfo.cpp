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

#include "commentinfo.h"
#include "util.h"

using namespace KFacebook;

void CommentData::setId( const QString &id)
{
  mId = id;
}

QString CommentData::id() const
{
  return mId;
}

void CommentData::setFrom( const QVariantMap &from)
{
  mFrom = UserInfoPtr( new UserInfo());
  QJson::QObjectHelper::qvariant2qobject(from, mFrom.data());
}

UserInfoPtr CommentData::from() const
{
  return mFrom;
}

QVariantMap CommentData::fromMap() const
{
  return QJson::QObjectHelper::qobject2qvariant(mFrom.data());
}

void CommentData::setMessage( const QString &message)
{
  mMessage = message;
}

QString CommentData::message() const
{
  return mMessage;
}

void CommentData::setCreatedTimeString( const QString &createdTime )
{
  mCreatedTime = createdTime;
}

QString CommentData::createdTimeString() const
{
  return mCreatedTime;
}

KDateTime CommentData::createdTime() const
{
  return facebookTimeToKDateTime(mCreatedTime);
}

void CommentData::setLikes( const int &likes)
{
  mLikes = likes;
}

int CommentData::likes() const
{
  return mLikes;
}

void CommentInfo::setData( const QVariantList &data)
{
  mData = QList<CommentDataPtr>();

  foreach (QVariant	v, data)
  {
    QVariantMap vMap = v.toMap();
    CommentDataPtr commentData ( new CommentData());
    QJson::QObjectHelper::qvariant2qobject(vMap, commentData.data());
    mData << commentData;
  }
}

QList<CommentDataPtr> CommentInfo::data() const
{
  return mData;
}

QVariantList CommentInfo::dataList() const
{
  QVariantList list;

  foreach( const CommentDataPtr &comment, mData ) {
    list.append(QJson::QObjectHelper::qobject2qvariant(comment.data()));
  }

  return list;
}

void CommentInfo::setCount( const int &count)
{
  mCount = count;
}

int CommentInfo::count() const
{
  return mCount;
}

QString CommentInfo::path() const
{
	return "/comments";
}
