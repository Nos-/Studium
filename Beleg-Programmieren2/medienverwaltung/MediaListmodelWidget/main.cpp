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

void addItem(QAbstractItemModel *model, const QString &mediumId,
             const QString &mediumLabel, const QString &mediumType, const QString &mediumLentTo, const QString &mediumNotes)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), mediumId);
    model->setData(model->index(0, 1), mediumLabel);
    model->setData(model->index(0, 2), mediumType);
    model->setData(model->index(0, 3), mediumLentTo);
    model->setData(model->index(0, 4), mediumNotes);
}

QAbstractItemModel *createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 5, parent);

    model->setHeaderData(0, Qt::Horizontal, QObject::trUtf8("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Bezeichnung"));
    model->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Typ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::trUtf8("ausgeliehen an"));
    model->setHeaderData(4, Qt::Horizontal, QObject::trUtf8("Notizen"));

    addItem(model, "DieMaus_Folge123", "Die Sendung mit der Maus", "Video", "Kleiner blauer Elephant", ";-)");
    addItem(model, "PAddG_Erstausgabe", "Per Anhalter durch die Galaxis", "Buch", "Alien von Nebenan", "Sollte man gelesen haben...");

    return model;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MediaListmodelWidget window;
    window.setSourceModel(createModel(&window));
#if defined(Q_OS_SYMBIAN)
    window.showMaximized();
#else
    window.show();
#endif
    return app.exec();
}
