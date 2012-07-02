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
#ifndef POSTADDJOB_H
#define POSTADDJOB_H

#include "facebookjobs.h"

namespace KFacebook {

/**
* Add a post to facebook
*
* @todo get the new id and set it accordingly!
*/
class LIBKFACEBOOK_EXPORT PostAddJob : public FacebookAddJob
{
  Q_OBJECT
  public:
    /**
    * @brief Add a post to facebook.
    *
    * @param subject The subject of the new post.
    * @param message The actual content of the post.
    * @param accessToken The accessToken to add content to facebook
    */
    PostAddJob( const QString &message, const QString &accessToken );
    void abort();
};

}

#endif
