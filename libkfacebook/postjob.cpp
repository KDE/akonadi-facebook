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
#include "postjob.h"

#include <KDebug>
#include <qjson/qobjecthelper.h>

PostJob::PostJob( const QString& postId, const QString& accessToken )
  : FacebookGetIdJob(postId, accessToken)
{
}

PostJob::PostJob( const QStringList& postIds, const QString& accessToken )
  : FacebookGetIdJob(postIds, accessToken )
{
}

QList<PostInfoPtr> PostJob::postInfo() const
{
  return mPostInfo;
}

void PostJob::handleSingleData( const QVariant& data )
{
  PostInfoPtr postInfo( new PostInfo() );
  const QVariantMap dataMap = data.toMap();
  QJson::QObjectHelper::qvariant2qobject( dataMap, postInfo.data() );
  mPostInfo.append(postInfo);
}

#include "postjob.moc"
