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

#ifndef KFACEBOOK_APPINFO_H
#define KFACEBOOK_APPINFO_H

#include "libkfacebook_export.h"
#include <qjson/qobjecthelper.h>
#include <QObject>
#include <QSharedPointer>

namespace KFacebook {

/**
 *	Class to represent a facebook application. See https://developers.facebook.com/docs/reference/api/application/
 */

 class LIBKFACEBOOK_EXPORT AppInfo : public QObject
 {
	Q_OBJECT
	Q_PROPERTY(QString id WRITE setId READ id)
	Q_PROPERTY(QString name WRITE setName READ name)
	Q_PROPERTY(QString description WRITE setDescription READ description)
	Q_PROPERTY(QString category WRITE setCategory READ category)
	Q_PROPERTY(QString company WRITE setCompany READ company)
	Q_PROPERTY(QString icon_url WRITE setIconUrl READ iconUrl)
	Q_PROPERTY(QString subcategory WRITE setSubcategory READ subcategory)
	Q_PROPERTY(QString link WRITE setLink READ link)
	Q_PROPERTY(QString logo_url WRITE setLogoUrl READ logoUrl)

	public :

		/**
		 * Set the facebook id of this application
		 * @param id the facebook id
		 */
		void setId( const QString &id);
		/**
		 * Returns the facebook id
		 */
		QString id() const;

		/**
		 * Set the facebook name of this application
		 * @param  the facebook name
		 */
		void setName( const QString &name);
		/**
		 * Returns the facebook name
		 */
		QString name() const;

		/**
		 * Set the description of this application
		 * @param  the description
		 */
		void setDescription( const QString &description);
		/**
		 * Returns the description
		 */
		QString description() const;

		/**
		 * Set the category of this application
		 * @param  the category
		 */
		void setCategory( const QString &category);
		/**
		 * Returns the category
		 */
		QString category() const;

		/**
		 * Set the company of this application
		 * @param  the company
		 */
		void setCompany( const QString &company);
		/**
		 * Returns the company
		 */
		QString company() const;

		/**
		 * Set the Icon URL of this application
		 * @param  the Icon URL
		 */
		void setIconUrl( const QString &iconUrl);
		/**
		 * Returns the Icon Url
		 */
		QString iconUrl() const;

		/**
		 * Set the subcategory of this application
		 * @param  the subcategory
		 */
		void setSubcategory( const QString &subcategory);
		/**
		 * Returns the subcategory
		 */
		QString subcategory() const;

		/**
		 * Set the Logo URL of this application
		 * @param  the Logo URL
		 */
		void setLogoUrl( const QString &logoUrl);
		/**
		 * Returns the Logo URL
		 */
		QString logoUrl() const;

		/**
		 * Set the link of this application
		 * @param  the link
		 */
		void setLink( const QString &link);
		/**
		 * Returns the link
		 */
		QString link() const;

	private:

		QString mId;          /* Facebook id of the Application. */
		QString mName; /* Name of the Application */
		QString mDescription; /* Description of the Application. */
		QString mCategory; /* Category of the Application */
		QString mCompany; /* Company of the Application */
		QString mIconUrl; /* IconUrl of the Application */
		QString mSubcategory; /* Subcategory of the Application */
		QString mLink; /* Link of the Application */
		QString mLogoUrl; /* LogoUrl of the Application */
		/*QString mName; /* Name of the Application *
		QString mName; /* Name of the Application */

 };

typedef QSharedPointer<AppInfo> AppInfoPtr;

}

#endif
