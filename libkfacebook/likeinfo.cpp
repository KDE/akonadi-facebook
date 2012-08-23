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

#include "likeinfo.h"

using namespace KFacebook;

void LikeInfo::setData(const QVariantList &data)
{
    m_data =  QList<UserInfoPtr>();

    foreach(const QVariant &v, data) {
        QVariantMap vMap = v.toMap();
        UserInfoPtr userInfo(new UserInfo());
        QJson::QObjectHelper::qvariant2qobject(vMap, userInfo.data());
        m_data << userInfo;
    }
}

QList<UserInfoPtr> LikeInfo::data() const
{
    return m_data;
}

QVariantList LikeInfo::dataList() const
{
    QVariantList list;

    foreach(const UserInfoPtr &user, m_data) {
        list.append(QJson::QObjectHelper::qobject2qvariant(user.data()));
    }

    return list;
}

void LikeInfo::setCount(const int &count)
{
    m_count = count;
}

int LikeInfo::count() const
{
    return m_count;
}

QString LikeInfo::path() const
{
    return "/likes";
}
