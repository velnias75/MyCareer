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

#include "age.h"

using namespace Model;

Age::Age(QObject *parent) : QObject(parent), m_days(6570ul) {}

Age &Age::operator=(const Age &o) {

    if(this != &o) {
        m_days = o.m_days;
    }

    return *this;
}

void Age::increaseDay() {

    ++m_days;

    emit yearsChanged(years());
    emit daysChanged(m_days);

    if(m_days >= 36500ul) emit dead();
}

ulong Age::days() const {
    return m_days;
}

uint Age::years() const {
    return days() / 365ul;
}
