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

#ifndef KFACEBOOK_PROPERTYINFO_H
#define KFACEBOOK_PROPERTYINFO_H

#include "libkfacebook_export.h"

#include <qjson/qobjecthelper.h>
#include <QObject>
#include <QSharedPointer>

namespace KFacebook {

/**
 *	Class to represent a property associated with a facebook post
 */

 class LIBKFACEBOOK_EXPORT PropertyInfo : public QObject
 {
	Q_OBJECT
	Q_PROPERTY(QString name WRITE setName READ name)
	Q_PROPERTY(QString text WRITE setText READ text)
	Q_PROPERTY(QString href WRITE setHref READ href)

	public:

		/**
		 * Set the name of this property
		 * @param name the property name
		 */
		void setName( const QString &name);
		/**
		 * Returns the property name
		 */
		QString name() const;

		/**
		 * Set the text of this property
		 * @param text the property text
		 */
		void setText( const QString &text);
		/**
		 * Returns the property text
		 */
		QString text() const;

		/**
		 * Set the href link of this property
		 * @param href the property href
		 */
		void setHref( const QString &href);
		/**
		 * Returns the property href
		 */
		QString href() const;

	private:

		QString mName;          /* Name of the property. */
		QString mText;          /* Text of the property. */
		QString mHref;          /* Href Link of the property. */
 };

typedef QSharedPointer<PropertyInfo> PropertyInfoPtr;

}

#endif
