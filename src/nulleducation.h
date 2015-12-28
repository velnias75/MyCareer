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

#ifndef NULLEDUCATION_H
#define NULLEDUCATION_H

#include "abstracteducation.h"

namespace Model {

class NullEducation : public AbstractEducation {
    Q_OBJECT
    Q_PROPERTY(QString name READ name)

public:
    static NullEducation &instance();

public slots:
    virtual QString name() const;
    virtual bool isInProgress() const;
    virtual void setInProgress(bool);
    virtual ulong days() const;
    virtual ulong currentDay() const;
    virtual ulong targetDay() const;
    virtual bool succeeded() const;
    virtual qreal cost() const;
    virtual qreal extraExpense() const;
    virtual uint level() const;

protected slots:
    virtual void ageDaysChanged(ulong days);

private:
    explicit NullEducation(QObject *parent = 0);

protected:
    virtual bool isAvailable(qreal) const;
};

}

#endif // NULLEDUCATION_H
