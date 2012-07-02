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
#ifndef KFACEBOOK_ALLNOTESLISTJOB_H
#define KFACEBOOK_ALLNOTESLISTJOB_H

#include "pagedlistjob.h"
#include "noteinfo.h"
#include "libkfacebook_export.h"

namespace KFacebook {

class LIBKFACEBOOK_EXPORT AllNotesListJob : public PagedListJob
{
  Q_OBJECT
  public:
    explicit AllNotesListJob( const QString &accessToken );
    QList<NoteInfoPtr> allNotes() const;

  protected:
    virtual void appendItems(const ListJobBase* job);
    virtual ListJobBase* createJob(const KUrl &prev, const KUrl &next);
    virtual bool shouldStartNewJob(const KUrl& prev, const KUrl& next);

  private:
    QList<NoteInfoPtr> mNotes;
};

}

#endif
