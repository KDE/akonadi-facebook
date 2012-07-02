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
#ifndef KFACEBOOK_POSTINFO_H
#define KFACEBOOK_POSTINFO_H

#include "libkfacebook_export.h"
#include <qjson/qobjecthelper.h>
#include "userinfo.h"
#include "propertyinfo.h"
#include "appinfo.h"
#include "commentinfo.h"
#include "likeinfo.h"

#include <KDateTime>
#include <QObject>

namespace KFacebook {

/**
 * Class to represent a facebook post.
 * See https://developers.facebook.com/docs/reference/api/post/
 */

class LIBKFACEBOOK_EXPORT PostInfo : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id WRITE setId READ id)
  Q_PROPERTY(QVariantMap from WRITE setFrom )
  Q_PROPERTY(QString message WRITE setMessage READ message)
  Q_PROPERTY(QString picture WRITE setPictureUrl READ pictureUrl)
  Q_PROPERTY(QString link WRITE setLink READ link)
  Q_PROPERTY(QString name WRITE setName READ name)
  Q_PROPERTY(QString caption WRITE setCaption READ caption)
  Q_PROPERTY(QString description WRITE setDescription READ description)
  Q_PROPERTY(QString source WRITE setSource READ source)
  Q_PROPERTY(QVariantList properties WRITE setProperties )
  Q_PROPERTY(QString icon WRITE setIcon READ icon)
  Q_PROPERTY(QString type WRITE setType READ type)
  Q_PROPERTY(QVariantMap likes WRITE setLikes )
  Q_PROPERTY(QString story WRITE setStory READ story)
  Q_PROPERTY(QVariantMap comments WRITE setComments )
  Q_PROPERTY(QVariantMap application WRITE setApplication )
  Q_PROPERTY(QString created_time WRITE setCreatedTimeString READ createdTimeString)
  Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)


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
     * Set the user who wrote the post as a QVariantMap
     * @param from the creator of the post
     */
    void setFrom( const QVariantMap &from);
    /**
     * Returns the creator of the post as a User Info Object Pointer
     */
    UserInfoPtr from() const;

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
     * Set picture url of  author of the post
     * @param picture url - url of  author of the post
     */
    void setPictureUrl( const QString &pictureUrl);
    /**
     * Returns the picture url of  author of the post
     */
    QString pictureUrl() const;

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
     * Set name of link
     * @param name  of the link
     */
    void setName( const QString &name);
    /**
     * Returns name of the link
     */
    QString name() const;

	/**
     * Set caption of link
     * @param caption  of the link
     */
    void setCaption( const QString &caption);
    /**
     * Returns caption of the link
     */
    QString caption() const;

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
     * Set source of link ( url of video for e.g.)
     * @param source  of the link
     */
    void setSource( const QString &source);
    /**
     * Returns source of the link
     */
    QString source() const;

	/**
     * Set properties aoosicated with the link ( length of video for e.g )
     * @param properties  of the link
     */
    void setProperties( const QVariantList &properties);
    /**
     * Returns properties of the link
     */
    QList<PropertyInfoPtr> properties() const;

	/**
     * Set icon of post ( represents type of post)
     * @param icon  of post
     */
    void setIcon( const QString &icon);
    /**
     * Returns icon of post
     */
    QString icon() const;

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
     * Set likes of post
     * @param likes  of the post
     */
    void setLikes( const QVariantMap &likes);
    /**
     * Returns likes of the post
     */
    LikeInfoPtr likes() const;
	/**
     * Set story of post ( generated by app)
     * @param story  of the post
     */
    void setStory( const QString &story);
    /**
     * Returns story of the post
     */
    QString story() const;

	/**
     * Set comments of post
     * @param comments  of the post
     */
    void setComments( const QVariantMap &comments);
    /**
     * Returns comments of the post
     */
    CommentInfoPtr comments() const;

	 /**
     * Set the app that created the post
     * @param app the app that created the post
     */
    void setApplication( const QVariantMap &app);
    /**
     * Returns the creator app of the post
     */
    AppInfoPtr application() const;

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

    /*/**
     * Set the id of app used to write the post
     * @param appId id of the creator app of the post
     *
    void setAppId( const QString &appId);
    /**
     * Returns the app id of creator app of the post
     *
    QString appId() const;

    /**
     * Set name of app who wrote the post
     * @param AppName of the creator app of the post
     *
    void setAppName( const QString &AppName);
    /**
     * Returns appName of the creator app of the post
     *
    QString appName() const;



    /**
     * Set who wrote the post
     * @param senderId the creator of the post
     *
    void setSenderId( const QString &senderId);
    /**
     * Returns the creator of the post
     *
    QString senderId() const;

    /**
     * Set who wrote the post
     * @param sendrName the creator of the post
     *
    void setSenderName( const QString &senderName);
    /**
     * Returns the creator of the post
     *
    QString senderName() const;
    */


  private:
    QString mId;          /* Facebook id of the post. */
	UserInfoPtr mFrom;        /* Creator of the post. */
	QString mMessage;     /* Actual content of the post. */
    QString mPictureUrl; /* Picture assocauted with the Post. */
    QString mLink;     /* Link associated with the post */
    QString mName; /* Name of the Link */
	QString mCaption; /* Caption of the Link */
    QString mDescription; /* Description of the Link. */
    QString mSource; /* Source of the Link */
	QList<PropertyInfoPtr> mProperties; /* Properties of the Link */
	QString mIcon; /* Icon of the post */
    QString mType;     /* Type of  post */
    LikeInfoPtr mLikes;     /* Likes of  post */
    QString mStory;     /* Story of  post */
    CommentInfoPtr mComments;     /* Comments on  post */
    AppInfoPtr mApplication; /*App associated with the post*/
    QString mCreatedTime; /* Creation time of the post. */
    QString mUpdatedTime; /* Last update time of the post. */

    //QString mSenderId;          /* Facebook id of the post. */
    //QString mSenderName;          /* Facebook id of the post. */
    //QString mAppName; /* App Name*/
    //QString mAppId; /*App id*/


};

typedef QSharedPointer<PostInfo> PostInfoPtr;

typedef QList<PostInfoPtr> PostInfoList;

}

Q_DECLARE_METATYPE(KFacebook::PostInfo *);

#endif
