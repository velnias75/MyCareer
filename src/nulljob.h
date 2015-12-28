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

#ifndef NULLJOB_H
#define NULLJOB_H

#include "abstractjob.h"

namespace Model {

class NullJob : public AbstractJob {
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(Money payment READ payment)

public:
    static NullJob &instance();

public slots:
    virtual QString name() const;
    virtual void addQualitySample(int quality);
    virtual uint minLevel() const;

private:
    explicit NullJob(QObject *parent = 0L);
};

}

#endif // NULLJOB_H
