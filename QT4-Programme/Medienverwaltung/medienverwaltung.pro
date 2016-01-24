HEADERS     = mainwindow.h \
              mediaWidget.h \
              treeitem.h \
              treemodel.h
RESOURCES   = medienverwaltung.qrc
SOURCES     = main.cpp \
              mainwindow.cpp \
              mediaWidget.cpp \
              treeitem.cpp \
              treemodel.cpp
CONFIG  += qt


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = medienverwaltung
TEMPLATE = app
