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

#include "mediaWidget.h"
#include "treemodel.h"

MediaWidget::MediaWidget(QWidget *parent)
    : QWidget(parent)
{
    mediaView     = new QTreeView;
    actionsMenu   = new QMenu;
    statusBar     = new QStatusBar;
    mainLayout    = new QVBoxLayout(this);
    groupBox      = new QGroupBox(trUtf8("Medienübersicht"));
    outerLayout   = new QGridLayout;

    mainLayout->addWidget(groupBox);
    groupBox->setLayout(outerLayout);
    outerLayout->addWidget(mediaView, 2, 2);
//    outerLayout->addWidget(statusBar, 3, 1, 1, 3);       //* Der Widget hat eine (optionale) Statuszeile
//    mainLayout->addWidget(actionsMenu);

#ifdef Q_WS_MAEMO_5
    // Alternating row colors look bad on Maemo
    mediaView->setAlternatingRowColors(false);
#endif

    TreeModel *model = loadFile();

    mediaView->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column) {
        mediaView->resizeColumnToContents(column);
        if (mediaView->columnWidth(column) < 50 ) mediaView->setColumnWidth(column, 50);
    }
    mediaView->setColumnWidth(0, 200);
//    mediaView->setSortingEnabled(true);

    connect(mediaView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));   //*

    createActions();
    updateActions();

    createToolBars();
    outerLayout->addWidget(toolBar, 3, 1, 1, 2);    // Die Toolbar des Widgets

    createMediaTypeView();
    outerLayout->addWidget(mediaTypeView, 2, 1);

}


TreeModel * MediaWidget::loadFile()
{
    QStringList headers;
    headers << trUtf8("Medien-ID") << trUtf8("Bezeichnung") << trUtf8("Medienspezifisch 1") << trUtf8("Medienspezifisch 2") << tr("Beschreibung");
    //*    QFile file(":/default.txt");
    QString fileName = QFileDialog::getOpenFileName(this,trUtf8("Medienverwaltungsdatei öffnen"));

    TreeModel *model;
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        model = new TreeModel(headers, file.readAll());
        file.close();
    } else {
        model = new TreeModel(headers, "[Keine Medien enthalten]");
    }
    return model;
}

void MediaWidget::createMediaTypeView()
{
    mediaTypeView = new QListView;
    mediaTypeView->setFixedWidth(150);

    // Liste der Medientypen zum Anlegen neuer Medien
    mediaTypeView->setModel(mediaView->model());
    mediaTypeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mediaTypeView->setStatusTip(trUtf8("Gewünschten Medientyp zum Erstellen anklicken"));

    mediaTypeView->connect(mediaTypeView, SIGNAL(clicked(QModelIndex)), this, SLOT(insertChild(QModelIndex)));
}

void MediaWidget::createActions()
{
    insertRowAction = new QAction(trUtf8("Neuen &Medientyp anlegen"), this);
    insertRowAction->setStatusTip(trUtf8("Legt einen neuen Medientyp an"));
    connect(insertRowAction, SIGNAL(triggered()), this, SLOT(insertRow()));

    insertColumnAction = new QAction(trUtf8("&Spalte einfügen"), this);
    insertColumnAction->setStatusTip(trUtf8("Fügt eine neue Eigenschaftenspalte ein"));
    connect(insertColumnAction, SIGNAL(triggered()), this, SLOT(insertColumn()));

    removeRowAction = new QAction(trUtf8("Eintrag &entfernen"), this);
    removeRowAction->setStatusTip(trUtf8("Entfernt das aktuelle Medium bzw. den Medientyp"));
    connect(removeRowAction, SIGNAL(triggered()), this, SLOT(removeRow()));

    removeColumnAction = new QAction(trUtf8("Spalte en&tfernen"), this);
    removeColumnAction->setStatusTip(trUtf8("Entfernt die aktuelle Eigenschaftenspalte"));
    connect(removeColumnAction, SIGNAL(triggered()), this, SLOT(removeColumn()));

    insertChildAction = new QAction(trUtf8("&Untereintrag einfügen"), this);
    insertChildAction->setStatusTip(trUtf8("Fügt einen neuen Untereintrag ein"));
    connect(insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));
}

void MediaWidget::insertChild()
{
    QModelIndex index = mediaView->selectionModel()->currentIndex();
    insertChild(index);
}

void MediaWidget::insertChild(QModelIndex index)
{
    QAbstractItemModel *model = mediaView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(trUtf8("[Neuer Eintrag]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant(trUtf8("[No header]")),
                                 Qt::EditRole);
    }

    mediaView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MediaWidget::insertColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = mediaView->model();
    int column = mediaView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1, parent);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant(trUtf8("[No header]")),
                             Qt::EditRole);

    updateActions();

    return changed;
}

void MediaWidget::insertRow()
{
    QModelIndex index = mediaView->selectionModel()->currentIndex();
    QAbstractItemModel *model = mediaView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant(trUtf8("[Neuer Eintrag]")), Qt::EditRole);
    }
}

bool MediaWidget::removeColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = mediaView->model();
    int column = mediaView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column, parent);

    if (!parent.isValid() && changed)
        updateActions();

    return changed;
}

void MediaWidget::removeRow()
{
    QModelIndex index = mediaView->selectionModel()->currentIndex();
    QAbstractItemModel *model = mediaView->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MediaWidget::updateActions()
{
    bool hasSelection = !mediaView->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    bool hasCurrent = mediaView->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        mediaView->closePersistentEditor(mediaView->selectionModel()->currentIndex());

        int row = mediaView->selectionModel()->currentIndex().row();
        int column = mediaView->selectionModel()->currentIndex().column();
        if (mediaView->selectionModel()->currentIndex().parent().isValid()) {
            statusBar->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        } else {
            statusBar->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        }
    }
}

void MediaWidget::createToolBars()
{
    toolBar = new QToolBar("Einträge bearbeiten");
//    toolBar->addAction(insertRowAction);
    toolBar->addAction(insertColumnAction);
    toolBar->addAction(removeRowAction);
    toolBar->addAction(removeColumnAction);
//    toolBar->addAction(insertChildAction);
//    toolBar->addSeparator();
}
