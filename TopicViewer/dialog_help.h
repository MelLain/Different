#ifndef DIALOG_HELP_H
#define DIALOG_HELP_H

#include <QDialog>

namespace Ui {
class DialogHelp;
}

class DialogHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHelp(QWidget* parent = 0);
    ~DialogHelp();

private:
    Ui::DialogHelp* ui_;
};

#endif // DIALOG_HELP_H
