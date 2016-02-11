#include "dialog_file_open_error.h"
#include "ui_dialog_file_open_error.h"

DialogFileOpenError::DialogFileOpenError(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::DialogFileOpenError)
{
    ui_->setupUi(this);

    connect(ui_->OkButton, SIGNAL(clicked()), this, SLOT(close()));
}

DialogFileOpenError::~DialogFileOpenError()
{
    delete ui_;
}
