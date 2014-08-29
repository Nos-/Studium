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
**     notices, this list of conditions and the following disclaimer.
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

MainWindow::MainWindow()
{
    setWindowTitle(trUtf8("Medienverwaltung"));
    QSplitter *splitter = new QSplitter(this);
    setCentralWidget(splitter);

    mediaListmodelWidget = new MediaListmodelWidget;
    mediaListModel = createMediaModel(mediaListmodelWidget);
    mediaListmodelWidget->setSourceModel(mediaListModel);
    splitter->addWidget(mediaListmodelWidget);

    personListmodelWidget = new PersonListmodelWidget;
    personListModel = createPersonModel(personListmodelWidget);
    personListmodelWidget->setSourceModel(personListModel);
    splitter->addWidget(personListmodelWidget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

//    connect(textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

//void MainWindow::newFile()
//{
//    if (maybeSave()) {
//        textEdit->clear();
//        setCurrentFile("");
//    }
//}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about()
{
   QMessageBox::about(this, trUtf8("über dieses Programm"),
            trUtf8("Die <b>Medienverwaltung</b> ist eine meiner (Norman Schwirz) ersten QT4-Applikationen."));
}

//void MainWindow::documentWasModified()
//{
//    setWindowModified(textEdit->document()->isModified());
//}

void MainWindow::createActions()
{
//    newAct = new QAction(QIcon(":/images/new.png"), trUtf8("&New"), this);
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(trUtf8("Create a new file"));
//    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), trUtf8("&Öffnen..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(trUtf8("Öffnet eine existierende Datei"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), trUtf8("&Speichern"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(trUtf8("Speichert in die aktuelle Datei"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(trUtf8("Speichern &unter..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(trUtf8("Speichert in eine neue Datei"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(trUtf8("B&eenden"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(trUtf8("Beendet das Programm"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/images/cut.png"), trUtf8("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(trUtf8("Cut the current selection's contents to the "
                            "clipboard"));
//    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), trUtf8("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(trUtf8("Copy the current selection's contents to the "
                             "clipboard"));
//    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), trUtf8("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(trUtf8("Paste the clipboard's contents into the current "
                              "selection"));
//    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(trUtf8("&Über dieses Programm"), this);
    aboutAct->setStatusTip(trUtf8("Zeigt das Infofenster dieses Programmes an"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(trUtf8("Über &Qt"), this);
    aboutQtAct->setStatusTip(trUtf8("Zeigt das Infofenster der QT-Bibliotheken an"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    pasteAct->setEnabled(false);
//    connect(textEdit, SIGNAL(copyAvailable(bool)),
//            cutAct, SLOT(setEnabled(bool)));
//    connect(textEdit, SIGNAL(copyAvailable(bool)),
//            copyAct, SLOT(setEnabled(bool)));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(trUtf8("&Datei"));
//*    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(trUtf8("&Bearbeiten"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(trUtf8("&Hilfe"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(trUtf8("Datei"));
//*    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(trUtf8("Bearbeiten"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(trUtf8("Bereit"));
}

void MainWindow::readSettings()
{
    QSettings settings("Nos-", "Medienverwaltung");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(800, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("Nos-", "Medienverwaltung");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool MainWindow::maybeSave()
{
//    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, trUtf8("Medienverwaltung"),
                     trUtf8("Sie haben Änderungen an den Einträgen vorgenommen.\n"
                        "Möchten sie diese speichern?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
//    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, trUtf8("Medienverwaltung"),
                             trUtf8("Fehler beim Einlesen der Datei %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
//*    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(trUtf8("Datei geöffnet"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, trUtf8("Medienverwaltung"),
                             trUtf8("Fehler beim Speichern in die Datei %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
//    qDebug << myListModel->children();                    //* Funzt leider nicht!
//    qDebug << myListModel->itemData();                    //*     -"-
//    out << textEdit->toPlainText();                       //*     -"-
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(trUtf8("Datei gespeichert"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
//*    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "unbenannt.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void MainWindow::addMediaItem(QAbstractItemModel *model, const QString &mediumId,
             const QString &mediumLabel, const QString &mediumType, const QString &mediumLentTo, const QString &mediumNotes)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), mediumId);
    model->setData(model->index(0, 1), mediumLabel);
    model->setData(model->index(0, 2), mediumType);
    model->setData(model->index(0, 3), mediumLentTo);
    model->setData(model->index(0, 4), mediumNotes);
}

QAbstractItemModel* MainWindow::createMediaModel(QObject *parent)     //*   *createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 5, parent);

    model->setHeaderData(0, Qt::Horizontal, QObject::trUtf8("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Bezeichnung"));
    model->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Typ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::trUtf8("ausgeliehen an"));
    model->setHeaderData(4, Qt::Horizontal, QObject::trUtf8("Notizen"));

    addMediaItem(model, "DieMaus_Folge123", "Die Sendung mit der Maus", "Video", "Kleiner blauer Elephant", ";-)");
    addMediaItem(model, "PAddG_Erstausgabe", "Per Anhalter durch die Galaxis", "Buch", "Alien von Nebenan", "Sollte man gelesen haben...");

    return model;
}

void MainWindow::addPersonItem(QAbstractItemModel *model, const QString &personId,
             const QString &firstName, const QString &surName, const QString &salutation, const QString &email, const QString &notes)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), personId);
    model->setData(model->index(0, 1), firstName);
    model->setData(model->index(0, 2), surName);
    model->setData(model->index(0, 3), salutation);
    model->setData(model->index(0, 4), email);
    model->setData(model->index(0, 6), notes);
}

QAbstractItemModel* MainWindow::createPersonModel(QObject *parent)     //*   *createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 5, parent);

    model->setHeaderData(0, Qt::Horizontal, QObject::trUtf8("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Vorname"));
    model->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Nachname"));
    model->setHeaderData(3, Qt::Horizontal, QObject::trUtf8("Anrede"));
    model->setHeaderData(4, Qt::Horizontal, QObject::trUtf8("Emailadresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::trUtf8("ausgeliehene Medien"));
    model->setHeaderData(6, Qt::Horizontal, QObject::trUtf8("Notizen"));

    addPersonItem(model, "BerndBrot", "Bernd", " das Brot", "", "DasBrot@kika.de", "");
    addPersonItem(model, "Briegel", "Briegel", " der Busch", "", "Busch@kika.de", ";-)");

    return model;
}
