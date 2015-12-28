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

#include "money.h"

using namespace Model;

Money::Money(qreal amount, QObject *parent) : QObject(parent), m_amount(amount) {}

Money &Money::operator=(const Money &o) {

    if(this != &o) {
        setAmount(o.amount());
    }

    return *this;
}

qreal Money::amount() const {
    return m_amount;
}

void Money::setAmount(qreal amount) {
    m_amount = amount;
    emit amountChanged(m_amount);
}
