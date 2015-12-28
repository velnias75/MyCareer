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

#ifndef AGE_H
#define AGE_H

#include <QObject>

namespace Model {

class Age : public QObject {
    Q_OBJECT
    Q_PROPERTY(ulong days READ days NOTIFY daysChanged)
    Q_PROPERTY(uint years READ years NOTIFY yearsChanged)

public:
    explicit Age(QObject *parent = 0);

    Age &operator=(const Age &o);

signals:
    void dead();
    void yearsChanged(uint);
    void daysChanged(ulong);

public slots:
    void increaseDay();

    ulong days() const;
    uint years() const;

private:
    ulong m_days;
};

}

#endif // AGE_H
