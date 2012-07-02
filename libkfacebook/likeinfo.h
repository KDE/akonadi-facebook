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

#ifndef KFACEBOOK_LIKEINFO_H
#define KFACEBOOK_LIKEINFO_H

#include "libkfacebook_export.h"
#include "userinfo.h"

#include <qjson/qobjecthelper.h>
#include <QObject>

namespace KFacebook {
/*
class LikeData : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name WRITE setName READ name)
	Q_PROPERTY(QString id WRITE setId READ id)

	public:

		/**
		 * Set the name of person who liked the post
		 * @param name the name
		 *
		void setName( const QString &name);
		/**
		 * Returns the name of person who liked the post
		 *
		QString name() const;

		/**
		 * Set the facebook id of person who liked the post
		 * @param id the facebook id
		 *
		void setId( const QString &id);
		/**
		 * Returns the facebook id of person who liked the post
		 *
		QString id() const;

	private:

		QString mId;          /* Facebook id person who liked the post. *
		QString mName;          /* Name person who liked the post. *
}

typedef QSharedPointer<LikeData> LikeDataPtr;
*/

/**
 *	Class to represent likes on a facebook post
 */

 class LIBKFACEBOOK_EXPORT LikeInfo : public QObject
 {

	Q_OBJECT
	Q_PROPERTY(QVariantList data WRITE setData )
	Q_PROPERTY(int count WRITE setCount READ count)

	public:

		/**
		 * Set the data of this like ( list of people who like the post)
		 * @param data the like data
		 */
		void setData( const QVariantList &data);
		/**
		 * Returns the like data
		 */
		QList<UserInfoPtr> data() const;

		/**
		 * Set the count of this like ( number of people who like the post)
		 * @param count the like count
		 */
		void setCount( const int &count);
		/**
		 * Returns the like count
		 */
		int count() const;


	private:

		QList<UserInfoPtr> mData;          /*  Data of like. */
		int mCount;          /* Count  of like. */

 };

typedef QSharedPointer<LikeInfo> LikeInfoPtr;

}

#endif
