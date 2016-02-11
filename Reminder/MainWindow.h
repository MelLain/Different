#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "common.h"

namespace Ui {
class MainWindow;
}

class Money
{
public:
    Money();

    void setCurRubNalValue(int value);
    void setCurEurNalValue(int value);
    void setCurUsdNalValue(int value);
    void setCurRubElecValue(int value);
    void setCurEurElecValue(int value);
    void setCurUsdElecValue(int value);

    void setOldRubNalValue(int value);
    void setOldEurNalValue(int value);
    void setOldUsdNalValue(int value);
    void setOldRubElecValue(int value);
    void setOldEurElecValue(int value);
    void setOldUsdElecValue(int value);

    inline int getCurRubNalValue() { return cur_rub_nal_value_; }
    inline int getCurEurNalValue() { return cur_eur_nal_value_; }
    inline int getCurUsdNalValue() { return cur_usd_nal_value_; }
    inline int getCurRubElecValue() { return cur_rub_elec_value_; }
    inline int getCurEurElecValue() { return cur_eur_elec_value_; }
    inline int getCurUsdElecValue() { return cur_usd_elec_value_; }

    inline int getOldRubNalValue() { return old_rub_nal_value_; }
    inline int getOldEurNalValue() { return old_eur_nal_value_; }
    inline int getOldUsdNalValue() { return old_usd_nal_value_; }
    inline int getOldRubElecValue() { return old_rub_elec_value_; }
    inline int getOldEurElecValue() { return old_eur_elec_value_; }
    inline int getOldUsdElecValue() { return old_usd_elec_value_; }

    inline int getRubDiffValue() { return rub_diff_value_; }
    inline int getEurDiffValue() { return eur_diff_value_; }
    inline int getUsdDiffValue() { return usd_diff_value_; }

private:
    int cur_rub_nal_value_;
    int cur_eur_nal_value_;
    int cur_usd_nal_value_;
    int cur_rub_elec_value_;
    int cur_eur_elec_value_;
    int cur_usd_elec_value_;

    int old_rub_nal_value_;
    int old_eur_nal_value_;
    int old_usd_nal_value_;
    int old_rub_elec_value_;
    int old_eur_elec_value_;
    int old_usd_elec_value_;

    int rub_diff_value_;
    int eur_diff_value_;
    int usd_diff_value_;
};

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
    void changeMoneyDiff();
    void requestExit();
    void setQLineEditColor(QLineEdit* line_edit_ptr, int value);

private:
    Ui::MainWindow* ui_;

    QString data_file_name_;
    QString password_;

    Money money_;
};

#endif // MAIN_WINDOW_H
