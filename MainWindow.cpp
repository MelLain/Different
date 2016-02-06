#include <algorithm>

#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QComboBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddEventDialog.h"
#include "ui_AddEventDialog.h"
#include "ChangePasswordDialog.h"
#include "ui_ChangePasswordDialog.h"
#include "EnterPasswordDialog.h"
#include "ui_EnterPasswordDialog.h"
#include "AddFriendDialog.h"
#include "ui_AddFriendDialog.h"
#include "SaveExitDialog.h"
#include "ui_SaveExitDialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    data_file_name_("C:/Users/MelLain/reminder.dat"),
    password_(QString())
{
    ui_->setupUi(this);

    connect(ui_->action_1,       SIGNAL(triggered()), this, SLOT(changePassword()));
    connect(ui_->action_2,       SIGNAL(triggered()), this, SLOT(saveData()));
    connect(ui_->action_3,       SIGNAL(triggered()), this, SLOT(requestExit()));
    connect(ui_->AddEventButton, SIGNAL(clicked()),   this, SLOT(addEvent()));
    connect(ui_->AddFriendButton, SIGNAL(clicked()),   this, SLOT(addFriend()));
    connect(ui_->DelEventsButton, SIGNAL(clicked()),   this, SLOT(delEvents()));
    connect(ui_->DelFriendsButton, SIGNAL(clicked()),   this, SLOT(delFriends()));

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

void MainWindow::addFriend()
{
    auto add_friend_dialog = new AddFriendDialog(ui_->FriendsTable, this);
    add_friend_dialog->exec();
}

void MainWindow::delEvents()
{
    QModelIndexList selection = ui_->EventsTable->selectionModel()->selectedRows();
    int saved_size = selection.count();

    QVector<int> indices;
    for(int i = 0; i < saved_size; ++i)
        indices.append(selection.at(i).row());

    std::sort(indices.begin(), indices.end());
    for(int i = 0; i < saved_size; ++i)
        indices[i] -= i;

    for(int i = 0; i < saved_size; ++i)
        ui_->EventsTable->removeRow(indices[i]);
}

void MainWindow::delFriends()
{
    QModelIndexList selection = ui_->FriendsTable->selectionModel()->selectedRows();
    int saved_size = selection.count();

    QVector<int> indices;
    for(int i = 0; i < saved_size; ++i)
        indices.append(selection.at(i).row());

    std::sort(indices.begin(), indices.end());
    for(int i = 0; i < saved_size; ++i)
        indices[i] -= i;

    for(int i = 0; i < saved_size; ++i)
        ui_->FriendsTable->removeRow(indices[i]);
}

void MainWindow::requestExit()
{
    auto request_exit = new SaveExitDialog(this);
    request_exit->exec();
}

void MainWindow::saveData()
{
    QFile file(data_file_name_);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << password_ << endl;

        stream << ui_->EventsTable->rowCount() << endl;
        for (int i = 0; i < ui_->EventsTable->rowCount(); ++i)
        {
            QTableWidgetItem* name = ui_->EventsTable->item(i, 0);
            QTableWidgetItem* descr = ui_->EventsTable->item(i, 1);
            QDateEdit* date = dynamic_cast<QDateEdit*>(ui_->EventsTable->cellWidget(i, 2));
            QComboBox* level = dynamic_cast<QComboBox*>(ui_->EventsTable->cellWidget(i, 3));
            stream << name->text() << '\n' << descr->text() << '\n'
                   << date->text() << '\n' << level->currentIndex() << endl;
        }

        stream << ui_->FriendsTable->rowCount() << endl;
        for (int i = 0; i < ui_->FriendsTable->rowCount(); ++i)
        {
            QTableWidgetItem* name = ui_->FriendsTable->item(i, 0);
            QComboBox* level = dynamic_cast<QComboBox*>(ui_->FriendsTable->cellWidget(i, 1));
            QTableWidgetItem* descr = ui_->FriendsTable->item(i, 2);
            QDateEdit* date = dynamic_cast<QDateEdit*>(ui_->FriendsTable->cellWidget(i, 3));
            stream << name->text() << '\n' << level->currentIndex() << '\n'
                   << descr->text() << '\n' << date->text() << endl;
        }

        stream << ui_->NotesTextField->toPlainText();
    }
    file.close();
}

void MainWindow::loadData()
{
    try
    {
        QFile file(data_file_name_);
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);

            password_ = stream.readLine();

            int rows_count = std::stoi(stream.readLine().toStdString());
            for (int i = 0; i < rows_count; ++i)
            {
                ui_->EventsTable->insertRow(ui_->EventsTable->rowCount());

                ui_->EventsTable->setItem(ui_->EventsTable->rowCount() - 1, 0,
                                          new QTableWidgetItem(stream.readLine()));

                ui_->EventsTable->setItem(ui_->EventsTable->rowCount() - 1, 1,
                                          new QTableWidgetItem(stream.readLine()));

                auto date_str = stream.readLine().split(QString("/"));
                ui_->EventsTable->setCellWidget(ui_->EventsTable->rowCount() - 1, 2,
                                                new QDateEdit(QDate(std::stoi(date_str[2].toStdString()),
                                                                    std::stoi(date_str[1].toStdString()),
                                                                    std::stoi(date_str[0].toStdString()))));

                auto combo_box_ptr = new QComboBox();
                combo_box_ptr->addItem("Низкий");
                combo_box_ptr->addItem("Средний");
                combo_box_ptr->addItem("Высокий");
                combo_box_ptr->setCurrentIndex(std::stoi(stream.readLine().toStdString()));
                ui_->EventsTable->setCellWidget(ui_->EventsTable->rowCount() - 1, 3, combo_box_ptr);
            }

            rows_count = std::stoi(stream.readLine().toStdString());
            for (int i = 0; i < rows_count; ++i)
            {
                ui_->FriendsTable->insertRow(ui_->FriendsTable->rowCount());

                ui_->FriendsTable->setItem(ui_->FriendsTable->rowCount() - 1, 0,
                                          new QTableWidgetItem(stream.readLine()));

                auto combo_box_ptr = new QComboBox();
                combo_box_ptr->addItem("Приятель");
                combo_box_ptr->addItem("Друг");
                combo_box_ptr->addItem("Близкий друг");
                combo_box_ptr->setCurrentIndex(std::stoi(stream.readLine().toStdString()));
                ui_->FriendsTable->setCellWidget(ui_->FriendsTable->rowCount() - 1, 1, combo_box_ptr);
                ui_->FriendsTable->setItem(ui_->FriendsTable->rowCount() - 1, 2,
                                          new QTableWidgetItem(stream.readLine()));

                auto date_str = stream.readLine().split(QString("/"));
                ui_->FriendsTable->setCellWidget(ui_->FriendsTable->rowCount() - 1, 3,
                                                 new QDateEdit(QDate(std::stoi(date_str[2].toStdString()),
                                                                     std::stoi(date_str[1].toStdString()),
                                                                     std::stoi(date_str[0].toStdString()))));
            }

            QString notes_str;
            while (!stream.atEnd())
                notes_str += stream.readLine() + QString("\n");

            ui_->NotesTextField->setText(notes_str);
        }
        file.close();
    }
    catch(...) { }
}
