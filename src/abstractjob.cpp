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

#include "abstractjob.h"

using namespace Model;

AbstractJob::AbstractJob(qreal payment, QObject *parent) : IJob(parent), m_payment(payment) {}

const Money &AbstractJob::payment() const {
    return m_payment;
}

void AbstractJob::addQualitySample(int quality) {
    m_qualitySamples.append(quality);
}

void AbstractJob::clearQuality() {
    m_qualitySamples.clear();
}

int AbstractJob::averageQuality() const {

    if(m_qualitySamples.isEmpty()) return 100;

    int s = 0;

    foreach (const int i, m_qualitySamples) s += i;

    return s/m_qualitySamples.size();
}
