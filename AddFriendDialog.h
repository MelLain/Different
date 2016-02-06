#ifndef ADD_FRIEND_DIALOG_H
#define ADD_FRIEND_DIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendDialog(QTableWidget* table, QWidget* parent = nullptr);
    ~AddFriendDialog();

private slots:
    void addFriend();

private:
    Ui::AddFriendDialog* ui_;

    QTableWidget* table_;
};

#endif // ADD_FRIEND_DIALOG_H
