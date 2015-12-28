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
    m_jobList.append(createGenericJob("Tree washer", 52.0, 0u));
    m_jobList.append(createGenericJob("Rain drop counter", 57.0, 0u));
    m_jobList.append(createGenericJob("Candle blower", 60.0, 0u));
    m_jobList.append(createGenericJob("Repairer of soda cans", 85.0, 1u));
    m_jobList.append(createGenericJob("Glass welder", 90.0, 1u));
    m_jobList.append(createGenericJob("DVD rewinder", 100.0, 1u));

    m_jobList.append(createGenericJob("Astronomer", 600.0, 2u));
    m_jobList.append(createGenericJob("Transcendental adviser", 800.0, 2u));
}

JobRegistry::~JobRegistry() {
    foreach (const IJob *j, m_jobList) delete j;
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
        IJob *j = m_jobList.at(qrand() % m_jobList.size());
        emit jobFound(j->minLevel() == m_eduLevel ? j : 0L);
    }
}

IJob *JobRegistry::createNullJob() const {
    return &NullJob::instance();
}

IJob *JobRegistry::createGenericJob(const QString &name, qreal payment, uint minLevel) const {
    return new GenericJob(payment, name, minLevel);
}
