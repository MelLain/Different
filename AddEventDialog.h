#ifndef ADD_EVENT_DIALOG_H
#define ADD_EVENT_DIALOG_H

#include <QDialog>

namespace Ui {
class AddEventDialog;
}

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEventDialog(QWidget* parent = nullptr);
    ~AddEventDialog();

private slots:

private:
    Ui::AddEventDialog* ui_;
};

#endif // ADD_EVENT_DIALOG_H
