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

#include "jobregistry.h"

#include "genericjob.h"
#include "ieducation.h"
#include "nulljob.h"
#include "player.h"

using namespace Model;

JobRegistry::JobRegistry(QObject *parent) : QObject(parent), m_jobList() {

    QList<IJob *> jobs;

    jobs.append(createGenericJob("Tree washer", 52.0, 0u));
    jobs.append(createGenericJob("Ant tamer", 11.0, 0u));
    jobs.append(createGenericJob("Rain drop counter", 57.0, 0u));
    jobs.append(createGenericJob("Candle blower", 60.0, 0u));

    m_jobList.insert(0u, jobs);
    jobs.clear();

    jobs.append(createGenericJob("Repairer of soda cans", 85.0, 1u));
    jobs.append(createGenericJob("Tape rewinder", 20.0, 1u));
    jobs.append(createGenericJob("Glass welder", 90.0, 1u));
    jobs.append(createGenericJob("DVD rewinder", 100.0, 1u));

    m_jobList.insert(1u, jobs);
    jobs.clear();

    jobs.append(createGenericJob("Astronomer", 600.0, 2u));
    jobs.append(createGenericJob("Transcendental adviser", 800.0, 2u));

    m_jobList.insert(2u, jobs);
}

JobRegistry::~JobRegistry() {

    foreach (const QList<IJob *> &l, m_jobList) {
        foreach(const IJob *j, l) delete j;
    }
}

const JobRegistry &JobRegistry::instance() {
    static JobRegistry inst;
    return inst;
}

uchar JobRegistry::findJob(const Player &player) const {

    m_searchStartDay = player.age().days();
    m_eduLevel = player.gainedEduLevel();

    QObject::connect(&player.age(), SIGNAL(daysChanged(ulong)),
                     this, SLOT(searchDaysChanged(ulong)));

    return (m_searchDuration = (10 + (qrand() % 19)));
}

void JobRegistry::searchDaysChanged(ulong d) {

    if(d >= m_searchStartDay + m_searchDuration) {

        QList<IJob *> jl(m_jobList[m_eduLevel]);
        IJob *j = jl.at(qrand() % m_jobList.size());

        emit jobFound(!(qrand() & 1) && j->minLevel() == m_eduLevel ? j : 0L);
    }
}

IJob *JobRegistry::createNullJob() const {
    return &NullJob::instance();
}

IJob *JobRegistry::createGenericJob(const QString &name, qreal payment, uint minLevel) const {
    return new GenericJob(payment, name, minLevel);
}
