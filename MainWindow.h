#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void saveData();

private slots:
    void addEvent();
    void addFriend();
    void delEvents();
    void delFriends();
    void loadData();
    void changePassword();
    void requestExit();

private:
    Ui::MainWindow* ui_;

    QString data_file_name_;
    QString password_;
};

#endif // MAIN_WINDOW_H
