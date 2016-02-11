#ifndef DIALOG_FILE_OPEN_ERROR_H
#define DIALOG_FILE_OPEN_ERROR_H

#include <QDialog>

namespace Ui {
class DialogFileOpenError;
}

class DialogFileOpenError : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFileOpenError(QWidget* parent = 0);
    ~DialogFileOpenError();

private:
    Ui::DialogFileOpenError* ui_;
};

#endif // DIALOG_FILE_OPEN_ERROR_H
