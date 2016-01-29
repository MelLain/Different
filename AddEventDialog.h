#ifndef ADD_EVENT_DIALOG_H
#define ADD_EVENT_DIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class AddEventDialog;
}

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEventDialog(QTableWidget* table, QWidget* parent = nullptr);
    ~AddEventDialog();

private slots:
    void addEvent();

private:
    Ui::AddEventDialog* ui_;

    QTableWidget* table_;

    QString limitConvert(int i);
};

#endif // ADD_EVENT_DIALOG_H
