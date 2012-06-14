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

#include "appinfo.h"

void AppInfo::setId( const QString &id)
{
  mId = id;
}

QString AppInfo::id() const
{
  return mId;
}

void AppInfo::setName( const QString &name)
{
  mName = name;
}

QString AppInfo::name() const
{
  return mName;
}

void AppInfo::setDescription( const QString &description)
{
  mDescription = description;
}

QString AppInfo::description() const
{
  return mDescription;
}

void AppInfo::setCategory( const QString &category)
{
  mCategory = category;
}

QString AppInfo::category() const
{
  return mCategory;
}

void AppInfo::setCompany( const QString &company)
{
  mCompany = company;
}

QString AppInfo::company() const
{
  return mCompany;
}

void AppInfo::setIconUrl( const QString &iconUrl)
{
  mIconUrl = iconUrl;
}

QString AppInfo::iconUrl() const
{
  return mIconUrl;
}

void AppInfo::setSubCategory( const QString &subCategory)
{
  mSubCategory = subCategory;
}

QString AppInfo::subCategory() const
{
  return mSubCategory;
}

void AppInfo::setLink( const QString &link)
{
  mLink = link;
}

QString AppInfo::link() const
{
  return mLink;
}

void AppInfo::setLogoUrl( const QString &logoUrl)
{
  mLogoUrl = logoUrl;
}

QString AppInfo::logoUrl() const
{
  return mLogoUrl;
}