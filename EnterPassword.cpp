#include "EnterPassword.h"
#include "ui_EnterPassword.h"

EnterPassword::EnterPassword(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::EnterPassword)
{
    ui_->setupUi(this);
}

EnterPassword::~EnterPassword()
{
    delete ui_;
}
