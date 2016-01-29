#include "AddEventDialog.h"
#include "ui_AddEventDialog.h"

#include <QDebug>

AddEventDialog::AddEventDialog(QTableWidget* table, QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::AddEventDialog),
    table_(table)
{
    ui_->setupUi(this);
    connect(ui_->CancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui_->AcceptButton, SIGNAL(clicked()), this, SLOT(addEvent()));
}

AddEventDialog::~AddEventDialog()
{
    delete ui_;
}

QString AddEventDialog::limitConvert(int i) {
    if (i == -2) return QString("Низкий");
    if (i == -3) return QString("Средний");
    if (i == -4) return QString("Высокий");
    return QString("Ошибка");
}

void AddEventDialog::addEvent()
{
    table_->insertRow(table_->rowCount());

    table_->setItem(table_->rowCount() - 1, 0, new QTableWidgetItem(QString(ui_->NameTextField->toPlainText())));
    table_->setItem(table_->rowCount() - 1, 1, new QTableWidgetItem(QString(ui_->DescrTextField->toPlainText())));
    table_->setCellWidget(table_->rowCount() - 1, 2, new QDateEdit(ui_->dateEdit->date()));
    table_->setItem(table_->rowCount() - 1, 3, new QTableWidgetItem(
                        limitConvert(ui_->EventLevelRadioButtonsGroup->checkedId())));
    close();
}
