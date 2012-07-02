/* Copyright 2011 Pankaj Bhambhani <pankajb64@gmail.com>

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
#include "postinfo.h"
#include "util.h"

using namespace KFacebook;


void PostInfo::setId( const QString &id)
{
  mId = id;
}

QString PostInfo::id() const
{
  return mId;
}

void PostInfo::setFrom( const QVariantMap &from)
{
  mFrom = UserInfoPtr (new UserInfo());
  QJson::QObjectHelper::qvariant2qobject(from, mFrom.data());
}

UserInfoPtr PostInfo::from() const
{
  return mFrom;
}

void PostInfo::setMessage( const QString &message)
{
  mMessage = message;
}

QString PostInfo::message() const
{
  return mMessage;
}

QString PostInfo::pictureUrl() const
{
  return mPictureUrl;
}

void PostInfo::setPictureUrl( const QString &pictureUrl)
{
  mPictureUrl = pictureUrl;
}


void PostInfo::setLink( const QString &link)
{
  mLink = link;
}

QString PostInfo::link() const
{
  return mLink;
}


void PostInfo::setName( const QString &name)
{
  mName = name;
}

QString PostInfo::name() const
{
  return mName;
}


void PostInfo::setCaption( const QString &caption)
{
  mCaption = caption;
}

QString PostInfo::caption() const
{
  return mCaption;
}

void PostInfo::setDescription( const QString &description)
{
  mDescription = description;
}

QString PostInfo::description() const
{
  return mDescription;
}

void PostInfo::setSource( const QString &source)
{
  mSource = source;
}

QString PostInfo::source() const
{
  return mSource;
}

void PostInfo::setProperties( const QVariantList &properties)
{
  mProperties = ( QList<PropertyInfoPtr>() );

  foreach (QVariant	v, properties)
  {
	QVariantMap vMap = v.toMap();
	PropertyInfoPtr propertyInfo ( new PropertyInfo());
	QJson::QObjectHelper::qvariant2qobject(vMap, propertyInfo.data());
	mProperties << propertyInfo;
  }
  //mProperties = properties;
}

QList<PropertyInfoPtr> PostInfo::properties() const
{
  return mProperties;
}

void PostInfo::setIcon( const QString &icon)
{
  mIcon = icon;
}

QString PostInfo::icon() const
{
  return mIcon;
}

void PostInfo::setType( const QString &type)
{
  mType = type;
}

QString PostInfo::type() const
{
  return mType;
}

void PostInfo::setLikes( const QVariantMap &likes)
{
  mLikes = LikeInfoPtr( new LikeInfo());
  QJson::QObjectHelper::qvariant2qobject(likes, mLikes.data());
  //mLikes = likes;
}

LikeInfoPtr PostInfo::likes() const
{
  return mLikes;
}

void PostInfo::setStory( const QString &story)
{
  mStory = story;
}

QString PostInfo::story() const
{
  return mStory;
}

void PostInfo::setComments( const QVariantMap &comments)
{
  mComments  = CommentInfoPtr ( new CommentInfo());
  QJson::QObjectHelper::qvariant2qobject(comments, mComments.data());
  //mComments = comments;
}

CommentInfoPtr PostInfo::comments() const
{
  return mComments;
}

void PostInfo::setApplication( const QVariantMap &application)
{
  mApplication = AppInfoPtr( new AppInfo());
  QJson::QObjectHelper::qvariant2qobject(application, mApplication.data());
  //mApplication = application;
}

AppInfoPtr PostInfo::application() const
{
  return mApplication;
}

void PostInfo::setCreatedTimeString( const QString &createdTime )
{
  mCreatedTime = createdTime;
}

QString PostInfo::createdTimeString() const
{
  return mCreatedTime;
}

KDateTime PostInfo::createdTime() const
{
  return facebookTimeToKDateTime(mCreatedTime);
}

void PostInfo::setUpdatedTimeString( const QString &updatedTime )
{
  mUpdatedTime = updatedTime;
}

QString PostInfo::updatedTimeString() const
{
  return mUpdatedTime;
}

KDateTime PostInfo::updatedTime() const
{
  return facebookTimeToKDateTime(mUpdatedTime);
}

/*
void PostInfo::setSenderId( const QString &senderId)
{
  mSenderId = senderId;
}

QString PostInfo::senderId() const
{
  return mSenderId;
}

void PostInfo::setSenderName( const QString &senderName)
{
  mSenderName = senderName;
}


QString PostInfo::senderName() const
{
  return mSenderName;
}



void PostInfo::setAppId( const QString &appId)
{
  mAppId = appId;
}


QString PostInfo::appId() const
{
  return mAppId;
}

void PostInfo::setAppName( const QString &appName)
{
  mAppName = appName;
}


QString PostInfo::appName() const
{
  return mAppName;
}
*/
