#include "dialog_results.h"
#include "ui_dialog_results.h"

#include <QFileDialog>
#include <QTextStream>

DialogResults::DialogResults(std::shared_ptr<QVector<int> > interpret_level,
                             std::shared_ptr<QVector<int> > ethnic_level,
                             std::shared_ptr<QMap<QString, QVector<int>> > checked_tokens,
                             std::shared_ptr<QVector<QString> > topic_names,
                             QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::DialogResults),
    interpret_level_(interpret_level),
    ethnic_level_(ethnic_level),
    checked_tokens_(checked_tokens),
    topic_names_(topic_names)
{
    ui_->setupUi(this);

    setTextFields();

    connect(ui_->CancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui_->ExitButton, SIGNAL(clicked()), this, SLOT(globalExit()));
    connect(ui_->SaveButton, SIGNAL(clicked()), this, SLOT(saveResults()));
}

DialogResults::~DialogResults()
{
    delete ui_;
}

void DialogResults::setTextFields()
{
    int interpret_none_count = 0;
    int interpret_low_count = 0;
    int interpret_middle_count = 0;
    int interpret_high_count = 0;

    int ethnic_none_count = 0;
    int ethnic_low_count = 0;
    int ethnic_middle_count = 0;
    int ethnic_high_count = 0;

    for (int i = 0; i < interpret_level_->size(); ++i) {
        if ((*interpret_level_)[i] == 0) interpret_none_count += 1;
        if ((*interpret_level_)[i] == 1) interpret_low_count += 1;
        if ((*interpret_level_)[i] == 2) interpret_middle_count += 1;
        if ((*interpret_level_)[i] == 3) interpret_high_count += 1;

        if ((*ethnic_level_)[i] == 0) ethnic_none_count += 1;
        if ((*ethnic_level_)[i] == 1) ethnic_low_count += 1;
        if ((*ethnic_level_)[i] == 2) ethnic_middle_count += 1;
        if ((*ethnic_level_)[i] == 3) ethnic_high_count += 1;
    }

    ui_->InterpretNoneEdit->setText(
                QString::number(interpret_none_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    ui_->InterpretLowEdit->setText(
                QString::number(interpret_low_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    ui_->InterpretMiddleEdit->setText(
                QString::number(interpret_middle_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    ui_->InterpretHighEdit->setText(
                QString::number(interpret_high_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));


    ui_->EthnicNoneEdit->setText(
                QString::number(ethnic_none_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    ui_->EthnicLowEdit->setText(
                QString::number(ethnic_low_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    ui_->EthnicMiddleEdit->setText(
                QString::number(ethnic_middle_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    ui_->EthnicHighEdit->setText(
                QString::number(ethnic_high_count) +
                QString(" / ") +
                QString::number(interpret_level_->size()));

    int checked_tokens_count = checked_tokens_->size();
    ui_->SavedTokensCountField->setText(QString::number(checked_tokens_count));
    for (int i = 0; i < checked_tokens_count; ++i)
        ui_->TokensList->insertItem(i, checked_tokens_->keys()[i]);
}

void DialogResults::saveResults()
{
    int topics_count = interpret_level_->size();
    // ToDo (MelLain): remove code duplication
    int interpret_none_count = 0;
    int interpret_low_count = 0;
    int interpret_middle_count = 0;
    int interpret_high_count = 0;

    int ethnic_none_count = 0;
    int ethnic_low_count = 0;
    int ethnic_middle_count = 0;
    int ethnic_high_count = 0;

    for (int i = 0; i < topics_count; ++i) {
        if ((*interpret_level_)[i] == 0) interpret_none_count += 1;
        if ((*interpret_level_)[i] == 1) interpret_low_count += 1;
        if ((*interpret_level_)[i] == 2) interpret_middle_count += 1;
        if ((*interpret_level_)[i] == 3) interpret_high_count += 1;

        if ((*ethnic_level_)[i] == 0) ethnic_none_count += 1;
        if ((*ethnic_level_)[i] == 1) ethnic_low_count += 1;
        if ((*ethnic_level_)[i] == 2) ethnic_middle_count += 1;
        if ((*ethnic_level_)[i] == 3) ethnic_high_count += 1;
    }

    QString file_name = QFileDialog::getSaveFileName(this,
                            tr("Save file with results"), "/", tr("Text Files (*.txt)"));

    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << "Topics count          = " << topics_count << endl << endl;

        stream << "None interpretation   = " << interpret_none_count << endl;
        stream << "Low interpretation    = " << interpret_low_count << endl;
        stream << "Middle interpretation = " << interpret_middle_count << endl;
        stream << "High interpretation   = " << interpret_high_count << endl << endl;

        stream << "None ethnicity        = " << ethnic_none_count << endl;
        stream << "Low ethnicity         = " << ethnic_low_count << endl;
        stream << "Middle ethnicity      = " << ethnic_middle_count << endl;
        stream << "High ethnicity        = " << ethnic_high_count << endl;

        int checked_tokens_count = checked_tokens_->size();
        stream << "Saved tokens count    = " << checked_tokens_count << endl << endl;
        for (int i = 0; i < checked_tokens_count; ++i)
            stream << checked_tokens_->keys()[i] << endl;

        stream << "\nTopics info. Pattern: topic_name, interpretation (0,1,2,3), "
               << "ethnicity (0,1,2,3)" << checked_tokens_count << endl << endl;
        for (int i = 0; i < topics_count; ++i)
            stream << (*topic_names_)[i] << ", " << (*interpret_level_)[i]
                                         << ", " << (*ethnic_level_)[i] << endl;
    }
    file.close();
}

void DialogResults::globalExit()
{
    parentWidget()->close();
}
