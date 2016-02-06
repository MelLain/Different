#include <QComboBox>

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

void AddEventDialog::addEvent()
{
    table_->insertRow(table_->rowCount());

    table_->setItem(table_->rowCount() - 1, 0, new QTableWidgetItem(QString(ui_->NameTextField->toPlainText())));
    table_->setItem(table_->rowCount() - 1, 1, new QTableWidgetItem(QString(ui_->DescrTextField->toPlainText())));
    table_->setCellWidget(table_->rowCount() - 1, 2, new QDateEdit(ui_->EventDateEdit->date()));

    auto combo_box_ptr = new QComboBox();
    combo_box_ptr->addItem("Низкий");
    combo_box_ptr->addItem("Средний");
    combo_box_ptr->addItem("Высокий");
    combo_box_ptr->setCurrentIndex(-2 - ui_->EventLevelRadioButtonsGroup->checkedId());
    table_->setCellWidget(table_->rowCount() - 1, 3, combo_box_ptr);

    close();
}
