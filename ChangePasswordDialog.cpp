#include "ChangePasswordDialog.h"
#include "ui_ChangePasswordDialog.h"

#include <QDebug>

ChangePasswordDialog::ChangePasswordDialog(QString* password, QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::ChangePasswordDialog),
    password_(password)
{
    ui_->setupUi(this);

    connect(ui_->cancelButton,       SIGNAL(clicked()),            this, SLOT(close()));
    connect(ui_->acceptPasswordText, SIGNAL(textChanged(QString)), this, SLOT(activateAcceptButton()));
    connect(ui_->newPasswordText,    SIGNAL(textChanged(QString)), this, SLOT(activateAcceptButton()));
    connect(ui_->acceptButton,       SIGNAL(clicked()),            this, SLOT(changePassword()));
    connect(ui_->showNewCheckBox,    SIGNAL(clicked()),            this, SLOT(showNewPassword()));
    connect(ui_->showAcceptCheckBox, SIGNAL(clicked()),            this, SLOT(showAcceptPassword()));
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui_;
}

void ChangePasswordDialog::activateAcceptButton()
{
    if ((ui_->newPasswordText->text() == ui_->acceptPasswordText->text())  &&
            ui_->newPasswordText->size().width() && ui_->acceptPasswordText->size().width())
    {
        ui_->acceptButton->setEnabled(true);
        return;
    }

    ui_->acceptButton->setEnabled(false);
}

void ChangePasswordDialog::changePassword()
{
    *password_ = QString(ui_->newPasswordText->text());
    close();
}

void ChangePasswordDialog::showNewPassword()
{
    ui_->newPasswordText->setEchoMode(ui_->newPasswordText->echoMode() == QLineEdit::EchoMode::Password ?
                                          QLineEdit::EchoMode::Normal : QLineEdit::EchoMode::Password);
}

void ChangePasswordDialog::showAcceptPassword()
{
    ui_->acceptPasswordText->setEchoMode(ui_->acceptPasswordText->echoMode() == QLineEdit::EchoMode::Password ?
                                             QLineEdit::EchoMode::Normal : QLineEdit::EchoMode::Password);
}
