/* Copyright 2011 Roeland Jago Douma <unix@rullzer.com>

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

#include "settings.h"

#include <libkfacebook/messagejob.h>
#include <libkfacebook/allmessageslistjob.h>

#include <Akonadi/Item>
#include <KLocalizedString>

using namespace Akonadi;

void FacebookResource::messageJobFinished(KJob *job)
{
  Q_ASSERT( !mIdle );
  Q_ASSERT( mCurrentJobs.indexOf(job) != -1 );
  MessageJob * const messageJob = dynamic_cast<MessageJob *>( job );
  Q_ASSERT(messageJob);
  mCurrentJobs.removeAll(job);

  if (messageJob->error()) {
    abortWithError( i18n( "Unable to fetch thread from server: %1", messageJob->errorText() ) );
  } else {
    mNumMessagesFetched++;
    const MessageInfoPtr msg = messageJob->messageInfo();

    Item newMessage;
    newMessage.setRemoteId( msg->id() );
    newMessage.setMimeType( "message/rfc822" );
    newMessage.setPayload<KMime::Message::Ptr>( msg->asMessage() );
    itemsRetrievedIncremental( Item::List() << newMessage, Item::List() );

    /*
     * replies
     */
    foreach (const MessageReplyInfoPtr &reply, msg->replies()) {
      Item newReply;
      newReply.setRemoteId( reply->id() );
      newReply.setMimeType( "message/rfc822" );
      newReply.setPayload<KMime::Message::Ptr>( reply->asMessage() );
      itemsRetrievedIncremental( Item::List() << newReply, Item::List() );
    }

    if (mNumMessagesFetched < mNumMessages) {
      const float percentageDone = mNumMessagesFetched / (float)mNumMessages * 100.0f;
      emit percent(10 + percentageDone * 0.9f);
    } else {
      itemsRetrievalDone();
      finishMessageFetching();
    }

  }
}

void FacebookResource::messageListFetched(KJob *job)
{
  Q_ASSERT(!mIdle);
  Q_ASSERT( mCurrentJobs.indexOf(job) != -1 );
  AllMessagesListJob * const messagesJob = dynamic_cast<AllMessagesListJob*>( job );
  Q_ASSERT( messagesJob );
  mCurrentJobs.removeAll(job);

  if ( job->error() ) {
    abortWithError( i18n( "Unable to get list of messages from server: %1", job->errorText() ),
                    job->error() == FacebookJob::AuthenticationProblem );
  } else {
    setItemStreamingEnabled( true );
    mNumMessagesFetched = 0;
    mNumMessages = messagesJob->allMessages().size();
    kDebug() << "Fetched " << mNumMessages << "messages";

    /*
     * TODO: do real updating instead of parsing everything here
     */
    mNewOrChangedMessages.append(messagesJob->allMessages());

    if (mNewOrChangedMessages.isEmpty()) {
      itemsRetrievalDone();
      finishMessageFetching();
    } else {
      emit percent(10);
      emit status( Running, i18n("Retrieving message threads."));
      fetchNewOrChangedMessages();
    }
  }
}

void FacebookResource::finishMessageFetching()
{
  Q_ASSERT(mCurrentJobs.size() == 0);
  Q_ASSERT(mNumMessages == mNumMessagesFetched);

  emit percent(100);
  if ( mNumMessages > 0 ) {
    emit status( Idle, i18np( "Updated one message from the server.",
                              "Updated %1 messages from the server.", mNumMessages ) );
  } else {
    emit status( Idle, i18n( "Finished, no messages needed to be updated." ) );
  }
  resetState();
}

void FacebookResource::fetchNewOrChangedMessages()
{
  /*
   * Fetch all message threads in parallel
   * TODO: Bad idea, Facebook limits mailbox_fql calls to 300 per 600 seconds, so we might even
   *       need artifical delay here :(
   */
  foreach(const MessageInfoPtr &msg, mNewOrChangedMessages) {
    MessageJob * const messageJob = new MessageJob( msg->id(), Settings::self()->accessToken() );
    mCurrentJobs << messageJob;
    connect(messageJob, SIGNAL(result(KJob*)), this, SLOT(messageJobFinished(KJob *)));
    messageJob->start();
  }
}