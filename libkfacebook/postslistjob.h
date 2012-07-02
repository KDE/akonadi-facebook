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
#ifndef KFACEBOOK_POSTSLISTJOB_H
#define KFACEBOOK_POSTSLISTJOB_H

#include "listjobbase.h"
#include "postinfo.h"

namespace KFacebook {

class LIBKFACEBOOK_EXPORT PostsListJob : public ListJobBase
{
  Q_OBJECT
  public:
    PostsListJob( const QString &accessToken );
    QList<PostInfoPtr> posts() const;
    int numEntries() const;

  protected:
    void handleItem( const QVariant& item );

  private:
    QList<PostInfoPtr> mPosts;
};

}

#endif
