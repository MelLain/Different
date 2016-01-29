#ifndef ENTER_PASSWORD_DIALOG_H
#define ENTER_PASSWORD_DIALOG_H

#include <QDialog>

namespace Ui {
class EnterPasswordDialog;
}

class EnterPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnterPasswordDialog(QWidget* parent = nullptr);
    ~EnterPasswordDialog();

private:
    Ui::EnterPasswordDialog* ui_;
};

#endif // ENTER_PASSWORD_DIALOG_H
