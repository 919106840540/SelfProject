#-------------------------------------------------
#
# Project created by QtCreator 2020-08-02T14:45:46
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raisingPigs
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    pig.cpp \
    pighouse.cpp \
    form_pig.cpp \
    form_sales.cpp \
    form_chart.cpp

HEADERS += \
        widget.h \
    pig.h \
    pighouse.h \
    form_pig.h \
    form_sales.h \
    form_chart.h

FORMS += \
        widget.ui \
    form_pig.ui \
    form_sales.ui \
    form_chart.ui

