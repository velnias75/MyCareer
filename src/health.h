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

#ifndef HEALTH_H
#define HEALTH_H

#include <QObject>

namespace Model {

class Health : public QObject {
    Q_OBJECT
    Q_PROPERTY(uchar value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit Health(QObject *parent = 0);

    Health &operator=(const Health &o);

signals:
    void dead();
    void valueChanged(uchar value);

public slots:
    uchar value() const;
    void setValue(uchar value);

private:
    uchar m_value;
};

}

#endif // HEALTH_H
