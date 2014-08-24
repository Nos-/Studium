/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is is based on a example of the Qt Toolkit.
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

 MainWindow::MainWindow()
 {
     addressBookW = new AddressBookWidget;
     setCentralWidget(addressBookW);

     createActions();
     createMenus();
     createToolBars();
     createStatusBar();

     readSettings();

//*     connect(textEdit->document(), SIGNAL(contentsChanged()),
//             this, SLOT(documentWasModified()));

     connect(addressBookW, SIGNAL(interfaceModeChanged()), this, SLOT(updateMainInterface()));

//*     setCurrentFile("");
     updateMainInterface();
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

 void MainWindow::newFile()
 {
//*     if (maybeSave()) {
         addressBookW->emptyContacts(); //*
//*         setCurrentFile("");
         statusBar()->showMessage(tr("Contactslist emptied"), 2000);
//*     }
 }

 void MainWindow::open()
 {
//     if (maybeSave()) {
//         QString fileName = QFileDialog::getOpenFileName(this);
//         if (!fileName.isEmpty())
             addressBookW->loadFromFile();  //*
//     }
//     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
 }

 bool MainWindow::save()
 {
//     if (curFile.isEmpty()) {
//         return saveAs();
//     } else {
         addressBookW->saveToFile();  //*
//     }
//     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File saved"), 2000);
     return true;   //*
 }

 bool MainWindow::saveAs()
 {
//     QString fileName = QFileDialog::getSaveFileName(this);
//     if (fileName.isEmpty())
//         return false;

     addressBookW->saveToFile(); //*

//     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File saved"), 2000);
     return true;   //*
 }

 void MainWindow::about()
 {
    QMessageBox::about(this, tr("About Simple Addressbook"),
             tr("This <b>Simple Addressbook Application</b> is my first QT-application and based on several tutorials I worked trough."));
 }

// void MainWindow::documentWasModified()
// {
//*     setWindowModified(textEdit->document()->isModified());
// }

 void MainWindow::createActions()
 {
     newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
     newAct->setShortcuts(QKeySequence::New);
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
     openAct->setShortcuts(QKeySequence::Open);
     openAct->setStatusTip(tr("Open an existing file"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
     saveAct->setShortcuts(QKeySequence::Save);
     saveAct->setStatusTip(tr("Save the document to disk"));
     connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

     saveAsAct = new QAction(tr("Save &As..."), this);
     saveAsAct->setShortcuts(QKeySequence::SaveAs);
     saveAsAct->setStatusTip(tr("Save the document under a new name"));
     connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

     exitAct = new QAction(tr("E&xit"), this);
     exitAct->setShortcuts(QKeySequence::Quit);
     exitAct->setStatusTip(tr("Exit the application"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

//     cutAct->setEnabled(false);
//     copyAct->setEnabled(false);
//     connect(textEdit, SIGNAL(copyAvailable(bool)),
//             cutAct, SLOT(setEnabled(bool)));
//     connect(textEdit, SIGNAL(copyAvailable(bool)),
//             copyAct, SLOT(setEnabled(bool)));
 }

 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(newAct);
     fileMenu->addAction(openAct);
     fileMenu->addAction(saveAct);
     fileMenu->addAction(saveAsAct);
     fileMenu->addSeparator();
     fileMenu->addAction(exitAct);

     editMenu = menuBar()->addMenu(tr("&Edit"));

     menuBar()->addSeparator();

     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);
 }

 void MainWindow::createToolBars()
 {
     fileToolBar = addToolBar(tr("File"));
     fileToolBar->addAction(newAct);
     fileToolBar->addAction(openAct);
     fileToolBar->addAction(saveAct);

     editToolBar = addToolBar(tr("Edit"));
 }

 void MainWindow::createStatusBar()
 {
     statusBar()->showMessage(tr("Ready"));
 }

 void MainWindow::readSettings()
 {
     QSettings settings("Nos-", "Simple Addressbook");
     QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
     QSize size = settings.value("size", QSize(400, 400)).toSize();
     resize(size);
     move(pos);
 }

 void MainWindow::writeSettings()
 {
     QSettings settings("Nos-", "Simple Addressbook");
     settings.setValue("pos", pos());
     settings.setValue("size", size());
 }

 bool MainWindow::maybeSave()
 {
 //*    if (textEdit->document()->isModified()) {
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning(this, tr("Application"),
                      tr("The document has been modified.\n"
                         "Do you want to save your changes?"),
                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         if (ret == QMessageBox::Save)
             return save();
         else if (ret == QMessageBox::Cancel)
             return false;
//*     }
     return true;
 }

// void MainWindow::loadFile(const QString &fileName)
// {
//     QFile file(fileName);
//     if (!file.open(QFile::ReadOnly | QFile::Text)) {
//         QMessageBox::warning(this, tr("Application"),
//                              tr("Cannot read file %1:\n%2.")
//                              .arg(fileName)
//                              .arg(file.errorString()));
//         return;
//     }

//     QTextStream in(&file);
// #ifndef QT_NO_CURSOR
//     QApplication::setOverrideCursor(Qt::WaitCursor);
// #endif
////*     textEdit->setPlainText(in.readAll());
// #ifndef QT_NO_CURSOR
//     QApplication::restoreOverrideCursor();
// #endif

//     setCurrentFile(fileName);
//     statusBar()->showMessage(tr("File loaded"), 2000);
// }

// bool MainWindow::saveFile(const QString &fileName)
// {
//     QFile file(fileName);
//     if (!file.open(QFile::WriteOnly | QFile::Text)) {
//         QMessageBox::warning(this, tr("Application"),
//                              tr("Cannot write file %1:\n%2.")
//                              .arg(fileName)
//                              .arg(file.errorString()));
//         return false;
//     }

//     QTextStream out(&file);
// #ifndef QT_NO_CURSOR
//     QApplication::setOverrideCursor(Qt::WaitCursor);
// #endif
////*     out << textEdit->toPlainText();
// #ifndef QT_NO_CURSOR
//     QApplication::restoreOverrideCursor();
// #endif

//     setCurrentFile(fileName);
//     statusBar()->showMessage(tr("File saved"), 2000);
//     return true;
// }

// void MainWindow::setCurrentFile(const QString &fileName)
// {
//     curFile = fileName;
// //*    textEdit->document()->setModified(false);
//     setWindowModified(false);

//     QString shownName = curFile;
//     if (curFile.isEmpty())
//         shownName = "untitled.txt";
//     setWindowFilePath(shownName);
// }

// QString MainWindow::strippedName(const QString &fullFileName)
// {
//     return QFileInfo(fullFileName).fileName();
// }

void MainWindow::updateMainInterface()
{
    if (addressBookW->getCurrentMode() == AddressBookWidget::NavigationMode) {  //*
        newAct->setEnabled(true);
        newAct->setEnabled(true);
        openAct->setEnabled(true);
        saveAct->setEnabled(true);
        saveAsAct->setEnabled(true);
        exitAct->setEnabled(true);
    } else if (addressBookW->getCurrentMode() == AddressBookWidget::AddingMode || AddressBookWidget::EditingMode ) {  //*
        newAct->setEnabled(false);
        newAct->setEnabled(false);
        openAct->setEnabled(false);
        saveAct->setEnabled(false);
        saveAsAct->setEnabled(false);
        exitAct->setEnabled(false);
    }
}
