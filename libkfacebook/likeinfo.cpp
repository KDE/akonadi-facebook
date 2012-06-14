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

#include "likeinfo.h"
/*
void LikeData::setId( const QString &id)
{
  mId = id;
}

QString LikeData::id() const
{
  return mId;
}

void LikeData::setName( const QString &name)
{
  mName = name;
}

QString LikeData::name() const
{
  return mName;
}
*/

void LikeInfo::setData( const QVariantList &data)
{
  mData = new QList<UserInfoPtr>();
  
  foreach (QVariant	v, data)
  {
	QVariantMap vMap = v.toMap();
	UserInfoPtr userInfo ( new UserInfo());
	QJson::QObjectHelper::qvariant2qobject(vMap, userInfo.data());
	mData << userInfo;
  }
  
}

QList<UserInfoPtr> LikeInfo::data() const
{
  return mData;
}

void LikeInfo::setCount( const int &count)
{
  mcount = count;
}

int LikeInfo::count() const
{
  return mCount;
}