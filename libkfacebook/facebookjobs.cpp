/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>
   Copyright 2011 Roeland Jago Douma <unix@rullzer.com>

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
#include "facebookjobs.h"

#include <qjson/parser.h>

#include <KIO/Job>
#include <KDebug>
#include <KLocale>

namespace KFacebook {

/*
 * FacebookJobs base class
 */
FacebookJob::FacebookJob(const QString &path, const QString &accessToken)
    : m_accessToken(accessToken),
      m_path(path)
{
    Q_ASSERT(m_path.startsWith('/'));
    setCapabilities(KJob::Killable);
}

FacebookJob::FacebookJob(const QString &accessToken)
    : m_accessToken(accessToken)
{
}

void FacebookJob::addQueryItem(const QString &key, const QString &value)
{
    QueryItem item;
    item.first = key;
    item.second = value;
    m_queryItems.append(item);
}

bool FacebookJob::doKill()
{
    if (m_job) {
        m_job->kill(KJob::Quietly);
    }

    return KJob::doKill();
}

void FacebookJob::handleError(const QVariant &data)
{
    const QVariantMap errorMap = data.toMap();
    const QString type = errorMap["type"].toString();
    const QString message = errorMap["message"].toString();

    kWarning() << "An error of type" << type << "occurred:" << message;

    if (type.toLower() != "oauthexception") {
        setError(KJob::UserDefinedError);
        setErrorText(i18n("The Facebook server returned an error of type <i>%1</i>: <i>%2</i>" , type, message));
    } else {
        setError(AuthenticationProblem);
        setErrorText(i18n("Unable to login to the Facebook server, authentication failure.\nThe server said: <i>%1</i>", message));
    }
}

/*
 * Facebook Add Job
 */
FacebookAddJob::FacebookAddJob(const QString &path, const QString &accessToken)
    : FacebookJob(path, accessToken)
{
}

void FacebookAddJob::start()
{
    KUrl url;
    url.setProtocol("https");
    url.setHost("graph.facebook.com");
    url.setPath(m_path);

    url.addQueryItem("access_token", m_accessToken);

    foreach (const QueryItem &item, m_queryItems) {
        url.addQueryItem(item.first, item.second);
    }

    kDebug() << "Starting add: " << url;
    KIO::StoredTransferJob * const job = KIO::storedHttpPost(QByteArray(), url, KIO::HideProgressInfo);
    m_job = job;
    connect(job, SIGNAL(result(KJob*)), this, SLOT(jobFinished(KJob*)));
    job->start();
}

void FacebookAddJob::jobFinished(KJob *job)
{
    KIO::StoredTransferJob *addJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(addJob);
    if (addJob->error()) {
        setError(addJob->error());
        setErrorText(KIO::buildErrorString(error(), addJob->errorText()));
        kWarning() << "Job error: " << addJob->errorString();
    } else {
        QJson::Parser parser;
        bool ok;
        const QVariant result = parser.parse(addJob->data(), &ok);
        if (!ok) {
            kWarning() << "Unable to parse JSON data: " << QString::fromAscii(addJob->data().data());
            setError(KJob::UserDefinedError);
            setErrorText(i18n("Unable to parse data returned by the Facebook server: %1", parser.errorString()));
        } else {
            const QVariant error = result.toMap()["error"];
            if (error.isValid()) {
                handleError(error);
            } else {
                const QVariantMap dataMap = result.toMap();
                if (dataMap.contains("id")) {
                    setProperty("id", dataMap["id"]);
                }
            }
        }
    }

    emitResult();
    m_job = 0;
}

/*
 * Facebook Delete job
 */
FacebookDeleteJob::FacebookDeleteJob(const QString &id, const QString &accessToken)
    : FacebookJob("/" + id, accessToken)
{
}

void FacebookDeleteJob::start()
{
    KUrl url;
    url.setProtocol("https");
    url.setHost("graph.facebook.com");
    url.setPath(m_path);

    url.addQueryItem("access_token", m_accessToken);
    url.addQueryItem("method", "delete");

    kDebug() << "Starting delete: " << url;
    KIO::StoredTransferJob * const job = KIO::storedHttpPost(QByteArray(), url, KIO::HideProgressInfo);
    m_job = job;
    connect(job, SIGNAL(result(KJob*)), this, SLOT(jobFinished(KJob*)));
    job->start();
}

void FacebookDeleteJob::jobFinished(KJob *job)
{
    KIO::StoredTransferJob *deleteJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(deleteJob);
    if (deleteJob->error()) {
        setError(deleteJob->error());
        setErrorText(KIO::buildErrorString(error(), deleteJob->errorText()));
        kWarning() << "Job error: " << deleteJob->errorString();
    } else {
        // TODO: error handling. Does the server return the error as a JSON string?
    //     kDebug() << "Got data: " << QString::fromAscii(deleteJob->data().data());
    }

    emitResult();
    m_job = 0;
}

/*
 * Facebook get job
 */
FacebookGetJob::FacebookGetJob(const QString &path, const QString &accessToken)
    : FacebookJob(path, accessToken)
{
}

FacebookGetJob::FacebookGetJob(const QString &accessToken)
    : FacebookJob(accessToken)
{
}

void FacebookGetJob::setIds(const QStringList &ids)
{
    m_ids = ids;
}

void FacebookGetJob::setFields(const QStringList &fields)
{
    m_fields = fields;
}

void FacebookGetJob::start()
{
    Q_ASSERT(m_ids.isEmpty() ^ m_path.isEmpty());
    KUrl url;
    url.setProtocol("https");
    url.setHost("graph.facebook.com");
    if (!m_path.isEmpty()) {
        url.setPath(m_path);
    } else {
        url.setPath("/");
        url.addQueryItem("ids", m_ids.join(","));
    }

    url.addQueryItem("access_token", m_accessToken);

    if (!m_fields.isEmpty()) {
        url.addQueryItem("fields", m_fields.join(","));
    }

    foreach (const QueryItem &item, m_queryItems) {
        url.addQueryItem(item.first, item.second);
    }

    kDebug() << "Starting query" << url;
    KIO::StoredTransferJob * const job = KIO::storedGet(url, KIO::Reload, KIO::HideProgressInfo);
    m_job = job;
    connect(job, SIGNAL(result(KJob*)), this, SLOT(jobFinished(KJob*)));
    job->start();
}

void FacebookGetJob::jobFinished(KJob *job)
{
    KIO::StoredTransferJob *transferJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(transferJob);
    if (transferJob->error()) {
        setError(transferJob->error());
        setErrorText(KIO::buildErrorString(error(), transferJob->errorText()));
        kWarning() << "Job error: " << transferJob->errorString();
    } else {
    //     kDebug() << "Got data: " << QString::fromAscii(transferJob->data().data());
        QJson::Parser parser;
        bool ok;
        const QVariant data = parser.parse(transferJob->data(), &ok);
        if (ok) {
            const QVariant error = data.toMap()["error"];
            if (error.isValid()) {
                handleError(error);
            } else {
                handleData(data);
            }
        } else {
            kWarning() << "Unable to parse JSON data: " << QString::fromAscii(transferJob->data().data());
            setError(KJob::UserDefinedError);
            setErrorText(i18n("Unable to parse data returned by the Facebook server: %1", parser.errorString()));
        }
    }

    emitResult();
    m_job = 0;
}

/*
 * FacebookGetIdJob
 */
FacebookGetIdJob::FacebookGetIdJob(const QStringList &ids, const QString &accessToken)
    : FacebookGetJob(accessToken),
      m_multiQuery(true)
{
    setIds(ids);
}

FacebookGetIdJob::FacebookGetIdJob(const QString &id, const QString &accessToken)
    : FacebookGetJob("/" + id, accessToken),
      m_multiQuery(false)
{
}

void FacebookGetIdJob::handleData(const QVariant &data)
{
    if (!m_multiQuery) {
        handleSingleData(data);
    } else {
        foreach (const QVariant &item, data.toMap()) {
            handleSingleData(item);
        }
    }
}

}

#include "facebookjobs.moc"
