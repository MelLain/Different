#include "dialog_about.h"
#include "ui_dialog_about.h"

DialogAbout::DialogAbout(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::DialogAbout)
{
    ui_->setupUi(this);
}

DialogAbout::~DialogAbout()
{
    delete ui_;
}
