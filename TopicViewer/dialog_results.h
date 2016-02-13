#ifndef DIALOG_RESULTS_H
#define DIALOG_RESULTS_H

#include <memory>

#include <QDialog>
#include <QMap>

namespace Ui {
class DialogResults;
}

class DialogResults : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResults(std::shared_ptr<QVector<int> > interpret_level,
                           std::shared_ptr<QVector<int> > ethnic_level,
                           std::shared_ptr<QMap<QString, QVector<int>> > checked_tokens,
                           std::shared_ptr<QVector<QString> > topic_names,
                           QWidget* parent = 0);
    ~DialogResults();

private slots:
    void saveResults();
    void setTextFields();
    void globalExit();

private:
    Ui::DialogResults* ui_;

    std::shared_ptr<QVector<int> > interpret_level_;
    std::shared_ptr<QVector<int> > ethnic_level_;
    std::shared_ptr<QMap<QString, QVector<int>> > checked_tokens_;
    std::shared_ptr<QVector<QString> > topic_names_;
};

#endif // DIALOG_RESULTS_H
