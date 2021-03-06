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

#include <QTimer>
#include <QMessageBox>
#include <QDesktopWidget>

#include "ijob.h"
#include "mainwindow.h"
#include "jobregistry.h"
#include "educationregistry.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_player(),
    m_daysTimer(new QTimer(this)),
    m_nextEducation(Model::EducationRegistry::instance(m_player).createNullEducation()),
    m_jobSearching(false) {

    setupUi(this);

    eduBar->setFormat(m_nextEducation->name());

    setupNextEducation();

    QObject::connect(action_Find_Job, SIGNAL(activated()), this, SLOT(findJob()));
    QObject::connect(findJobButton, SIGNAL(clicked()), this, SLOT(findJob()));
    QObject::connect(eduButton, SIGNAL(clicked()), this, SLOT(doNextEducation()));

    QObject::connect(m_daysTimer, SIGNAL(timeout()), &m_player, SLOT(increaseDay()));

    QObject::connect(&m_player, SIGNAL(dead()), this, SLOT(dead()));
    QObject::connect(&m_player, SIGNAL(healthChanged(Model::Health)),
                     this, SLOT(healthChanged(Model::Health)));
    QObject::connect(&m_player, SIGNAL(moneyChanged(Model::Money)),
                     this, SLOT(moneyChanged(Model::Money)));
    QObject::connect(&m_player, SIGNAL(expensesChanged(Model::Expenses)),
                     this, SLOT(expensesChanged(Model::Expenses)));
    QObject::connect(&m_player, SIGNAL(ageChanged(Model::Age)),
                     this, SLOT(ageChanged(Model::Age)));
    QObject::connect(&m_player, SIGNAL(jobChanged(const Model::IJob *)),
                     this, SLOT(jobChanged(const Model::IJob *)));
    QObject::connect(&m_player, SIGNAL(offerHealthCheck(qreal)),
                     this, SLOT(healthCheck(qreal)));

    expensesChanged(m_player.expenses());
    healthChanged(m_player.health());
    moneyChanged(m_player.money());
    ageChanged(m_player.age());
    jobChanged(m_player.job());

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
            qApp->desktop()->availableGeometry()));

    m_daysTimer->start(500);
}

MainWindow::~MainWindow() {
    delete m_daysTimer;
}

const ModelPlayer &MainWindow::player() const {
    return m_player;
}

void MainWindow::ageChanged(const Model::Age &age) {
    ageBar->setFormat(QString("%1 years").arg(QString::number(age.years())));

    const int v = age.days() - age.years() * 365ul;

    ageBar->setValue(v);

    if(m_jobSearching) findJobBar->setValue(findJobBar->value() + 1);

    if(age.years() > 18u && !v) statusBar()->showMessage("Happy Birthday!", 2000);
}

void MainWindow::jobChanged(const Model::IJob *job) {
    jobLabel->setText(jobDescription(job));
}

void MainWindow::moneyChanged(const Model::Money &money) {

    const qreal amount = m_player.money().amount();

    moneyLabel->setText(QString("%1%2 %3%4").arg(amount < 0.0 ? "<b><font color=red>" : "<b>").
                        arg(QString::number(money.amount(), 'f', 2)).
                        arg(QString::fromUtf8("\u20AC")).
                        arg(m_player.money().amount() < 0.0 ?
                                "</font></b>" : "</b>"));
}

void MainWindow::expensesChanged(const Model::Expenses &expenses) {
    expensesLabel->setText(QString("%1 %2/day").arg(QString::number(expenses.amount(), 'f', 2)).
                           arg(QString::fromUtf8("\u20AC")));
}

void MainWindow::healthChanged(const Model::Health &health) {
    healthBar->setValue(health.value());
}

void MainWindow::dead() {
    m_daysTimer->stop();
    statusBar()->showMessage("You have died!");
}

QString MainWindow::jobDescription(const Model::IJob *job) const {
    return QString("%1 (%2 %3/day)").arg(job->name()).
            arg(QString::number(job->payment().amount(), 'f', 2)).
            arg(QString::fromUtf8("\u20AC"));
}

void MainWindow::findJob() {

    findJobButton->setDisabled(true);

    findJobBar->setValue(0);
    findJobBar->setFormat("Finding job...");
    findJobBar->setMaximum(Model::JobRegistry::instance().findJob(m_player));

    QObject::connect(&Model::JobRegistry::instance(), SIGNAL(jobFound(Model::IJob*)),
                     this, SLOT(jobFound(Model::IJob*)));

    m_jobSearching = true;
}

void MainWindow::jobFound(Model::IJob *job) {

    m_jobSearching = false;

    if(job) findJobBar->setFormat("Got a job offer!");

    QObject::disconnect(&Model::JobRegistry::instance(), SIGNAL(jobFound(Model::IJob*)),
                        this, SLOT(jobFound(Model::IJob*)));

    if(job && m_player.job() != job && (m_player.job()->payment().amount() == 0.0 ||
                                        (QMessageBox::question(this, "Job offer",
                                                              QString("Do you want to be a " \
                                                                      "<br /><b>%1</b>?").
                                                              arg(jobDescription(job)),
                                                              QMessageBox::Yes, QMessageBox::No)
                                        == QMessageBox::Yes))) m_player.setJob(job);

    findJobBar->setValue(0);
    findJobBar->setFormat(QString::null);

    findJobButton->setDisabled(false);
}

void MainWindow::educationAvailable(const Model::IEducation *education) {
    eduButton->setEnabled(!education->isInProgress());
}

void MainWindow::doNextEducation() {

    eduButton->setEnabled(false);

    eduBar->setValue(0);
    eduBar->setEnabled(true);
    eduBar->setMaximum(m_nextEducation->days());
    eduBar->setFormat(m_nextEducation->name());

    QObject::connect(m_nextEducation, SIGNAL(currentDayChanged(ulong)),
                     this, SLOT(educationCurrentDayChanged(ulong)));

    m_nextEducation->setInProgress(true);
    m_player.setEducation(m_nextEducation);

    QObject::connect(m_nextEducation, SIGNAL(succeededChanged(bool)),
                     this, SLOT(educationSucceeded(bool)));
}

void MainWindow::educationCurrentDayChanged(ulong currentDay) {
    eduBar->setValue(currentDay);
}

void MainWindow::educationSucceeded(bool) {

    QObject::disconnect(m_nextEducation, SIGNAL(currentDayChanged(ulong)),
                        this, SLOT(educationCurrentDayChanged(ulong)));
    QObject::disconnect(m_nextEducation, SIGNAL(succeededChanged(bool)),
                        this, SLOT(educationSucceeded(bool)));

    m_player.setEducation(m_nextEducation);

    Model::EducationRegistry::instance(m_player).increaseEducation();

    setupNextEducation();
}

void MainWindow::setupNextEducation() {

    eduBar->setEnabled(false);

    QObject::disconnect(m_nextEducation, SIGNAL(available(const Model::IEducation*)),
                     this, SLOT(educationAvailable(const Model::IEducation*)));

    m_nextEducation = Model::EducationRegistry::instance(m_player).nextEducation();

    eduButton->setText(eduButtonText(m_nextEducation));
    eduButton->setDisabled(true);

    QObject::connect(m_nextEducation, SIGNAL(available(const Model::IEducation*)),
                     this, SLOT(educationAvailable(const Model::IEducation*)));
}

QString MainWindow::eduButtonText(const Model::IEducation *edu) const {
    return QString("&Go to %1 (%3 %4/%2 years)").arg(edu->name()).arg(edu->days() / 365ul).
            arg(QString::number(edu->cost(), 'f', 2)).arg(QString::fromUtf8("\u20AC"));
}

void MainWindow::healthCheck(qreal cost) {
    if(QMessageBox::question(this, "Health check", QString("Do you want to get a<br />" \
                                                           "health chack for %1 %2").
                             arg(QString::number(cost, 'f', 2)).arg(QString::fromUtf8("\u20AC")),
                             QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        m_player.doHealthCheck(cost);
    }
}
