#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T21:05:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = addressbook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        addressbookwidget/addressbookwidget.cpp\
        addressbookwidget/finddialog.cpp

HEADERS  += mainwindow.h\
         addressbookwidget/addressbookwidget.h\
         addressbookwidget/finddialog.h

RESOURCES += mainwindow.qrc
