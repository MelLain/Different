#include "dialog_help.h"
#include "ui_dialog_help.h"

DialogHelp::DialogHelp(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::DialogHelp)
{
    ui_->setupUi(this);
}

DialogHelp::~DialogHelp()
{
    delete ui_;
}
