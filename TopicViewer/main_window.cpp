#include "main_window.h"
#include "ui_main_window.h"

#include "dialog_file_open_error.h"
#include "ui_dialog_file_open_error.h"
#include "dialog_results.h"
#include "ui_dialog_results.h"

#include <algorithm>
#include <string>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QCheckBox>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    source_file_name_(QString()),
    topic_names_(nullptr),
    topic_data_(nullptr),
    current_index_(0),
    interpret_level_(nullptr),
    ethnic_level_(nullptr),
    last_index_(false),
    checked_tokens_(nullptr)
{
    ui_->setupUi(this);

    resetMainWindow();

    connect(ui_->ActionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui_->ActionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui_->NextButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(ui_->PrevButton, SIGNAL(clicked()), this, SLOT(prevPage()));
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::resetMainWindow()
{
    source_file_name_ = QString();
    topic_names_.reset(new QVector<QString>());
    topic_data_.reset(new QVector<QVector<QString> >());
    current_index_ = 0;
    interpret_level_.reset(new QVector<int>());
    ethnic_level_.reset(new QVector<int>());
    last_index_ = false;
    checked_tokens_.reset(new QMap<QString, QVector<int> >());
}

void MainWindow::openFile()
{
    resetMainWindow();
    source_file_name_ = QFileDialog::getOpenFileName(this,
         tr("Open file with topics"), "/", tr("Text Files (*.txt)"));

    try
    {
        QFile file(source_file_name_);
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");

            bool reading_started = false;
            while (!stream.atEnd())
            {
                QString current_line = stream.readLine();
                if (current_line == START_MARKER)
                {
                    reading_started = true;
                    continue;
                }

                if (reading_started) {
                    QStringList current_topic_data = current_line.split(' ');

                    for (int i = 0; i < current_topic_data.size(); ++i)
                    {
                        if (current_topic_data[i].isEmpty())
                            continue;

                        if (i == 0)  // read topic name
                        {
                            topic_names_->append(current_topic_data[i].mid(0,
                                                     current_topic_data[i].size() - 1));

                            interpret_level_->append(0);
                            ethnic_level_->append(0);
                        }

                        if (i > 0) {  // read topic data
                            if (i == 1)
                                topic_data_->append(QVector<QString>());

                            (*topic_data_)[topic_data_->size() - 1].append(
                                current_topic_data[i].mid(0, current_topic_data[i].size() - 1));
                        }
                    }
                }
            }
            if (!reading_started)
                throw std::runtime_error(QString().toStdString());
        }
        file.close();
    }
    catch(...)
    {
        auto dialog_file_open_error = new DialogFileOpenError(this);
        dialog_file_open_error->exec();
    }

    enableWorkspace();
    loadPage(0);
}

void MainWindow::enableWorkspace()
{
    ui_->EthnicNoneRButton->setEnabled(true);
    ui_->EthnicLowRButton->setEnabled(true);
    ui_->EthnicMiddleRButton->setEnabled(true);
    ui_->EthnicHighRButton->setEnabled(true);

    ui_->InterpretNoneRButton->setEnabled(true);
    ui_->InterpretLowRButton->setEnabled(true);
    ui_->InterpretMiddleRButton->setEnabled(true);
    ui_->InterpretHighRButton->setEnabled(true);

    ui_->ProgressBar->setEnabled(true);
    ui_->NextButton->setEnabled(true);
    ui_->NameEdit->setEnabled(true);
    ui_->TokensList->setEnabled(true);
    ui_->NameEdit->setReadOnly(true);

    ui_->InterpretNoneRButton->setChecked(true);
    ui_->EthnicNoneRButton->setChecked(true);
    ui_->NameEdit->clear();

    while (ui_->TokensList->rowCount())
        ui_->TokensList->removeRow(0);

    ui_->TokensList->setColumnWidth(0, 200);
    ui_->TokensList->setColumnWidth(1, 80);

    ui_->ProgressBar->setValue(0);
}

void MainWindow::loadPage(int index)
{
    // ToDo (MelLain): remove code duplication and all constants
    while (ui_->TokensList->rowCount())
        ui_->TokensList->removeRow(0);

    ui_->TokensList->setColumnWidth(0, 200);
    ui_->TokensList->setColumnWidth(1, 80);

    if (index == 0)
        ui_->PrevButton->setEnabled(false);

    if (index > 0) {
        ui_->PrevButton->setEnabled(true);
        ui_->NextButton->setText("Следующая");
        last_index_ = false;
    }

    if (index == topic_names_->size() - 1)
    {
        ui_->NextButton->setText("Результаты");
        last_index_ = true;
    }

    ui_->NameEdit->setText((*topic_names_)[index]);

    for (int i = 0; i < (*topic_data_)[index].size(); ++i)
    {
        ui_->TokensList->insertRow(ui_->TokensList->rowCount());

        auto item_ptr = new QTableWidgetItem((*topic_data_)[index][i]);
        item_ptr->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui_->TokensList->setItem(ui_->TokensList->rowCount() - 1, 0, item_ptr);

        auto check_box_ptr = new QCheckBox();
        check_box_ptr->setChecked(false);
        ui_->TokensList->setCellWidget(ui_->TokensList->rowCount() - 1, 1, check_box_ptr);
    }

    for (int i = 0; i < ui_->TokensList->rowCount(); ++i)
    {
        QString token = ui_->TokensList->item(i, 0)->text();
        QMap<QString, QVector<int> >::iterator indices_iter = checked_tokens_->find(token);

        bool checked_flag = true;
        if (indices_iter == checked_tokens_->end())
            checked_flag = false;
        else
        {
            auto iter = std::find(indices_iter.value().begin(),
                                  indices_iter.value().end(),
                                  current_index_);

            if (iter == indices_iter.value().end())
                checked_flag = false;
        }

        (dynamic_cast<QCheckBox*>(ui_->TokensList->cellWidget(i, 1)))->setChecked(checked_flag);
    }

    switch ((*interpret_level_)[index])
    {
        case 0: ui_->InterpretNoneRButton->setChecked(true); break;
        case 1: ui_->InterpretLowRButton->setChecked(true); break;
        case 2: ui_->InterpretMiddleRButton->setChecked(true); break;
        case 3: ui_->InterpretHighRButton->setChecked(true); break;
    }

    switch ((*ethnic_level_)[index])
    {
        case 0: ui_->EthnicNoneRButton->setChecked(true); break;
        case 1: ui_->EthnicLowRButton->setChecked(true); break;
        case 2: ui_->EthnicMiddleRButton->setChecked(true); break;
        case 3: ui_->EthnicHighRButton->setChecked(true); break;
    }

    ui_->ProgressBar->setValue(float(index + 1) / ethnic_level_->size() * 100);
}

void MainWindow::nextPage()
{
    switch (ui_->InterpretButtonGroup->checkedId())
    {
        case -5: (*interpret_level_)[current_index_] = 0; break;
        case -2: (*interpret_level_)[current_index_] = 1; break;
        case -3: (*interpret_level_)[current_index_] = 2; break;
        case -4: (*interpret_level_)[current_index_] = 3; break;
    }

    switch (ui_->EthnicButtonGroup->checkedId())
    {
        case -5: (*ethnic_level_)[current_index_] = 0; break;
        case -2: (*ethnic_level_)[current_index_] = 1; break;
        case -3: (*ethnic_level_)[current_index_] = 2; break;
        case -4: (*ethnic_level_)[current_index_] = 3; break;
    }

    saveCheckedTokens();

    last_index_ = (current_index_ == ethnic_level_->size() - 1);
    if (last_index_)
        showResults();
    else
        loadPage(++current_index_);
}

void MainWindow::prevPage()
{
    switch (ui_->InterpretButtonGroup->checkedId())
    {
        case -5: (*interpret_level_)[current_index_] = 0; break;
        case -2: (*interpret_level_)[current_index_] = 1; break;
        case -3: (*interpret_level_)[current_index_] = 2; break;
        case -4: (*interpret_level_)[current_index_] = 3; break;
    }

    switch (ui_->EthnicButtonGroup->checkedId())
    {
        case -5: (*ethnic_level_)[current_index_] = 0; break;
        case -2: (*ethnic_level_)[current_index_] = 1; break;
        case -3: (*ethnic_level_)[current_index_] = 2; break;
        case -4: (*ethnic_level_)[current_index_] = 3; break;
    }

    saveCheckedTokens();

    last_index_ = false;
    loadPage(--current_index_);
}

void MainWindow::showResults()
{
    auto dialog_results = new DialogResults(interpret_level_, ethnic_level_, checked_tokens_, this);
    dialog_results->exec();
}

void MainWindow::saveCheckedTokens()
{
    for (int i = 0; i < ui_->TokensList->rowCount(); ++i)
    {
        QString token = ui_->TokensList->item(i, 0)->text();
        bool is_checked = (dynamic_cast<QCheckBox*>(ui_->TokensList->cellWidget(i, 1)))->isChecked();

        QMap<QString, QVector<int> >::iterator indices_iter = checked_tokens_->find(token);

        if (is_checked)
        {
            if (indices_iter == checked_tokens_->end())
                checked_tokens_->insert(token, QVector<int>(1, current_index_));

            else
            {
                auto iter = std::find(indices_iter.value().begin(),
                                      indices_iter.value().end(),
                                      current_index_);

                if (iter == indices_iter.value().end())
                    indices_iter.value().append(current_index_);
            }
        }
        else
        {
            if (indices_iter != checked_tokens_->end())
            {
                indices_iter.value().erase(std::remove(indices_iter.value().begin(),
                                                       indices_iter.value().end(),
                                                       current_index_),
                                           indices_iter.value().end());
            }
        }
    }
}
