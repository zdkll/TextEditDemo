#-------------------------------------------------
#
# Project created by QtCreator 2019-05-30T13:25:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTextEditDemo
TEMPLATE = app


SOURCES += main.cpp\
        texteditwidget.cpp \
    mysplashscreen.cpp \
    textbrowser.cpp

HEADERS  += texteditwidget.h \
    mysplashscreen.h \
    textbrowser.h

FORMS    += texteditwidget.ui

RESOURCES += \
    qrc.qrc
