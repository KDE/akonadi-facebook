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
#include "postslistjob.h"

#include <KDebug>
#include <qjson/qobjecthelper.h>


PostsListJob::PostsListJob( const QString& accessToken )
  : ListJobBase( "/me/home", accessToken )
{
}

QList<PostInfoPtr> PostsListJob::posts() const
{
  return mPosts;
}

void PostsListJob::handleItem(const QVariant& item)
{
  PostInfoPtr postInfo( new PostInfo() );
  QJson::QObjectHelper::qvariant2qobject( item.toMap(), postInfo.data() );
  QVariantMap from = postInfo->from();		
  QVariantMap application = postInfo->application();
  postInfo->setSenderId (from["id"].toString());
  postInfo->setSenderName (from["name"].toString());
  postInfo->setAppId (application["id"].toString());
  postInfo->setAppName (application["name"].toString());
  mPosts.append( postInfo );
}

int PostsListJob::numEntries() const
{
  return mPosts.size();
}

