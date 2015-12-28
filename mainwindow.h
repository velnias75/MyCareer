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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "ieducation.h"
#include "player.h"

typedef Model::Player ModelPlayer;

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT
    Q_PROPERTY(ModelPlayer player READ player NOTIFY playerChanged)

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    const ModelPlayer &player() const;

private slots:
    void dead();

    void expensesChanged(const Model::Expenses &expenses);
    void healthChanged(const Model::Health &health);
    void moneyChanged(const Model::Money &money);
    void ageChanged(const Model::Age &age);
    void jobChanged(const Model::IJob *job);

    void findJob();
    void educationAvailable(const Model::IEducation *education);
    void doNextEducation();
    void educationSucceeded(bool);
    void educationCurrentDayChanged(ulong currentDay);

signals:
    void playerChanged(const Model::Player &);

private:
    QString jobDescription(const Model::IJob *job) const;
    void setupNextEducation();
    QString eduButtonText(const Model::IEducation *edu) const;

private:
    ModelPlayer m_player;
    QTimer *m_daysTimer;
    Model::IEducation * m_nextEducation;
};

#endif // MAINWINDOW_H
