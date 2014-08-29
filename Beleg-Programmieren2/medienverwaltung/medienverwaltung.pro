QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = medienverwaltung
TEMPLATE = app


SOURCES += main.cpp \
    MediaListmodelWidget/MediaListmodelWidget.cpp \
    PersonListmodelWidget/PersonListmodelWidget.cpp \
    mainwindow.cpp

HEADERS  += \
    MediaListmodelWidget/MediaListmodelWidget.h \
    PersonListmodelWidget/PersonListmodelWidget.h \
    mainwindow.h

RESOURCES += \
    medienverwaltung.qrc
