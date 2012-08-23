/* Copyright 2011 Roeland Jago Douma <unix@rullzer.com>

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

#include "noteinfo.h"

#include "util.h"

#include <KDebug>
#include <KLocalizedString>
#include <KPIMUtils/LinkLocator>

using namespace KFacebook;

void NoteInfo::setId(const QString &id)
{
    m_id = id;
}

KMime::Message::Ptr NoteInfo::asNote() const
{
    KMime::Message * const note = new KMime::Message();

    QString m = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
    m += "<html><head></head><body>\n";
    m += message();
    m += "</body>";

    note->contentType()->setMimeType("text/html");
    note->contentType()->setCharset("utf-8");
    note->fromUnicodeString(m);
    note->date()->fromUnicodeString(updatedTime().toString(KDateTime::RFCDateDay), "utf-8");
    note->subject()->fromUnicodeString(subject(), "utf-8");
    note->from()->fromUnicodeString("you@facebook", "utf-8");
    note->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);

    note->assemble();

    return KMime::Message::Ptr(note);
}

QString NoteInfo::id() const
{
    return m_id;
}

void NoteInfo::setFrom(const QString &from)
{
    m_from = from;
}

QString NoteInfo::from() const
{
    return m_from;
}

void NoteInfo::setSubject(const QString &subject)
{
    m_subject = subject;
}

QString NoteInfo::subject() const
{
    return m_subject;
}

void NoteInfo::setMessage(const QString &message)
{
    m_message = message;
}

QString NoteInfo::message() const
{
    return m_message;
}

void NoteInfo::setCreatedTimeString(const QString &createdTime)
{
    m_createdTime = createdTime;
}

QString NoteInfo::createdTimeString() const
{
    return m_createdTime;
}

KDateTime NoteInfo::createdTime() const
{
    return facebookTimeToKDateTime(m_createdTime);
}

void NoteInfo::setUpdatedTimeString(const QString &updatedTime)
{
    m_updatedTime = updatedTime;
}

QString NoteInfo::updatedTimeString() const
{
    return m_updatedTime;
}

KDateTime NoteInfo::updatedTime() const
{
    return facebookTimeToKDateTime(m_updatedTime);
}
