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

#include "educationregistry.h"

#include "player.h"
#include "nulleducation.h"
#include "genericeducation.h"

using namespace Model;

EducationRegistry::EducationRegistry(const Player &player, QObject *parent) :
    QObject(parent), m_educations(), m_nextEducation(0) {

    m_educations.append(new GenericEducation(player.money(), player.age(), 2000.0,
                                             1.0/((qrand() % 99) + 1), 730ul,
                                             "Technical School", 1u));
    m_educations.append(new GenericEducation(player.money(), player.age(), 100000.0,
                                             10.0 + (qrand() % 10), 1460ul,
                                             "Technical University", 2u));
}

EducationRegistry::~EducationRegistry() {
    foreach (const IEducation *e, m_educations) delete e;
}

EducationRegistry &EducationRegistry::instance(const Player &player) {
    static EducationRegistry inst(player);
    return inst;
}

void EducationRegistry::increaseEducation() {
    if(m_nextEducation + 1 < m_educations.size()) ++m_nextEducation;
}

IEducation *EducationRegistry::createNullEducation() const {
    return &NullEducation::instance();
}

IEducation *EducationRegistry::nextEducation() const {
    return m_educations.at(m_nextEducation);
}
