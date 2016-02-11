#ifndef SAVE_EXIT_DIALOG_H
#define SAVE_EXIT_DIALOG_H

#include <QDialog>

#include "common.h"

namespace Ui {
class SaveExitDialog;
}

class SaveExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveExitDialog(QWidget* parent = 0);
    ~SaveExitDialog();

private slots:
    void saveExit();
    void onlyExit();

private:
    Ui::SaveExitDialog* ui_;
};

#endif // SAVE_EXIT_DIALOG_H
