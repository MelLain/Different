#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddEventDialog.h"
#include "ui_AddEventDialog.h"
#include "ChangePasswordDialog.h"
#include "ui_ChangePasswordDialog.h"
#include "EnterPasswordDialog.h"
#include "ui_EnterPasswordDialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    password_(QString(""))
{
    ui_->setupUi(this);

    connect(ui_->action_1,       SIGNAL(triggered()), this, SLOT(changePassword()));
    connect(ui_->action_2,       SIGNAL(triggered()), this, SLOT(saveData()));
    connect(ui_->action_3,       SIGNAL(triggered()), this, SLOT(close()));
    connect(ui_->AddEventButton, SIGNAL(clicked()),   this, SLOT(addEvent()));

    loadData();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::changePassword()
{
    auto change_password_dialog = new ChangePasswordDialog(&password_, this);
    change_password_dialog->exec();
}

void MainWindow::addEvent()
{
    auto add_event_dialog = new AddEventDialog(ui_->EventsTable, this);
    add_event_dialog->exec();
}

void MainWindow::acceptEvent()
{
    //qDebug() << new_event_name_ << new_event_content_ << new_event_level_ << new_event_date_;
}

void MainWindow::saveData()
{
    qDebug() << password_;
}

void MainWindow::loadData()
{
    qDebug() << "load data";
}
