#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <memory>

#include <QVector>
#include <QString>
#include <QMap>

#include <QMainWindow>

const QString START_MARKER = QString("============ Model top tokens ============");

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
    void resetMainWindow();
    void openFile();
    void enableWorkspace();
    void loadPage(int index);
    void nextPage();
    void prevPage();
    void showResults();
    void saveCheckedTokens();

private:
    Ui::MainWindow* ui_;

    QString source_file_name_;
    std::shared_ptr<QVector<QString> > topic_names_;
    std::shared_ptr<QVector<QVector<QString>> > topic_data_;
    int current_index_;
    std::shared_ptr<QVector<int> > interpret_level_;
    std::shared_ptr<QVector<int> > ethnic_level_;
    bool last_index_;
    std::shared_ptr<QMap<QString, QVector<int>> > checked_tokens_;
};

#endif // MAIN_WINDOW_H
