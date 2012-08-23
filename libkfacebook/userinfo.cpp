/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>

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
#include "userinfo.h"

#include "util.h"

#include <KDebug>

using namespace KFacebook;

static const int invalidTimezone = 42;

UserInfo::UserInfo()
    : m_timezone(invalidTimezone)
{
}

QString UserInfo::name() const
{
    return m_name;
}

QString UserInfo::id() const
{
    return m_id;
}

void UserInfo::setName(const QString &name)
{
    m_name = name;
}

void UserInfo::setId(const QString &id)
{
    m_id = id;
}

QDate UserInfo::birthday() const
{
    return m_birthday;
}

QString UserInfo::birthdayAsString() const
{
    return m_birthday.toString();
}

QString UserInfo::firstName() const
{
    return m_firstName;
}

QString UserInfo::lastName() const
{
    return m_lastName;
}

void UserInfo::setBirthday(const QString &birthday)
{
    m_birthday = QDate::fromString(birthday, "MM/dd/yyyy");
    if (!m_birthday.isValid()) {
        // Some users don't tell the year of their birthday.
        m_birthday = QDate::fromString(birthday + "/0001", "MM/dd/yyyy");
    }
}

void UserInfo::setFirstName(const QString &firstName)
{
    m_firstName = firstName;
}

void UserInfo::setLastName(const QString &lastName)
{
    m_lastName = lastName;
}

void UserInfo::setWebsite(const QString &website)
{
    if (website.contains('\r') || website.contains('\n')) {
        QString normalized = website;
        normalized.replace("\r\n", "\n");
        normalized.replace("\r", "\n");
        const QStringList websites = normalized.split('\n');
        m_website = websites[0];
    } else {
        m_website = website;
    }
}

void UserInfo::setCity(const QString &city)
{
    m_city = city;
}

void UserInfo::setCountry(const QString &country)
{
    m_country = country;
}


QString UserInfo::website() const
{
    return m_website;
}

QString UserInfo::username() const
{
    return m_username;
}

void UserInfo::setUsername(const QString &username)
{
    m_username = username;
}

QString UserInfo::company() const
{
    return m_company;
}

QString UserInfo::profession() const
{
    return m_profession;
}

void UserInfo::setCompany(const QString &company)
{
    m_company = company;
}

void UserInfo::setProfession(const QString &profession)
{
    m_profession = profession;
}

QString UserInfo::partner() const
{
    return m_partner;
}

void UserInfo::setPartner(const QString &partner)
{
    m_partner = partner;
}

void UserInfo::setTimezone(int timezone)
{
    m_timezone = timezone;
}

int UserInfo::timezone() const
{
    return m_timezone;
}

KABC::Addressee UserInfo::toAddressee() const
{
    KABC::Addressee addressee;
    addressee.setGivenName(firstName());
    addressee.setUid(id());
    addressee.setFamilyName(lastName());
    addressee.setFormattedName(name());
    addressee.setUrl(website());
    addressee.setBirthday(QDateTime(birthday()));
    addressee.setOrganization(m_company);
    if (m_timezone != invalidTimezone) {
        addressee.setTimeZone(KABC::TimeZone(m_timezone));
    }
    addressee.insertCustom("KADDRESSBOOK", "X-Profession", m_profession);
    addressee.insertCustom("KADDRESSBOOK", "X-SpousesName", m_partner);
    if (!m_city.isEmpty() || !m_country.isEmpty()) {
        KABC::Address address(KABC::Address::Home);
        address.setRegion(m_country);
        address.setLocality(m_city);
        addressee.insertAddress(address);
    }
    return addressee;
}

void UserInfo::setUpdatedTimeString(const QString &updatedTime)
{
    m_updatedTime = updatedTime;
}

QString UserInfo::updatedTimeString() const
{
    return m_updatedTime;
}

KDateTime UserInfo::updatedTime() const
{
    return facebookTimeToKDateTime(m_updatedTime);
}

void UserInfo::setPicture(const QUrl &pictureUrl)
{
    m_pictureUrl = pictureUrl;
}

QUrl UserInfo::picture() const
{
    return m_pictureUrl;
}
