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

#ifndef ABSTRACTEDUCATION_H
#define ABSTRACTEDUCATION_H

#include "ieducation.h"

namespace Model {

class Age;
class Money;

class AbstractEducation : public IEducation {
    Q_OBJECT

protected:
    explicit AbstractEducation(const Money &money, const Age &age, QObject *parent = 0L);

    virtual bool isAvailable(qreal money) const = 0;

    const Age &age() const;

protected slots:
    virtual void ageDaysChanged(ulong days) = 0;

private slots:
    void moneyAmountChanged(qreal amount);

private:
    const Money &m_money;
    const Age &m_age;
};

}

#endif // ABSTRACTEDUCATION_H
