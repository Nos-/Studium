##########################################################################################
# \brief Dies ist ein Medienverwaltungsprogramm // This is an mediamanagementapplication
#
# \Author Norman Schwirz <nospam.schwirz AT freenet PUNKT de> (Bitte die großgeschriebenen Wörter in der Emailadr. entspr. ersetzen!)
#
# \License GPLv3
# Kurz umrissen heist dies vor allem: Dies ist Freie Software, mach damit was du willst, solange du immer den Quellcode des kompletten Programms (inklusive der Autorenangabe und dieser Lizenzinfo) mitlieferst. Außerdem muss im Programm selbst bzw. dessen Dokumentation darauf hingewiesen werden.
#
##########################################################################################

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

FORMS +=
