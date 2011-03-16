/* Copyright 2011 Thomas McGuire <mcguire@kde.org>

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
#ifndef PHOTOJOB_H
#define PHOTOJOB_H

#include "libkfacebook_export.h"
#include "facebookjobs.h"
#include <KJob>
#include <QImage>
#include <QPointer>

/**
 * A FacebookGetJob to retrieve the profile picture of a person.
 */
class LIBKFACEBOOK_EXPORT PhotoJob : public FacebookGetJob
{
  Q_OBJECT
  public:
    /**
    * @brief Create a PhotoJob that will retrieve the large pphoto of a person.
    *
    * @param friendId The id of the person of whom we want to retrive the
    *                 profile picture.
    * @param accessToken The facebook access token to retrieve this data.
    */
    PhotoJob( const QString &friendId, const QString &accessToken );

    /**
    * @return The profile picture as a QImage.
    */
    QImage photo() const;

  private slots:
    void jobFinished( KJob *job );

  private:
    void handleData( const QVariant& data );
    QImage mImage;
};

#endif
