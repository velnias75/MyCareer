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

#ifndef MONEY_H
#define MONEY_H

#include <QObject>

namespace Model {

class Money : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal amount READ amount WRITE setAmount NOTIFY amountChanged)

public:
    explicit Money(qreal amount, QObject *parent = 0);

    Money &operator=(const Money &o);

signals:
    void amountChanged(qreal amount);

public slots:
    qreal amount() const;
    void setAmount(qreal amount);

private:
    qreal m_amount;

};

}

#endif // MONEY_H
