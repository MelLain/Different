#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#include <QDate>
#include <QString>
#include <QTableWidget>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QPalette>

const int RADIO_BUTTON_SHIFT = -2;
const QString DATA_FILE_PATH = QString("C:/Users/MelLain/reminder.dat");
const int MONEY_EDIT_FIELDS_COUNT = 12;
const int MONEY_DIFF_FIELDS_COUNT = 3;

const QString EVENT_LOW_RUS = QString("Низкий");
const QString EVENT_MIDDLE_RUS = QString("Средний");
const QString EVENT_HIGH_RUS = QString("Высокий");

const QString EVENT_LOW_COLOR = QString("green");
const QString EVENT_MIDDLE_COLOR = QString("yellow");
const QString EVENT_HIGH_COLOR = QString("red");

const QString FRIEND_LOW_RUS = QString("Приятель");
const QString FRIEND_MIDDLE_RUS = QString("Друг");
const QString FRIEND_HIGH_RUS = QString("Близкий друг");

#endif // COMMON_H
