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

#include "abstracteducation.h"

#include "money.h"

using namespace Model;

AbstractEducation::AbstractEducation(const Money &money, const Age &age, QObject *parent) :
    IEducation(parent), m_money(money), m_age(age) {

    QObject::connect(&m_money, SIGNAL(amountChanged(qreal)),
                     this, SLOT(moneyAmountChanged(qreal)));
}

void AbstractEducation::moneyAmountChanged(qreal amount) {
    if(isAvailable(amount)) emit available(this);
}

const Age &AbstractEducation::age() const {
    return m_age;
}
