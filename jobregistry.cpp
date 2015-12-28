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
#include "nulljob.h"

using namespace Model;

JobRegistry::JobRegistry(QObject *parent) : QObject(parent), m_jobList() {
    m_jobList.append(createGenericJob("Ant tamer", 11.0));
    m_jobList.append(createGenericJob("Pea counter", 12.0));
    m_jobList.append(createGenericJob("Dish washer", 13.0));
    m_jobList.append(createGenericJob("Car washer", 13.5));
    m_jobList.append(createGenericJob("Gorgonzola tester", 1000.0));
}

JobRegistry::~JobRegistry() {}

const JobRegistry &JobRegistry::instance() {
    static JobRegistry inst;
    return inst;
}

const IJob *JobRegistry::findJob(const Player &player) const {
    return m_jobList.at(qrand() % m_jobList.size());
}

const IJob *JobRegistry::createNullJob() const {
    return &NullJob::instance();
}

const IJob *JobRegistry::createGenericJob(const QString &name, qreal payment) const {
    return new GenericJob(payment, name);
}
