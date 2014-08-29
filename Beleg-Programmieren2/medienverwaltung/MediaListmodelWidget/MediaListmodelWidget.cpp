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

#include "MediaListmodelWidget.h"

MediaListmodelWidget::MediaListmodelWidget()
{
    proxyModel = new QSortFilterProxyModel;
    proxyModel->setDynamicSortFilter(true);

//    sourceView = new QTreeView;
//    sourceView->setRootIsDecorated(false);
//    sourceView->setAlternatingRowColors(true);

    proxyView = new QTreeView;
    proxyView->setRootIsDecorated(false);
    proxyView->setAlternatingRowColors(true);
    proxyView->setModel(proxyModel);
    proxyView->setSortingEnabled(true);

    filterCaseSensitivityCheckBox = new QCheckBox(trUtf8("GROSS-/&kleinschreibung beachten"));

    filterPatternLineEdit = new QLineEdit;
    filterPatternLabel = new QLabel(trUtf8("&Suche nach:"));
    filterPatternLabel->setBuddy(filterPatternLineEdit);

    filterSyntaxComboBox = new QComboBox;
    filterSyntaxComboBox->addItem(trUtf8("Regulärer Ausdruck"), QRegExp::RegExp);
    filterSyntaxComboBox->addItem(trUtf8("Wildcard"), QRegExp::Wildcard);
    filterSyntaxComboBox->addItem(trUtf8("exakter Text"), QRegExp::FixedString);
    filterSyntaxLabel = new QLabel(trUtf8("Suchsy&ntax:"));
    filterSyntaxLabel->setBuddy(filterSyntaxComboBox);

    filterColumnComboBox = new QComboBox;
    filterColumnLabel = new QLabel(trUtf8("&in Spalte:"));
    filterColumnLabel->setBuddy(filterColumnComboBox);

    addItemBtn = new QPushButton(trUtf8("hinzufügen"));
    delItemBtn = new QPushButton(trUtf8("entfernen"));

    connect(filterPatternLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(filterRegExpChanged()));
    connect(filterSyntaxComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(filterRegExpChanged()));
    connect(filterColumnComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(filterColumnChanged()));
    connect(filterCaseSensitivityCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(filterRegExpChanged()));

    connect(addItemBtn, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(delItemBtn, SIGNAL(clicked()), this, SLOT(delItem()));

//#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
// //     sourceWidget = new QWidget;
//     filterWidget = new QWidget;
//     proxyWidget = new QWidget;

// //    QHBoxLayout *sourceLayout = new QHBoxLayout;
// //    sourceLayout->addWidget(sourceView);
// //    sourceWidget->setLayout(sourceLayout);

//    QGridLayout *filterLayout = new QGridLayout;
//    filterLayout->addWidget(filterPatternLabel, 1, 0);
//    filterLayout->addWidget(filterPatternLineEdit, 1, 1, 1, 2);
//    filterLayout->addWidget(filterSyntaxLabel, 2, 0);
//    filterLayout->addWidget(filterSyntaxComboBox, 2, 1, 1, 2);
//    filterLayout->addWidget(filterColumnLabel, 3, 0);
//    filterLayout->addWidget(filterColumnComboBox, 3, 1, 1, 2);
//    filterLayout->addWidget(filterCaseSensitivityCheckBox, 4, 0, 1, 2);
//    filterWidget->setLayout(filterLayout);

//    QHBoxLayout *proxyLayout = new QHBoxLayout;
//    proxyLayout->addWidget(proxyView);
//    proxyWidget->setLayout(proxyLayout);

//    QVBoxLayout *mainLayout = new QVBoxLayout;

//    QTabWidget *tabWidget = new QTabWidget;
// //    tabWidget->addTab(sourceWidget, "Source");
//    tabWidget->addTab(filterWidget, "Filters");
//    tabWidget->addTab(proxyWidget, "Proxy");
//    mainLayout->addWidget(tabWidget);
//#else
//    sourceGroupBox = new QGroupBox(trUtf8("vollständige Medienübersicht (unsortiert)"));
    proxyGroupBox = new QGroupBox(trUtf8("Medienübersicht"));

//    QHBoxLayout *sourceLayout = new QHBoxLayout;
//    sourceLayout->addWidget(sourceView);
//    sourceGroupBox->setLayout(sourceLayout);

    QGridLayout *proxyLayout = new QGridLayout;
    proxyLayout->addWidget(proxyView, 2, 0, 1, 7);
    proxyLayout->addWidget(filterPatternLabel, 0, 0);
    proxyLayout->addWidget(filterPatternLineEdit, 0, 1, 1, 3);
    proxyLayout->addWidget(filterSyntaxLabel, 1, 0);
    proxyLayout->addWidget(filterSyntaxComboBox, 1, 1, 1, 2);
    proxyLayout->addWidget(filterColumnLabel, 0, 4);
    proxyLayout->addWidget(filterColumnComboBox, 0, 5, 1, 2);
    proxyLayout->addWidget(filterCaseSensitivityCheckBox, 1, 4, 1, 2);
    proxyLayout->addWidget(addItemBtn,3,0);
    proxyLayout->addWidget(delItemBtn,3,1);
    proxyGroupBox->setLayout(proxyLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;              //*

//    mainLayout->addWidget(sourceGroupBox);
    mainLayout->addWidget(proxyGroupBox);                   //*
//#endif

    setLayout(mainLayout);                                  //*

    resize(350, 300);                                       //*

    proxyView->sortByColumn(1, Qt::AscendingOrder);
    filterColumnComboBox->setCurrentIndex(1);

    filterPatternLineEdit->setText("");
    filterCaseSensitivityCheckBox->setChecked(true);
}


void MediaListmodelWidget::setSourceModel(QAbstractItemModel *model)
{
    proxyModel->setSourceModel(model);
//*   sourceView->setModel(model);

    connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(headerDataChanged(Qt::Orientation,int,int)));
    refreshFilterColumnComboBox();
}

void MediaListmodelWidget::filterRegExpChanged()
{
    QRegExp::PatternSyntax syntax =
            QRegExp::PatternSyntax(filterSyntaxComboBox->itemData(
                    filterSyntaxComboBox->currentIndex()).toInt());
    Qt::CaseSensitivity caseSensitivity =
            filterCaseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive
                                                       : Qt::CaseInsensitive;

    QRegExp regExp(filterPatternLineEdit->text(), caseSensitivity, syntax);
    proxyModel->setFilterRegExp(regExp);
}

void MediaListmodelWidget::filterColumnChanged()
{
    proxyModel->setFilterKeyColumn(filterColumnComboBox->currentIndex());
}

void MediaListmodelWidget::sortChanged()
{
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
}

void MediaListmodelWidget::addItem()
{
    qDebug() << "Füge neuen Medieneintrag hinzu";  //*
    proxyModel->insertRow(0, proxyView->currentIndex().parent());
}

void MediaListmodelWidget::delItem()
{
    qDebug() << "Entferne Medieneintrag:" << proxyView->currentIndex();  //*
    proxyModel->removeRow(proxyView->currentIndex().row(), proxyView->currentIndex().parent());
}

void MediaListmodelWidget::headerDataChanged( Qt::Orientation orientation, int first, int last )
{
    if (orientation == Qt::Horizontal) {
        refreshFilterColumnComboBox();
   }
}

void MediaListmodelWidget::refreshFilterColumnComboBox()
{
    filterColumnComboBox->clear();
//    qDebug() << "Spaltenbeschriftung(en) wurde(n) geändert.";
    for (int i=0; i < proxyModel->columnCount(); i++) {
//        qDebug() << "Spaltenbeschriftung(en) wurde(n) geändert:" << i << ", " << (proxyModel->headerData(i, Qt::Horizontal)).toString();
        filterColumnComboBox->addItem((proxyModel->headerData(i, Qt::Horizontal)).toString()); //* Achtung: Nicht internationalisierbarer Text (trUtf8() funktioniert nicht)
    }
}
