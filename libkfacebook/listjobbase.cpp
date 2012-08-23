/* Copyright 2011 Thomas McGuire <mcguire@kde.org>

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

#include "listjobbase.h"

#include <QVariant>

using namespace KFacebook;

ListJobBase::ListJobBase(const QString &path, const QString &accessToken, bool multiQuery)
    : FacebookGetJob(path, accessToken)
{
    m_multiQuery = multiQuery;
}

void ListJobBase::handleData(const QVariant &root)
{
    if (!m_multiQuery) {
        handleItems(root);
    } else {
        const QVariant data = root.toMap()["data"];
        foreach(const QVariant &user, data.toList()) {
            handleItem(user);
        }
    }

    const QVariant paging = root.toMap()["paging"];
    m_nextPage = paging.toMap().value("next").toString();
    m_prevPage = paging.toMap().value("previous").toString();
}

void ListJobBase::handleItems(const QVariant &root)
{
}

QString ListJobBase::nextItems() const
{
    return m_nextPage;
}

QString ListJobBase::previousItems() const
{
    return m_prevPage;
}
