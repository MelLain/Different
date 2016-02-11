#-------------------------------------------------
#
# Project created by QtCreator 2016-02-07T13:26:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TopicViewer
TEMPLATE = app


SOURCES += main.cpp \
    main_window.cpp \
    dialog_file_open_error.cpp \
    dialog_results.cpp

HEADERS  += \
    main_window.h \
    dialog_file_open_error.h \
    dialog_results.h

FORMS    += \
    main_window.ui \
    dialog_file_open_error.ui \
    dialog_results.ui
