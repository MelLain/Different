#include "AddEventDialog.h"
#include "ui_AddEventDialog.h"

AddEventDialog::AddEventDialog(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::AddEventDialog)
{
    ui_->setupUi(this);
    connect(ui_->CancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui_->AcceptButton, SIGNAL(clicked()), parentWidget(), SLOT(addEvent()));
}

AddEventDialog::~AddEventDialog()
{
    delete ui_;
}
