/*  Copyright (C) 2012  Martin Klapetek <martin.klapetek@gmail.com>

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

#include "facebookresource.h"
#include <config.h>
#include "settings.h"
#include "settingsdialog.h"
#include "timestampattribute.h"

#include <libkfacebook/postslistjob.h>
#include <libkfacebook/noteaddjob.h>
#include <libkfacebook/postjob.h>

#include <Akonadi/AttributeFactory>
#include <Akonadi/EntityDisplayAttribute>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ChangeRecorder>

using namespace Akonadi;

void FacebookResource::postsListFetched( KJob* job )
{
    Q_ASSERT( !mIdle );
    KFacebook::PostsListJob * const listJob = dynamic_cast<KFacebook::PostsListJob*>( job );
    Q_ASSERT( listJob );
    mCurrentJobs.removeAll(job);

    if ( listJob->error() ) {
        abortWithError( i18n( "Unable to get posts from server: %1", listJob->errorString() ),
                        listJob->error() == KFacebook::FacebookJob::AuthenticationProblem );
    } else {
        setItemStreamingEnabled( true );

        Item::List postItems;
        kDebug() << "Going into foreach";
        foreach( const KFacebook::PostInfoPtr &postInfo, listJob->posts() ) {
            Item post;
            post.setRemoteId( postInfo->id() );
            post.setMimeType( "text/x-vnd.akonadi.statusitem" );
            post.setPayload<KFacebook::PostInfoPtr>( postInfo );
            postItems.append(post);
        }

        itemsRetrieved( postItems );
        itemsRetrievalDone();
        finishPostsFetching();
    }
}

void FacebookResource::finishPostsFetching()
{
    emit percent(100);
    emit status( Idle, i18n( "All posts fetched from server." ) );
    resetState();
}

void FacebookResource::postJobFinished(KJob *job)
{
    Q_ASSERT(!mIdle);
    Q_ASSERT( mCurrentJobs.indexOf(job) != -1 );
    KFacebook::PostJob * const postJob = dynamic_cast<KFacebook::PostJob*>( job );
    Q_ASSERT( postJob );
    Q_ASSERT( postJob->postInfo().size() == 1 );
    mCurrentJobs.removeAll(job);

    if ( postJob->error() ) {
        abortWithError( i18n( "Unable to get information about post from server: %1", postJob->errorText() ) );
    } else {
        Item post = postJob->property( "Item" ).value<Item>();
        post.setPayload( postJob->postInfo().first() );
        itemRetrieved( post );
        resetState();
    }
}
