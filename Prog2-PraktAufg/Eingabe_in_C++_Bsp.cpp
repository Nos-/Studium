/** Diese Programm dient dem Ausprobieren von cin, cout, und cin.getline() sowie der Funktionsüberladung für die Weiterverarbeitung der Daten.
 * Um keinen Bufferoverflow oder Fehlfunktionen des Programmes zu riskieren, sollte cin.get(Char[], Zeichenanzahl) oder cin.getline(Char, Zeichenanzahl, Trennzeichen) verwendet und der Eingabetext ins gewünschte Zielformat konvertiert werden!
 * Vorsicht beim Mischen der verschiedenen Eingabefunktionen.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

// Variante mit Integer und Rest
// int divide(int& x, int& y, int & Rest) {
int divide(int x, int y, int & Rest) {
	Rest = x % y;
	return (x / y);
}

// Variante mit Double und ohne Rest
double divide(int x, int y) {
	return ((double)x / (double)y);
}


int main() {
	int Ganzzahl, div1, div2, rest, quotient_Int;
	double gebrZahl, quotient_Double;
	char Zeichen;
	char Zeichenkette[10];

	//~ cout << "Bitte geben sie eine Ganzzahl ein:";
	//~ cin >> Ganzzahl;										// Programm überspringt komischerweise die weiteren Eingaben, bei Texteingabe anstatt der Eingabe einer Zahl.
	//~ cout << "Bitte geben sie eine Zahl mit Nachkommastellen ein:";
	//~ cin >> gebrZahl;
	//~ cout << "Bitte geben sie einen Buchstaben, Sonderzeichen o.ä. ein:";
	//~ cin >> Zeichen;
	//~ cout << "Bitte geben sie ein Wort ein:";
	//~ cin >> Zeichenkette;									// Vorsicht Bufferoverflowrisiko! Außerdem wird nur bis zum ersten Whitespace verarbeitet.
//~ 
	//~ cout << "Ihre Eingaben: " << endl;
	//~ cout << '(' << Ganzzahl << ')' << endl;
	//~ cout << '(' << gebrZahl << ')' << endl;
	//~ cout << '(' << Zeichen << ')' << endl;
	//~ cout << '(' << Zeichenkette << ')' << endl;	
	//~ cout << "Drücke ggf. eine Taste um fortzufahren..." << endl;
	//~ cin.getline(Zeichenkette, 10);							// Tastaturpuffer leeren
//~ 
	//~ cout << "Weitere Zeichenkette per cin.getline():";
	//~ cin.getline(Zeichenkette, 10);
	//~ cout << '(' << Zeichenkette<< ')' <<endl;
//~ 
	//~ cout << "Weitere Zeichenkette per cin.get():";
	//~ cin.get(Zeichenkette, 10);								// Bis zu 10 Zeichen von Stdin einlesen (Weitere Zeichen werden ignoriert). Es spielt keine Rolle ob Leerzeichen enthalten sind, die ersten 10 Zeichen werden auf jeden Fall verarbeitet. Allerdings bleibt der Zeilenumbruch (Enter) im Tastaturpuffer und kann die nächste Abfrage stören.
	//~ cout << '(' << Zeichenkette<< ')' <<endl;		
	//~ cout << "Drücke ggf. eine Taste um fortzufahren..." << endl;
	//~ cin.getline(Zeichenkette, 10);							// Tastaturpuffer leeren

	cout << "Und nun bitte Zwei Zahlen getrennt duch ein Divisionszeichen (/):";
	cin.getline(Zeichenkette, 10, '/');
	div1 = atoi(Zeichenkette);
	cout << "Die aufgesplittete Zeichenkette: (" << Zeichenkette<< ")/";
	cin.getline(Zeichenkette, 10);
	div2 = atoi(Zeichenkette);
	cout << '(' << Zeichenkette<< ')' <<endl;		

//	quotient_Int = divide(10,3,rest); 
	quotient_Int = divide(div1, div2, rest);
	cout <<div1<<"/"<<div2<<"="<<quotient_Int<<" Rest="<<rest<<endl;
	quotient_Double = divide(div1, div2);
	cout <<div1<<"/"<<div2<<"="<<quotient_Double<<endl;
		
	return 0;
}
