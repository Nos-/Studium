#include "Taschenrechner.h"
#include "myAdd.h"
#include "mySub.h"

/// Konstruktor der Taschenrechnerklasse
Taschenrechner::Taschenrechner(QMainWindow *parent) : QMainWindow(parent){	
	setupUi(this);

	// Instanzen der Widgets erzeugen. Hierbei wird durch `this` eine Referenz auf die Hauptklasse Taschenrechner übergeben.
	myAdd *addWidget = new myAdd(this);
	mySub *subWidget = new mySub(this);
 
	// Anfangswerte für Eingabefelder setzen
	InputA_1 -> setText("0");
	InputB_1 -> setText("0");
	InputA_2 -> setText("0");
	InputB_2 -> setText("0");
 
	// Signale und Slots verbinden
	connect(Calculate_1, SIGNAL (clicked()), addWidget, SLOT(addAB()));
	connect(Calculate_2, SIGNAL (clicked()), subWidget, SLOT(subAB()));
	connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));	// Man beachte das "qApp-Makro" und den Aufruf der QT-Funktion quit().
	connect(actionAdd, SIGNAL(triggered()), this, SLOT(showAdd()));
	connect(actionSub, SIGNAL(triggered()), this, SLOT(showSub()));
}

/// Destruktor der Taschenrechnerklasse 
Taschenrechner::~Taschenrechner(){
}

/// Zeige Ansicht für Addition
void Taschenrechner::showAdd(){
	stackedWidget -> setCurrentIndex(0);
}

/// Zeige Ansicht für Substraktion
void Taschenrechner::showSub(){
	stackedWidget -> setCurrentIndex(1);
}
