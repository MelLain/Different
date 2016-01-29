#ifndef CHANGE_PASSWORD_DIALOG_H
#define CHANGE_PASSWORD_DIALOG_H

#include <QDialog>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QString* password, QWidget* parent = nullptr);
    ~ChangePasswordDialog();

private slots:
    void activateAcceptButton();
    void changePassword();
    void showNewPassword();
    void showAcceptPassword();

private:
    Ui::ChangePasswordDialog* ui_;
    QString* password_;
};

#endif // CHANGE_PASSWORD_DIALOG_H
