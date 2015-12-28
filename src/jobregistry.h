/*
 * Copyright 2015 by Heiko Schäfer <heiko@rangun.de>
 *
 * This file is part of NetMauMau Qt Client.
 *
 * NetMauMau Qt Client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * NetMauMau Qt Client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NetMauMau Qt Client.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JOBREGISTRY_H
#define JOBREGISTRY_H

#include <QObject>
#include <QList>

namespace Model {

class IJob;
class Player;

class JobRegistry : public QObject {
    Q_OBJECT

public:
    static const JobRegistry &instance();

    virtual ~JobRegistry();

    uchar findJob(const Player &player) const;
    IJob *createNullJob() const;

signals:
    void jobFound(Model::IJob *);

private slots:
    void searchDaysChanged(ulong);

private:
    explicit JobRegistry(QObject *parent = 0);

    IJob *createGenericJob(const QString &name, qreal payment, uint minLevel) const;

private:
    QList<IJob *> m_jobList;
    mutable ulong m_searchStartDay;
    mutable ulong m_searchDuration;
    mutable uint m_eduLevel;
};

}

#endif // JOBREGISTRY_H
