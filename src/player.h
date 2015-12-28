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

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "expenses.h"
#include "health.h"
#include "money.h"
#include "age.h"

namespace Model {

class IJob;
class IEducation;

class Player : public QObject {

    Q_OBJECT
    Q_PROPERTY(Money money READ money NOTIFY moneyChanged)
    Q_PROPERTY(const IJob* job WRITE setJob READ job NOTIFY jobChanged)
    Q_PROPERTY(Expenses expenses READ expenses NOTIFY expensesChanged)
    Q_PROPERTY(Health health READ health NOTIFY healthChanged)
    Q_PROPERTY(Age age READ age NOTIFY ageChanged)
    Q_PROPERTY(const IEducation* IEducation WRITE setEducation READ education
               NOTIFY educationChanged)

public:
    explicit Player(QObject *parent = 0);

    Player &operator=(const Player &o);

signals:
    void dead();
    void moneyChanged(const Model::Money &);
    void jobChanged(const Model::IJob *);
    void expensesChanged(const Model::Expenses &);
    void healthChanged(const Model::Health &);
    void ageChanged(const Model::Age &);
    void educationChanged(const Model::IEducation *);

public slots:
    void increaseDay();

    const Money &money() const;
    const Expenses &expenses() const;
    const Health &health() const;
    const Age &age() const;

    const IEducation *education() const;
    void setEducation(const IEducation *IEducation);

    const IJob *job() const;
    void setJob(const IJob *job);

private slots:
    void die();

    void yearsChanged(uint);
    void healthValueChanged(unsigned char);
    void moneyValueChanged(qreal money);
    void expensesValueChanged(qreal expenses);

private:
    const qreal m_interestRate;
    Money m_money;
    const IJob *m_job;
    Expenses m_expenses;
    Health m_health;
    Age m_age;
    const IEducation *m_education;
};

}

#endif // PLAYER_H
