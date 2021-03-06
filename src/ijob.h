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

#ifndef IJOB_H
#define IJOB_H

#include <QObject>

#include "money.h"

namespace Model {

class IJob : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString name READ name)
	Q_PROPERTY(Money payment READ payment)
	Q_PROPERTY(uint minLevel READ minLevel)

public slots:
	virtual QString name() const = 0;
	virtual const Money &payment() const = 0;
	virtual void addQualitySample(int quality) = 0;
	virtual uint minLevel() const = 0;

public:
	virtual int averageQuality() const = 0;
	virtual void clearQuality() = 0;

protected:
	explicit inline IJob(QObject *parent = 0) : QObject(parent) {}
};

}

#endif // IJOB_H
