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

#ifndef GENERICJOB_H
#define GENERICJOB_H

#include "abstractjob.h"

namespace Model {

class GenericJob : public AbstractJob {
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(Money payment READ payment)
    Q_PROPERTY(uint minLevel READ minLevel)

    friend class JobRegistry;

public slots:
    virtual QString name() const;
    virtual uint minLevel() const;

protected:
    explicit GenericJob(qreal payment, const QString &name, uint minLevel, QObject *parent = 0L);

private:
    QString m_name;
    uint m_minLevel;
};

}

#endif // GENERICJOB_H
