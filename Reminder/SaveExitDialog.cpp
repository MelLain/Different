#include "SaveExitDialog.h"
#include "ui_SaveExitDialog.h"

#include "MainWindow.h"

SaveExitDialog::SaveExitDialog(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::SaveExitDialog)
{
    ui_->setupUi(this);
    connect(ui_->CancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui_->SaveExitButton, SIGNAL(clicked()), this, SLOT(saveExit()));
    connect(ui_->OnlyExitButton, SIGNAL(clicked()), this, SLOT(onlyExit()));
}

SaveExitDialog::~SaveExitDialog()
{
    delete ui_;
}

void SaveExitDialog::saveExit()
{
    dynamic_cast<MainWindow*>(parentWidget())->saveData();
    onlyExit();
}

void SaveExitDialog::onlyExit()
{
    parentWidget()->close();
}
