#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

#include <QDialog>

namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget* parent = 0);
    ~DialogAbout();

private:
    Ui::DialogAbout* ui_;
};

#endif // DIALOG_ABOUT_H
