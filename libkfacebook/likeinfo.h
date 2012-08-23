 /* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   (at your option) version 3 or, at the discretion of KDE e.V.
   (which shall act as a proxy as in section 14 of the GPLv3), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KFACEBOOK_LIKEINFO_H
#define KFACEBOOK_LIKEINFO_H

#include "libkfacebook_export.h"
#include "userinfo.h"

#include <qjson/qobjecthelper.h>
#include <QObject>

namespace KFacebook {

/**
 * Class to represent likes on a facebook post
 */

class LIBKFACEBOOK_EXPORT LikeInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList data WRITE setData READ dataList)
    Q_PROPERTY(int count WRITE setCount READ count)

public:
    /**
     * Set the data of this like (list of people who like the post)
     * @param data the like data
     */
    virtual void setData(const QVariantList &data);
    /**
     * Returns the like data
     */
    QList<UserInfoPtr> data() const;
    /**
     * Return the like data as VariantList
     */
    virtual QVariantList dataList() const;

    /**
     * Set the count of this like (number of people who like the post)
     * @param count the like count
     */
    virtual void setCount(const int &count);
    /**
     * Returns the like count
     */
    virtual int count() const;

    /**
     * Returns relative REST path w.r.t FacebookObject, "/" included
     */
    virtual QString path() const ;

private:
    QList<UserInfoPtr> m_data;   /*  Data of like. */
    int m_count;                 /* Count  of like. */
};

typedef QSharedPointer<LikeInfo> LikeInfoPtr;

}

#endif
