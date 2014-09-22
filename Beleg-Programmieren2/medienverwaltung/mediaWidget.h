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

#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#include <QMainWindow>
#include <QModelIndex>
#include <QToolBar>
#include <QListView>
#include <QGroupBox>
#include <QGridLayout>
#include <QMenu>

#include "treemodel.h"

class QAction;
class QTreeView;
class QWidget;
class QMenu;
class QGroupBox;

class MediaWidget : public QWidget
{
    Q_OBJECT

public:
    MediaWidget(QWidget *parent = 0);
    QMenu   *actionsMenu;
    QAction *insertRowAction;
    QAction *insertColumnAction;
    QAction *removeRowAction;
    QAction *removeColumnAction;
    QAction *insertChildAction;


public slots:
    void updateActions();
    void insertChild();
    void insertChild(QModelIndex index);
    bool insertColumn(const QModelIndex &parent = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();
    void resizeColumnWidth(int column);
    bool loadFile();
    bool saveFile();

private:
    QTreeView   *mediaView;
    QListView   *mediaTypeView;
    QVBoxLayout *mainLayout;
    QGridLayout *outerLayout;
    QStatusBar  *statusBar;
    QToolBar    *toolBar;
    QGroupBox   *groupBox;

    void createToolBars();
    void createActions();
    void createMediaTypeView();
//*    TreeModel * loadModelFromFile();
    bool saveModelToFile(QAbstractItemModel *model);
    QString* getItemData(QAbstractItemModel *model, QModelIndex parent = QModelIndex(), int level=-1);
//    QString* getItemData(QModelIndex index, int level=0);

private slots:
};

#endif // MEDIAWIDGET_H
