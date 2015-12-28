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

#ifndef IEDUCATION_H
#define IEDUCATION_H

#include <QObject>

namespace Model {

class IEducation : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString name READ name)
	Q_PROPERTY(bool inProgress READ isInProgress WRITE setInProgress NOTIFY inProgressChanged)
	Q_PROPERTY(unsigned long days READ days)
	Q_PROPERTY(unsigned long currentDay READ currentDay NOTIFY currentDayChanged)
	Q_PROPERTY(unsigned long targetDay READ targetDay)
	Q_PROPERTY(bool succeeded READ succeeded NOTIFY succeededChanged)
	Q_PROPERTY(qreal cost READ cost)
	Q_PROPERTY(qreal extraExpense READ extraExpense)

public slots:
	virtual QString name() const = 0;
	virtual bool isInProgress() const = 0;
	virtual void setInProgress(bool progress) = 0;
	virtual unsigned long days() const = 0;
	virtual unsigned long currentDay() const = 0;
	virtual unsigned long targetDay() const = 0;
	virtual bool succeeded() const = 0;
	virtual qreal cost() const = 0;
	virtual qreal extraExpense() const = 0;

signals:
	void available(const Model::IEducation *);
	void inProgressChanged(bool);
	void currentDayChanged(unsigned long);
	void succeededChanged(bool);

protected:
	explicit inline IEducation(QObject *parent = 0) : QObject(parent) {}
};

}

#endif // IEDUCATION_H
