#include "EnterPasswordDialog.h"
#include "ui_EnterPasswordDialog.h"

EnterPasswordDialog::EnterPasswordDialog(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::EnterPasswordDialog)
{
    ui_->setupUi(this);
}

EnterPasswordDialog::~EnterPasswordDialog()
{
    delete ui_;
}
