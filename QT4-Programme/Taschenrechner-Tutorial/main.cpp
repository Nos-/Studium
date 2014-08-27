#include "Taschenrechner.h"
#include <QApplication>

/** QT4-Tutorial eines Taschenrechners nach https://de.wikibooks.org/wiki/Qt_f%C3%BCr_C%2B%2B-Anf%C3%A4nger
 * 
 * Kompilierbefehle:
 * 
 * qmake-qt4 -project
 * qmake-qt4
 * make
 * 
 * Verwendung:
 * 
 * ./Taschenrechner
 */

/// Die Mainfunktion
int main( int argc, char* argv[])
{
        QApplication a(argc, argv);							// QT-Anwendungsobjekt erzeugen und Aufrufparameters des Programms an QT weiterreichen
        Taschenrechner w;									// Ein Objekt der Taschenrechnerklasse (also des Programmfensters) erzeugen
        w.show();											// Taschenrechnerfenster anzeigen
        return a.exec();									// Kontrolle an das zuvor erzeugte QT-Anwendungsobjekt übergeben und nach dessen Beendigung auch das Programm beenden
}
