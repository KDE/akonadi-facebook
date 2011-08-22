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
#ifndef POSTINFO_H
#define POSTINFO_H

#include "libkfacebook_export.h"
#include <qjson/qobjecthelper.h>

#include <KDateTime>
#include <QObject>

/**
 * Class to represent a facebook post
 */
class LIBKFACEBOOK_EXPORT PostInfo : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id WRITE setId READ id)
  Q_PROPERTY(QVariantMap from WRITE setFrom READ from)
  Q_PROPERTY(QVariantMap application WRITE setApplication READ application)
  Q_PROPERTY(QString message WRITE setMessage READ message)
  Q_PROPERTY(QString picture WRITE setPictureUrl READ pictureUrl)
  Q_PROPERTY(QString created_time WRITE setCreatedTimeString READ createdTimeString)
  Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)
  Q_PROPERTY(QString name WRITE setName READ name)
  Q_PROPERTY(QString type WRITE setType READ type)
  Q_PROPERTY(QString description WRITE setDescription READ description)
  Q_PROPERTY(QString link WRITE setLink READ link)


  public:
    /**
     * Set the facebook id of this post
     * @param id the facebook id
     */
    void setId( const QString &id);
    /**
     * Returns the facebook id
     */
    QString id() const;

    /**
     * Set who wrote the post
     * @param from the creator of the post
     */
    void setFrom( const QVariantMap &from);
    /**
     * Returns the creator of the post
     */
    QVariantMap from() const;

    /**
     * Set the app who wrote the post
     * @param app the app that created the post
     */
    void setApplication( const QVariantMap &app);
    /**
     * Returns the creator app of the post
     */
    QVariantMap application() const;
    /**
     * Set the id of app used to write the post
     * @param appId id of the creator app of the post
     */
    void setAppId( const QString &appId);
    /**
     * Returns the app id of creator app of the post
     */
    QString appId() const;

    /**
     * Set name of app who wrote the post
     * @param AppName of the creator app of the post
     */
    void setAppName( const QString &AppName);
    /**
     * Returns appName of the creator app of the post
     */
    QString appName() const;

   
	
    /**
     * Set who wrote the post
     * @param senderId the creator of the post
     */
    void setSenderId( const QString &senderId);
    /**
     * Returns the creator of the post
     */
    QString senderId() const;

    /**
     * Set who wrote the post
     * @param sendrName the creator of the post
     */
    void setSenderName( const QString &senderName);
    /**
     * Returns the creator of the post
     */
    QString senderName() const;

    /**
     * Set name of post
     * @param name  of the post
     */
    void setName( const QString &name);
    /**
     * Returns name of the post
     */
    QString name() const;

    /**
     * Set type of post
     * @param type  of the post
     */
    void setType( const QString &type);
    /**
     * Returns type of the post
     */
    QString type() const;

    /**
     * Set picture url of  author of the post
     * @param picture url - url of  author of the post
     */
    void setPictureUrl( const QString &pictureUrl);
    /**
     * Returns the picture url of  author of the post
     */
    QString pictureUrl() const;
    	
    /**
     * Set description of the post
     * @param description the description of the post
     */
    void setDescription( const QString &description);
    /**
     * Returns the description of the post
     */
    QString description() const;

    /**
     * Set link associated the post
     * @param link the link of the post
     */
    void setLink( const QString &link);
    /**
     * Returns the Link of the post
     */
    QString link() const;
    /**
     * Set the actual content of the post
     * @param message The actual content of the post
     */
    void setMessage( const QString &message);
    /**
     * Returns the content of the post.
     */
    QString message() const;

    /**
     * Set the creation time of the post
     * @param createdTime Time in "facebook format"
     */
    void setCreatedTimeString( const QString &createdTime );
    /**
     * Returns the creation time as a string in "facebook format"
     */
    QString createdTimeString() const;
    /**
     * Returns the creation time in KDateTime
     */
    KDateTime createdTime() const;

    /**
     * Set the time of the last update of the post
     * @param updatedTime The time, in "facebook format", of the last update of
     *                    the post.
     */
    void setUpdatedTimeString( const QString &updatedTime );
    /**
     * Returns the time of the last update of the post in "facebook format"
     */
    QString updatedTimeString() const;
    /**
     * Returns the time of the last update of the post as a KDateTime
     */
    KDateTime updatedTime() const;

    

  private:
    QString mId;          /* Facebook id of the post. */
    QString mSenderId;          /* Facebook id of the post. */
    QString mSenderName;          /* Facebook id of the post. */
    QVariantMap mFrom;        /* Creator of the post. */
    QString mLink;     /* Link associated with the post */
    QString mType;     /* Type of  post */	
    QString mName; /* Name of the Link */
    QString mDescription; /* Description of the Link. */
    QString mPictureUrl; /* Picture assocauted with the Post. */
    QVariantMap mApplication; /*App associated with the post*/
    QString mAppName; /* App Name*/
    QString mAppId; /*App id*/		    
    QString mMessage;     /* Actual content of the post. */
    QString mCreatedTime; /* Creation time of the post. */
    QString mUpdatedTime; /* Last update time of the post. */
};

typedef QSharedPointer<PostInfo> PostInfoPtr;

#endif
