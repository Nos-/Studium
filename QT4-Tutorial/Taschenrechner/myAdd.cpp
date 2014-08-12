#include "myAdd.h"
#include "Taschenrechner.h"
 
/// Konstruktor der myAdd-Funktion, welcher myAdd mit der Taschenrechner-Hauptklasse verbindet
myAdd::myAdd(Taschenrechner *TRechner):myTaschenrechner(TRechner){
}

myAdd::~myAdd(){
}

/// Addiert A und B. Das Ergebnis wird in C geschrieben.
void myAdd::addAB(){
	double a, b;
	a = (myTaschenrechner -> InputA_1 -> text()).toDouble();
	b = (myTaschenrechner -> InputB_1 -> text()).toDouble();
	myTaschenrechner -> ResultC_1 -> setText(QString("%1").arg(a+b,0,'f',4));	
}
