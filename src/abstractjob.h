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

#ifndef ABSTRACTJOB_H
#define ABSTRACTJOB_H

#include "ijob.h"

namespace Model {

class AbstractJob : public IJob {
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(Money payment READ payment)

public slots:
    virtual QString name() const = 0;
    virtual const Money &payment() const;
    virtual void addQualitySample(int quality);

public:
    virtual int averageQuality() const;
    virtual void clearQuality();

protected:
    explicit AbstractJob(qreal payment, QObject *parent = 0L);

private:
    Money m_payment;
    QList<int> m_qualitySamples;
};

}

#endif // ABSTRACTJOB_H
