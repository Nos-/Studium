/****************************************************************************
** \brief Dies ist ein Medienverwaltungsprogramm // This is an mediamanagementapplication
**
** \Author Norman Schwirz <nospam.schwirz AT freenet PUNKT de> (Bitte die großgeschriebenen Wörter in der Emailadr. entspr. ersetzen!)
**
** \License GPLv3
** Kurz umrissen heist dies vor allem: Dies ist Freie Software, mach damit was du willst, solange du immer den Quellcode des kompletten Programms (inklusive der Autorenangabe und dieser Lizenzinfo) mitlieferst. Außerdem muss im Programm selbst bzw. dessen Dokumentation darauf hingewiesen werden.
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is originally based of an example of the Qt Toolkit and adopted by me (N. Schwirz) to my needs.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "mainwindow.h"
#include "treemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(trUtf8("Medienverwaltung"));
    setWindowIcon(QIcon(":Medien"));
    splitter = new QSplitter(this);
    setCentralWidget(splitter);

    mediaWidget = new MediaWidget;
    splitter->addWidget(mediaWidget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
}

void MainWindow::createActions()
{
    loadFileAction = new QAction(trUtf8("Medienverwaltungsdatei &öffnen"), this);
    loadFileAction->setShortcuts(QKeySequence::Open);
    loadFileAction->setStatusTip(trUtf8("Liest die Medienverwaltungseinträge aus einer Datei ein"));
    loadFileAction->setIcon(QIcon(":DateiOeffnen"));
    connect(loadFileAction, SIGNAL(triggered()), mediaWidget, SLOT(loadFile()) );

    saveAsFileAction = new QAction(trUtf8("Datei &speichern"), this);
    saveAsFileAction->setShortcuts(QKeySequence::SaveAs);
    saveAsFileAction->setStatusTip(trUtf8("Speichert die Medienverwaltungseinträge in eine Datei"));
    saveAsFileAction->setIcon(QIcon(":DateiSpeichern"));
    connect(saveAsFileAction, SIGNAL(triggered()), mediaWidget, SLOT(saveFile()) );

    exitAction = new QAction(trUtf8("B&eenden"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(trUtf8("Beendet das Programm"));
    exitAction->setIcon(QIcon(":Beenden"));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    aboutAction = new QAction(trUtf8("&Über dieses Programm"), this);
    aboutAction->setStatusTip(trUtf8("Zeigt das Infofenster dieses Programmes an"));
    aboutAction->setIcon(QIcon(":Info"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(trUtf8("Über &Qt"), this);
    aboutQtAction->setStatusTip(trUtf8("Zeigt das Infofenster der QT-Bibliotheken an"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::about()
{
   QMessageBox::about(this, trUtf8("über dieses Programm"),
            trUtf8("Die <b>Medienverwaltung</b> ist eine meiner ersten QT4-Applikationen.\n "
                   "Sie entstand als Belegarbeit für die Lehrveranstaltung 'Programmieren2' bei Herrn Prof. Beck im Studiengang Informatik an der HTW Dresden im SS2014\n "
                   "Autor &Kontakt: Norman Schwirz (s70341@htw-dresden.de). "
                   "Dieses Programm gebe ich unter der <a href='https://www.gnu.org/licenses/gpl-3.0'>GPLv3 Lizenz</a> frei. (Natürlich <b>ohne Gewähr und Haftung. Nutzung auf eigenes Risiko!</b>) Weitere Informationen sowie der Quellcode befinden sich auf der Projektseite: <a href='https://github.com/Nos-/Studium/tree/master/Beleg-Programmieren2/medienverwaltung'>https://github.com/Nos-/Studium</a>."));
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(trUtf8("Bereit"));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(trUtf8("&Datei"));
    fileMenu->addAction(loadFileAction);
//    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsFileAction);
//    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(trUtf8("&Hilfe"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    MainToolBar = addToolBar(trUtf8("Haupt&werkzeugleiste"));
    MainToolBar->addAction(loadFileAction);
    MainToolBar->addAction(saveAsFileAction);
    MainToolBar->addAction(exitAction);
    MainToolBar->addAction(aboutAction);
}
