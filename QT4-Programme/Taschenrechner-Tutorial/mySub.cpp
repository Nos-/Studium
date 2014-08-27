#include "mySub.h"
#include "Taschenrechner.h"
 
/// Konstruktor der mySub-Funktion, welcher mySub mit der Taschenrechner-Hauptklasse verbindet
mySub::mySub(Taschenrechner *TRechner):myTaschenrechner(TRechner){
}

mySub::~mySub(){
}

/// Subtrahiert A und B. Das Ergebnis wird in C geschrieben.
void mySub::subAB(){
	double a, b;
	a = (myTaschenrechner -> InputA_2 -> text()).toDouble();
	b = (myTaschenrechner -> InputB_2 -> text()).toDouble();
	myTaschenrechner -> ResultC_2 -> setText(QString("%1").arg(a-b,0,'f',4));	
}
