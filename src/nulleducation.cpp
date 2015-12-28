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

#include "nulleducation.h"

#include "age.h"
#include "money.h"

using namespace Model;

NullEducation::NullEducation(QObject *parent) : AbstractEducation(Money(0.0), Age(), parent) {}

NullEducation &NullEducation::instance() {
    static NullEducation inst;
    return inst;
}

bool NullEducation::isAvailable(qreal) const {
    return false;
}

bool NullEducation::isInProgress() const {
    return false;
}

void NullEducation::setInProgress(bool) {}

void NullEducation::ageDaysChanged(ulong) {}

QString NullEducation::name() const {
    return "Educated fool";
}

ulong NullEducation::days() const {
    return 1ul;
}

qreal NullEducation::cost() const {
    return 0.0;
}

qreal NullEducation::extraExpense() const {
    return 0.0;
}

ulong NullEducation::currentDay() const {
    return 0ul;
}

ulong NullEducation::targetDay() const {
    return 1ul;
}

bool NullEducation::succeeded() const {
    return true;
}
