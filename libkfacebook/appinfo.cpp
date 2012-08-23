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

#include "appinfo.h"

using namespace KFacebook;

void AppInfo::setId(const QString &id)
{
    m_id = id;
}

QString AppInfo::id() const
{
    return m_id;
}

void AppInfo::setName(const QString &name)
{
    m_name = name;
}

QString AppInfo::name() const
{
    return m_name;
}

void AppInfo::setDescription(const QString &description)
{
    m_description = description;
}

QString AppInfo::description() const
{
    return m_description;
}

void AppInfo::setCategory(const QString &category)
{
    m_category = category;
}

QString AppInfo::category() const
{
    return m_category;
}

void AppInfo::setCompany(const QString &company)
{
    m_company = company;
}

QString AppInfo::company() const
{
    return m_company;
}

void AppInfo::setIconUrl(const QString &iconUrl)
{
    m_iconUrl = iconUrl;
}

QString AppInfo::iconUrl() const
{
    return m_iconUrl;
}

void AppInfo::setSubcategory(const QString &subCategory)
{
    m_subcategory = subCategory;
}

QString AppInfo::subcategory() const
{
    return m_subcategory;
}

void AppInfo::setLink(const QString &link)
{
    m_link = link;
}

QString AppInfo::link() const
{
    return m_link;
}

void AppInfo::setLogoUrl(const QString &logoUrl)
{
    m_logoUrl = logoUrl;
}

QString AppInfo::logoUrl() const
{
    return m_logoUrl;
}
