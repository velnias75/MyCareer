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

#ifndef GENERICEDUCATION_H
#define GENERICEDUCATION_H

#include "abstracteducation.h"

namespace Model {

class GenericEducation : public AbstractEducation {
    Q_OBJECT
    Q_PROPERTY(bool inProgress READ isInProgress WRITE setInProgress NOTIFY inProgressChanged)
    Q_PROPERTY(ulong currentDay READ currentDay NOTIFY currentDayChanged)
    Q_PROPERTY(ulong targetDay READ targetDay)
    Q_PROPERTY(qreal cost READ cost)
    Q_PROPERTY(qreal extraExpense READ extraExpense)

    friend class EducationRegistry;

signals:
    void inProgressChanged(bool);
    void currentDayChanged(ulong);

public slots:
    virtual QString name() const;
    virtual bool isInProgress() const;
    virtual void setInProgress(bool progress);
    virtual ulong days() const;
    virtual ulong currentDay() const;
    virtual ulong targetDay() const;
    virtual bool succeeded() const;
    virtual qreal cost() const;
    virtual qreal extraExpense() const;

protected slots:
    virtual void ageDaysChanged(ulong days);

protected:
    explicit GenericEducation(const Money &money, const Age &age, qreal amount,
                              qreal extraExpense, ulong days, const QString &name,
                              QObject *parent = 0);

    virtual bool isAvailable(qreal money) const;

private:
    const qreal m_amount;
    const QString m_name;
    bool m_isInProgress;
    ulong m_days;
    ulong m_currentDay;
    ulong m_targetDay;
    ulong m_startDay;
    bool m_succeeded;
    qreal m_extraExpense;
};

}

#endif // GENERICEDUCATION_H
