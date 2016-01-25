#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddEventDialog.h"
#include "ui_AddEventDialog.h"

#include <iostream>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::on_AddEventButton_clicked()
{
    auto add_event_dialog = new AddEventDialog(this);
    add_event_dialog->exec();
}

void MainWindow::addEvent()
{
    std::cout << "-----\n";
}
