QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = medienverwaltung
TEMPLATE = app


SOURCES += main.cpp \
    mylistmodelwidget/mylistmodelwidget.cpp \
    mainwindow.cpp

HEADERS  += \
    mylistmodelwidget/mylistmodelwidget.h \
    mainwindow.h

RESOURCES += \
    medienverwaltung.qrc
