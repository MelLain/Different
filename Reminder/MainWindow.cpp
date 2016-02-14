#include <algorithm>

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

Money::Money() :
    cur_rub_nal_value_(0),
    cur_eur_nal_value_(0),
    cur_usd_nal_value_(0),
    cur_rub_elec_value_(0),
    cur_eur_elec_value_(0),
    cur_usd_elec_value_(0),
    old_rub_nal_value_(0),
    old_eur_nal_value_(0),
    old_usd_nal_value_(0),
    old_rub_elec_value_(0),
    old_eur_elec_value_(0),
    old_usd_elec_value_(0),
    rub_diff_value_(0),
    eur_diff_value_(0),
    usd_diff_value_(0) { }

    void Money::setCurRubNalValue(int value)
    {
        cur_rub_nal_value_ = value;
        rub_diff_value_ = (value + cur_rub_elec_value_) - (old_rub_nal_value_ + old_rub_elec_value_);
    }

    void Money::setCurEurNalValue(int value)
    {
        cur_eur_nal_value_ = value;
        eur_diff_value_ = (value + cur_eur_elec_value_) - (old_eur_nal_value_ + old_eur_elec_value_);
    }

    void Money::setCurUsdNalValue(int value)
    {
        cur_usd_nal_value_ = value;
        usd_diff_value_ = (value + cur_usd_elec_value_) - (old_usd_nal_value_ + old_usd_elec_value_);
    }

    void Money::setCurRubElecValue(int value)
    {
        cur_rub_elec_value_ = value;
        rub_diff_value_ = (cur_rub_nal_value_ + value) - (old_rub_nal_value_ + old_rub_elec_value_);
    }

    void Money::setCurEurElecValue(int value)
    {
        cur_eur_elec_value_ = value;
        eur_diff_value_ = (cur_eur_nal_value_ + value) - (old_eur_nal_value_ + old_eur_elec_value_);
    }

    void Money::setCurUsdElecValue(int value)
    {
        cur_usd_elec_value_ = value;
        usd_diff_value_ = (cur_usd_nal_value_ + value) - (old_usd_nal_value_ + old_usd_elec_value_);
    }

    void Money::setOldRubNalValue(int value)
    {
        old_rub_nal_value_ = value;
        rub_diff_value_ = (cur_rub_nal_value_ + cur_rub_elec_value_) - (value + old_rub_elec_value_);
    }

    void Money::setOldEurNalValue(int value)
    {
        old_eur_nal_value_ = value;
        eur_diff_value_ = (cur_eur_nal_value_ + cur_eur_elec_value_) - (value + old_eur_elec_value_);
    }

    void Money::setOldUsdNalValue(int value)
    {
        old_usd_nal_value_ = value;
        usd_diff_value_ = (cur_usd_nal_value_ + cur_usd_elec_value_) - (value + old_usd_elec_value_);
    }

    void Money::setOldRubElecValue(int value)
    {
        old_rub_elec_value_ = value;
        rub_diff_value_ = (cur_rub_nal_value_ + cur_rub_elec_value_) - (old_rub_nal_value_ + value);
    }

    void Money::setOldEurElecValue(int value)
    {
        old_eur_elec_value_ = value;
        eur_diff_value_ = (cur_eur_nal_value_ + cur_eur_elec_value_) - (old_eur_nal_value_ + value);
    }

    void Money::setOldUsdElecValue(int value)
    {
        old_usd_elec_value_ = value;
        usd_diff_value_ = (cur_usd_nal_value_ + cur_usd_elec_value_) - (old_usd_nal_value_ + value);
    }

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    data_file_name_(DATA_FILE_PATH),
    password_(QString()),
    money_(Money())
{
    ui_->setupUi(this);

    connect(ui_->ActionChangePass, SIGNAL(triggered()), this, SLOT(changePassword()));
    connect(ui_->ActionSave,       SIGNAL(triggered()), this, SLOT(saveData()));
    connect(ui_->ActionExit,       SIGNAL(triggered()), this, SLOT(requestExit()));
    connect(ui_->ActionUpdate,     SIGNAL(triggered()), this, SLOT(updateState()));
    connect(ui_->AddEventButton,   SIGNAL(clicked()),   this, SLOT(addEvent()));
    connect(ui_->AddFriendButton,  SIGNAL(clicked()),   this, SLOT(addFriend()));
    connect(ui_->DelEventsButton,  SIGNAL(clicked()),   this, SLOT(delEvents()));
    connect(ui_->DelFriendsButton, SIGNAL(clicked()),   this, SLOT(delFriends()));

    // financial events
    connect(ui_->CurRubNalEdit,    SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->CurEurNalEdit,    SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->CurUsdNalEdit,    SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->CurRubElecEdit,   SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->CurEurElecEdit,   SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->CurUsdElecEdit,   SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->OldRubNalEdit,    SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->OldEurNalEdit,    SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->OldUsdNalEdit,    SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->OldRubElecEdit,   SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->OldEurElecEdit,   SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));
    connect(ui_->OldUsdElecEdit,   SIGNAL(textChanged(QString)), this, SLOT(changeMoneyDiff()));

    loadData();
    updateState();
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

void MainWindow::updateState()
{
    for (int i = 0; i < ui_->EventsTable->rowCount(); ++i)
    {
        QComboBox* level = dynamic_cast<QComboBox*>(ui_->EventsTable->cellWidget(i, 3));
        if (level->currentText() == EVENT_LOW_RUS)
            level->setStyleSheet("QComboBox { background-color:" + LOW_COLOR + "; }");
        if (level->currentText() == EVENT_MIDDLE_RUS)
            level->setStyleSheet("QComboBox { background-color:" + MIDDLE_COLOR + "; }");
        if (level->currentText() == EVENT_HIGH_RUS)
            level->setStyleSheet("QComboBox { background-color:" + HIGH_COLOR + "; }");
    }

    for (int i = 0; i < ui_->FriendsTable->rowCount(); ++i)
    {
        QComboBox* level = dynamic_cast<QComboBox*>(ui_->FriendsTable->cellWidget(i, 1));
        if (level->currentText() == FRIEND_LOW_RUS)
            level->setStyleSheet("QComboBox { background-color:" + HIGH_COLOR + "; }");
        if (level->currentText() == FRIEND_MIDDLE_RUS)
            level->setStyleSheet("QComboBox { background-color:" + MIDDLE_COLOR + "; }");
        if (level->currentText() == FRIEND_HIGH_RUS)
            level->setStyleSheet("QComboBox { background-color:" + LOW_COLOR + "; }");
    }
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

void MainWindow::changeMoneyDiff()
{
    QVector<bool> is_correct(MONEY_EDIT_FIELDS_COUNT /*= 12*/, true);
    QVector<float> new_values(MONEY_EDIT_FIELDS_COUNT + MONEY_DIFF_FIELDS_COUNT, 0.0f);

    new_values[0] = ui_->CurRubNalEdit->text().toFloat(&is_correct[0]);
    new_values[1] = ui_->CurEurNalEdit->text().toFloat(&is_correct[1]);
    new_values[2] = ui_->CurUsdNalEdit->text().toFloat(&is_correct[2]);
    new_values[3] = ui_->CurRubElecEdit->text().toFloat(&is_correct[3]);
    new_values[4] = ui_->CurEurElecEdit->text().toFloat(&is_correct[4]);
    new_values[5] = ui_->CurUsdElecEdit->text().toFloat(&is_correct[5]);

    new_values[6] = ui_->OldRubNalEdit->text().toFloat(&is_correct[6]);
    new_values[7] = ui_->OldEurNalEdit->text().toFloat(&is_correct[7]);
    new_values[8] = ui_->OldUsdNalEdit->text().toFloat(&is_correct[8]);
    new_values[9] = ui_->OldRubElecEdit->text().toFloat(&is_correct[9]);
    new_values[10] = ui_->OldEurElecEdit->text().toFloat(&is_correct[10]);
    new_values[11] = ui_->OldUsdElecEdit->text().toFloat(&is_correct[11]);

    bool passed = true;
    for (bool elem : is_correct)
        passed &= elem;

    if (passed)
    {
        money_.setCurRubNalValue(new_values[0]);
        money_.setCurEurNalValue(new_values[1]);
        money_.setCurUsdNalValue(new_values[2]);
        money_.setCurRubElecValue(new_values[3]);
        money_.setCurEurElecValue(new_values[4]);
        money_.setCurUsdElecValue(new_values[5]);
        money_.setOldRubNalValue(new_values[6]);
        money_.setOldEurNalValue(new_values[7]);
        money_.setOldUsdNalValue(new_values[8]);
        money_.setOldRubElecValue(new_values[9]);
        money_.setOldEurElecValue(new_values[10]);
        money_.setOldUsdElecValue(new_values[11]);
    }

    QString value_str;

    ui_->CurRubNalEdit->setText(value_str.setNum(money_.getCurRubNalValue()));
    ui_->CurEurNalEdit->setText(value_str.setNum(money_.getCurEurNalValue()));
    ui_->CurUsdNalEdit->setText(value_str.setNum(money_.getCurUsdNalValue()));
    ui_->CurRubElecEdit->setText(value_str.setNum(money_.getCurRubElecValue()));
    ui_->CurEurElecEdit->setText(value_str.setNum(money_.getCurEurElecValue()));
    ui_->CurUsdElecEdit->setText(value_str.setNum(money_.getCurUsdElecValue()));

    ui_->OldRubNalEdit->setText(value_str.setNum(money_.getOldRubNalValue()));
    ui_->OldEurNalEdit->setText(value_str.setNum(money_.getOldEurNalValue()));
    ui_->OldUsdNalEdit->setText(value_str.setNum(money_.getOldUsdNalValue()));
    ui_->OldRubElecEdit->setText(value_str.setNum(money_.getOldRubElecValue()));
    ui_->OldEurElecEdit->setText(value_str.setNum(money_.getOldEurElecValue()));
    ui_->OldUsdElecEdit->setText(value_str.setNum(money_.getOldUsdElecValue()));

    ui_->RubDiffEdit->setText(value_str.setNum(money_.getRubDiffValue()));
    ui_->EurDiffEdit->setText(value_str.setNum(money_.getEurDiffValue()));
    ui_->UsdDiffEdit->setText(value_str.setNum(money_.getUsdDiffValue()));

    setQLineEditColor(ui_->RubDiffEdit, money_.getRubDiffValue());
    setQLineEditColor(ui_->EurDiffEdit, money_.getEurDiffValue());
    setQLineEditColor(ui_->UsdDiffEdit, money_.getUsdDiffValue());
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

        stream << money_.getCurRubNalValue() << ' '
               << money_.getCurEurNalValue() << ' '
               << money_.getCurUsdNalValue() << ' '
               << money_.getCurRubElecValue() << ' '
               << money_.getCurEurElecValue() << ' '
               << money_.getCurUsdElecValue() << ' '
               << money_.getOldRubNalValue() << ' '
               << money_.getOldEurNalValue() << ' '
               << money_.getOldUsdNalValue() << ' '
               << money_.getOldRubElecValue() << ' '
               << money_.getOldEurElecValue() << ' '
               << money_.getOldUsdElecValue() << endl;

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

            int rows_count = stream.readLine().toInt();
            for (int i = 0; i < rows_count; ++i)
            {
                ui_->EventsTable->insertRow(ui_->EventsTable->rowCount());

                ui_->EventsTable->setItem(ui_->EventsTable->rowCount() - 1, 0,
                                          new QTableWidgetItem(stream.readLine()));

                ui_->EventsTable->setItem(ui_->EventsTable->rowCount() - 1, 1,
                                          new QTableWidgetItem(stream.readLine()));

                auto date_str = stream.readLine().split(QString("/"));
                ui_->EventsTable->setCellWidget(ui_->EventsTable->rowCount() - 1, 2,
                                                new QDateEdit(QDate(date_str[2].toInt(),
                                                                    date_str[1].toInt(),
                                                                    date_str[0].toInt())));

                auto combo_box_ptr = new QComboBox();
                combo_box_ptr->addItem(EVENT_LOW_RUS);
                combo_box_ptr->addItem(EVENT_MIDDLE_RUS);
                combo_box_ptr->addItem(EVENT_HIGH_RUS);
                combo_box_ptr->setCurrentIndex(stream.readLine().toInt());
                ui_->EventsTable->setCellWidget(ui_->EventsTable->rowCount() - 1, 3, combo_box_ptr);
            }

            rows_count = stream.readLine().toInt();
            for (int i = 0; i < rows_count; ++i)
            {
                ui_->FriendsTable->insertRow(ui_->FriendsTable->rowCount());

                ui_->FriendsTable->setItem(ui_->FriendsTable->rowCount() - 1, 0,
                                          new QTableWidgetItem(stream.readLine()));

                auto combo_box_ptr = new QComboBox();
                combo_box_ptr->addItem(FRIEND_LOW_RUS);
                combo_box_ptr->addItem(FRIEND_MIDDLE_RUS);
                combo_box_ptr->addItem(FRIEND_HIGH_RUS);
                combo_box_ptr->setCurrentIndex(stream.readLine().toInt());
                ui_->FriendsTable->setCellWidget(ui_->FriendsTable->rowCount() - 1, 1, combo_box_ptr);
                ui_->FriendsTable->setItem(ui_->FriendsTable->rowCount() - 1, 2,
                                          new QTableWidgetItem(stream.readLine()));

                auto date_str = stream.readLine().split(QString("/"));
                ui_->FriendsTable->setCellWidget(ui_->FriendsTable->rowCount() - 1, 3,
                                                 new QDateEdit(QDate(date_str[2].toInt(),
                                                                     date_str[1].toInt(),
                                                                     date_str[0].toInt())));
            }

            auto money_data_list = stream.readLine().split(' ');

            ui_->CurRubNalEdit->setText(money_data_list[0]);
            ui_->CurEurNalEdit->setText(money_data_list[1]);
            ui_->CurUsdNalEdit->setText(money_data_list[2]);
            ui_->CurRubElecEdit->setText(money_data_list[3]);
            ui_->CurEurElecEdit->setText(money_data_list[4]);
            ui_->CurUsdElecEdit->setText(money_data_list[5]);

            ui_->OldRubNalEdit->setText(money_data_list[6]);
            ui_->OldEurNalEdit->setText(money_data_list[7]);
            ui_->OldUsdNalEdit->setText(money_data_list[8]);
            ui_->OldRubElecEdit->setText(money_data_list[9]);
            ui_->OldEurElecEdit->setText(money_data_list[10]);
            ui_->OldUsdElecEdit->setText(money_data_list[11]);

            changeMoneyDiff();

            QString notes_str;
            while (!stream.atEnd())
                notes_str += stream.readLine() + QString("\n");

            ui_->NotesTextField->setText(notes_str);
        }
        file.close();
    }
    catch(...) { }
}

void MainWindow::setQLineEditColor(QLineEdit* line_edit_ptr, int value)
{
    QPalette p = line_edit_ptr->palette();
    p.setColor(QPalette::Base, Qt::white);
    if (value >= 0)
        p.setColor(QPalette::Text, Qt::green);
    else
        p.setColor(QPalette::Text, Qt::red);
    line_edit_ptr->setPalette(p);
}
