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

#include "genericeducation.h"

#include "age.h"

using namespace Model;

GenericEducation::GenericEducation(const Money &money, const Age &age, qreal amount,
                                   qreal extraExpense, ulong days, const QString &name, uint level,
                                   QObject *parent) : AbstractEducation(money, age, parent),
    m_amount(amount), m_name(name), m_isInProgress(false), m_days(days), m_currentDay(0ul),
    m_targetDay(0ul), m_startDay(0ul), m_succeeded(false), m_extraExpense(extraExpense),
    m_level(level) {}

QString GenericEducation::name() const {
    return m_name;
}

bool GenericEducation::isAvailable(qreal money) const {
    return money >= m_amount;
}

bool GenericEducation::isInProgress() const {
    return m_isInProgress;
}

void GenericEducation::setInProgress(bool progress) {

    m_isInProgress = progress;

    if(m_isInProgress) {
        m_startDay = age().days();
        m_targetDay = m_startDay + m_days;
        QObject::connect(&age(), SIGNAL(daysChanged(ulong)), this, SLOT(ageDaysChanged(ulong)));
    }

    emit inProgressChanged(m_isInProgress);
}

void GenericEducation::ageDaysChanged(ulong days) {

    const ulong elapsed = days - m_startDay;

    emit currentDayChanged(elapsed);

    if(elapsed == m_days) {
        m_succeeded = true;
        emit succeededChanged(m_succeeded);
        QObject::disconnect(&age(), SIGNAL(daysChanged(ulong)),
                            this, SLOT(ageDaysChanged(ulong)));
    }
}

ulong GenericEducation::days() const {
    return m_days;
}

qreal GenericEducation::cost() const {
    return m_amount;
}

qreal GenericEducation::extraExpense() const {
    return m_extraExpense;
}

ulong GenericEducation::currentDay() const {
    return m_currentDay;
}

ulong GenericEducation::targetDay() const {
    return m_targetDay;
}

bool GenericEducation::succeeded() const {
    return m_succeeded;
}

uint GenericEducation::level() const {
    return m_level;
}
