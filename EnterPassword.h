#ifndef ENTERPASSWORD_H
#define ENTERPASSWORD_H

#include <QDialog>

namespace Ui {
class EnterPassword;
}

class EnterPassword : public QDialog
{
    Q_OBJECT

public:
    explicit EnterPassword(QWidget *parent = 0);
    ~EnterPassword();

private:
    Ui::EnterPassword* ui_;
};

#endif // ENTERPASSWORD_H
