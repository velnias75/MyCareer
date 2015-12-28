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

#include "ijob.h"
#include "player.h"
#include "ieducation.h"
#include "jobregistry.h"
#include "educationregistry.h"

using namespace Model;

Player::Player(QObject *parent) : QObject(parent),
    m_interestRate(1.0 + (2.0/((qrand() % 1000) + 1))), m_money(2000.0),
    m_job(JobRegistry::instance().createNullJob()), m_expenses(10.0), m_health(), m_age(),
    m_education(EducationRegistry::instance(*this).createNullEducation()) {

    QObject::connect(&m_age, SIGNAL(yearsChanged(uint)), this, SLOT(yearsChanged(uint)));
    QObject::connect(&m_health, SIGNAL(valueChanged(unsigned char)),
                     this, SLOT(healthValueChanged(unsigned char)));
    QObject::connect(&m_money, SIGNAL(amountChanged(qreal)),
                     this, SLOT(moneyValueChanged(qreal)));
    QObject::connect(&m_expenses, SIGNAL(amountChanged(qreal)),
                     this, SLOT(expensesValueChanged(qreal)));

    QObject::connect(&m_age, SIGNAL(dead()), this, SLOT(die()));
    QObject::connect(&m_health, SIGNAL(dead()), this, SLOT(die()));
}

Player &Player::operator=(const Player &o) {

    if(this != &o) {
        m_money = o.money();
        m_expenses = o.expenses();
        m_health = o.health();
        m_age = o.age();

        setJob(o.job());
    }

    return *this;
}

void Player::yearsChanged(uint) {
    emit ageChanged(m_age);
}

void Player::healthValueChanged(unsigned char) {
    emit healthChanged(m_health);
}

void Player::moneyValueChanged(qreal money) {

    if(money < 0.0) m_expenses.setAmount(m_expenses.amount() * m_interestRate);

    emit moneyChanged(m_money);
}

void Player::expensesValueChanged(qreal) {
    emit expensesChanged(m_expenses);
}

void Player::increaseDay() {

    m_age.increaseDay();

    if(!(m_age.days() & 63)) m_health.setValue(qMax(0, m_health.value() -
                                                    (m_money.amount() < 0.0 ? 2 : 1)));

    m_money.setAmount(m_money.amount() + m_job->payment().amount() - m_expenses.amount());
}

void Player::die() {
    emit dead();
}

const Money &Player::money() const {
    return m_money;
}

const IJob *Player::job() const {
    return m_job;
}

void Player::setJob(const IJob *job) {
    m_job = job;
    emit jobChanged(m_job);
}

const Expenses &Player::expenses() const {
    return m_expenses;
}

const Health &Player::health() const {
    return m_health;
}

const Age &Player::age() const {
    return m_age;
}

const IEducation *Player::education() const {
    return m_education;
}

void Player::setEducation(const IEducation *education) {

    m_education = education;
    emit educationChanged(m_education);

    if(m_education->isInProgress() && !m_education->succeeded()) {
        m_expenses.setAmount(m_expenses.amount() + m_education->extraExpense());
    } else if(m_education->isInProgress()) {
        m_expenses.setAmount(m_expenses.amount() - m_education->extraExpense());
    }
}
