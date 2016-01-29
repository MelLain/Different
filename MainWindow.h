#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void addEvent();
    void acceptEvent();
    void loadData();
    void saveData();
    void changePassword();

private:
    Ui::MainWindow* ui_;

    QString password_;
};

#endif // MAIN_WINDOW_H
