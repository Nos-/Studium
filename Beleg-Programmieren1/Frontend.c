/** \file Frontend.c \brief Diese Datei enthält das Frontend der Materialverwaltung.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 * 
 * \image Latex Bildschirmfoto-v0_1.eps
 * "Die Materialverwaltung in Aktion"
 */

// Includes - auf die Reihenfolge kommts an!
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "Projekt.h"
# include "Materialverwaltung.h"
# include "List.h"
# include "Frontend.h"

// GLOBALE DEKLARATIONEN

int sortKey;	///< Der Sortierschlüssel (\see cmpArtikel() )

// UNTERPROGRAMME

/// Gibt den Programmkopf (anpassbare Überschrift) auf einem leeren Bildschirm aus
void showHeader(char text[]) {
	int i;
	char header[255];

	// Bildschirm löschen
	CLEAR

	// Überschrift zusammenbauen und ausgeben
	sprintf(header, "Materialverwaltung %s", text);
	puts(header);
	for (i=0; i < strlen(header); i++) putchar('=');
	puts("\n");
}

/// Listet alle in der übergebenen Liste enthaltenen Datensätze auf
int listDs(tList* pList) {
	tData* pData = getFirst(pList);
	long count = 0;

	if (pData != NULL) {
		printf("Nr. \tArtikelNr.     \tArtikelbezeichnung	  \tLagerbestand\n");  
		printf("-------+----------+---------------------------------+------------------\n");  
		while (pData) {
			count++;
			printf("%6ld \t%10ld \t%-28s \t%10.3f\n", count, pData->lArtNr, pData->cArtBez, pData->Lagerbestand);
			pData=getNext(pList);
		}
		printf(  "-------+----------+---------------------------------+------------------\n");  
		printf("Anzahl ausgegebener Datensätze: %ld\n", count);
	}
	printf("\n");
	return count;
}

/// Vergleichsfunktion zum sortierten Einfügen neuer Artikel per AddItemToList(). (Weiterleitungsfunktion)
/**
 * Diese Funktion ist eine Weiterleitung. Sie leitet Aufrufe entsprechend sortKey an eine spezifischere Vergleichsfunktion weiter.
 * 1= cmpArtikelNr(), 2= cmpArtikelBez()
 */
int cmpArtikel (void*pItList,void*pItNew) {
	char meldung[100];

	switch (sortKey) {
		case 1: {
			return (cmpArtikelNr(pItList, pItNew));// nach Art.Nummer sortieren
			break;
		}
		case 2: {
			return (cmpArtikelBez(pItList, pItNew));// nach Art.Bezeichnung sortieren
			break;
		}
		default: {
			sprintf(meldung, "Ungültiger Sortierschlüssel: %d", sortKey);
			perror(meldung);
			DEBUG_STR(meldung)
			exit(3); /// \error 3: Ungültiger Sortierschlüssel
		}
	}
}
//~ typedef int cmp_Artikel (void*pItList,void*pItNew);	//*
//~ cmp_Artikel cmpArtikel	= &cmpArtikelNr;

/// Vergleichsfunktion zum (nach ArtikelNr. sortierten) Einfügen neuer Artikel per AddItemToList().
/**
 * Ähnlich anderer Vergleichsfunktionen, wird -1 (1. Wert ist kleiner als 2.), 0 (beide Werte sind gleich) oder +1 (1. Wert ist größer als 2.) zurückgegeben. 
 */
int cmpArtikelNr (void*pItList,void*pItNew) {
	tData* pData1 = getSelected((tList*)pItList);
	tData* pData2 = ((tData*)pItNew);

	// ArtikelNr. vergleichen
	if ( pData1->lArtNr == pData2->lArtNr ) return  0;
	if ( pData1->lArtNr <  pData2->lArtNr ) return -1;
	if ( pData1->lArtNr >  pData2->lArtNr ) return  1;
}

/// Vergleichsfunktion zum (nach ArtikelBezeichnung. sortierten) Einfügen neuer Artikel per `AddItemToList()`.
/**
 * Ähnlich anderer Vergleichsfunktionen, wird -1 (1. Wert ist kleiner als 2.), 0 (beide Werte sind gleich) oder +1 (1. Wert ist größer als 2.) zurückgegeben. 
 */
int cmpArtikelBez (void*pItList,void*pItNew) {
	tData* pData1 = getSelected((tList*)pItList);
	tData* pData2 = ((tData*)pItNew);

	// ArtikelBezeich. vergleichen
	return( strcmp(pData1->cArtBez, pData2->cArtBez) );
}

/// Per Suchmaske kann die Auflistung aller Artikel-Datensätze entsprechend gefiltert werden.
/**
 * Gibt die Anzahl der zutreffenen Datensätze zurück.
 */
int searchItem (tList* pList) {	
	tData* pData = getFirst(pList);
	long artnr, count = 0;
	double lagerbest;
	char artbez[255], vBuf[128], lagerbest_operator;

	printf("HINWEIS: Je genauer ihre Suchangaben sind, um so präziser kann gesucht werden.\n");
	printf("* Möchten sie hingegen einige Felder nicht mit in die Suche einbeziehen, lassen sie diese einfach frei.\n");
	printf("* Bei der Artikelbezeichnung genügt die Angabe eines Wortbestandteiles um alle Artikel zu finden, die ihn enthalten.\n");
	printf("* Der Lagerbestand kann 'mittels weniger als' (<), 'genau so viel' (=) oder 'mehr als' (>), gefolgt von der entspr. Zahl, angegeben werden.\n");
	printf("* Es wird zwischen Groß- und Kleinschreibung unterschieden.\n");
	printf("\n");
	printf("Artikelnr. (genaue Angabe)              : ");
	fgets(vBuf, 128, stdin); artnr= atol(vBuf);
	printf("Artikelbezeichnung (Teilbegriff genügt)	: ");
	fgets(artbez, 128, stdin);
	artbez[strlen(artbez)-1] = 0;
	printf("Lagerbestand (<,=,> Zahl)               : ");
	fgets(vBuf, 128, stdin);
	lagerbest_operator = vBuf[0];	// Vergleichsoperator ("<", "=", ">") für den Lagerbestand extrahieren
	vBuf[0]=' ';
	lagerbest= atol(vBuf);
	printf("\n");

	if (pData != NULL) {
		printf("Nr. \tArtikelNr.     \tArtikelbezeichnung	  \tLagerbestand\n");  
		printf("-------+----------+---------------------------------+------------------\n");  
		while (pData) {
			count++;
			if (pData->lArtNr == artnr || artnr == 0) {
				if (strstr(pData->cArtBez, artbez) != NULL || strlen(artbez) == 0) {
					if ((lagerbest_operator == '<' && pData->Lagerbestand < lagerbest) || (lagerbest_operator == '=' && pData->Lagerbestand == lagerbest) || (lagerbest_operator == '>' && pData->Lagerbestand > lagerbest) || lagerbest == 0) {
						printf("%6ld \t%10ld \t%-28s \t%10.3f\n", count, pData->lArtNr, pData->cArtBez, pData->Lagerbestand);
					}
				}
			}
			pData=getNext(pList);
		}
		printf(  "-------+----------+---------------------------------+------------------\n");  
		printf("Anzahl durchsuchter Datensätze: %ld\n", count);
	} else {
	  printf("Achtung! Die Liste ist leer.\n");
	}
	printf("\n");
	return count;
}

/// Manuelle Eingabe eines Artikel-Datensatzes mit automatischer Einsortierung in die Liste.
int inputNewDs(tList* pList) {
	char vBuf[30];
	int result;
	tData* pData=malloc(sizeof(tData));	// Speicherplatz für neuen Eintrag besorgen

	printf("ArtikelNr. :");	fgets(vBuf, 30, stdin);
	pData->lArtNr =atol(vBuf);

	printf("Artikelbezeichnung :");	fgets(vBuf, 30, stdin);
	vBuf[strlen(vBuf)-1]=0;				// Zeilenumbruch entf.
	strcpy(pData->cArtBez,vBuf);		// Zuvor eingeg. Eintragstext hier ablegen 

	printf("Lagerbestand :");	fgets(vBuf, 30, stdin);
	pData->Lagerbestand = atof(vBuf);

	result = addItemToList(pList, pData, &cmpArtikel);// fuege neues Listenelement sortiert ein
	if (result == OK){
	  printf("Neues Element hinzugefügt.\n\n");
	} else {
		perror("Fehler beim Hinzufügen des neuen Elementes!\n\n");
	}
	return(result);
}

/// Löschen eines Artikel-Datensatz per Suchmaskenauswahl oder direkt.
int deleteDs(tList* pList) {
	char vBuf[128];
	tData* pData;
	int nr;

	do {
		printf("HINWEIS: Sie können auch das Eingabefeld leer lassen um den Vorgang abzubrechen.\n\n"); 
		printf("EINTRAG-LÖSCHEN-MENÜ:\n");
		printf("Artikel per Listen<Nr.> | [S]uche :"); 
		fgets(vBuf, 7, stdin);
		if (vBuf[0] != 'S') break;
		showHeader("(Löschen > Suchen)");
		searchItem(pList);
	} while (vBuf[0] == 'S');
	
	nr=atoi(vBuf);

	pData = getIndexed(pList, nr);		// zu löschendes Element zum Aktuellen machen
	if (pData != NULL) {
	  printf("Folgendes Listenelement würde gelöscht:\n\n");  
	  printf("Nr. \tArtikelNr.     \tArtikelbezeichnung	  \tLagerbestand\n");  
	  printf("-------+----------+---------------------------------+------------------\n");  
	  printf("%6d \t%10ld \t%-28s \t%10.3f\n", nr, pData->lArtNr, pData->cArtBez, pData->Lagerbestand);
	  printf("\nSind Sie sicher? ([J]a/ [N]ein) :");
	  fgets(vBuf, 3, stdin);
	  if (tolower(vBuf[0]) == 'j') {
		removeItem(pList);				// loesche das aktuelle Element
		return(OK);
	  }
	  puts("");
	} else {
	  printf("Die Liste enthält keinen Eintrag mit dieser Nr.\n\n");
	}
	return(FAIL);
}

/// Verwaltung von Zugängen/ Abgängen per Suchmaskenauswahl oder direkt.
int materialManagement(tList* pList) {
	char vBuf[128];
	tData* pData;
	int nr;
	double menge;

	do {
		printf("ZUGÄNGE/ABGÄNGE-MENÜ:\n");
		printf("Artikel per Listen<Nr.> | [S]uche :"); 
		fgets(vBuf, 7, stdin);
		if (vBuf[0] != 'S') break;
		showHeader("(Zugänge/Abgänge > Suchen)");
		searchItem(pList);
	} while (vBuf[0] == 'S');
	nr=atoi(vBuf);

	pData = getIndexed(pList, nr);		// zu änderndes Element markieren
	if (pData != NULL) {
	  printf("Details zum gewählten Artikel:\n\n");  
	  printf("Nr. \tArtikelNr.     \tArtikelbezeichnung	  \tLagerbestand\n");  
	  printf("-------+----------+---------------------------------+------------------\n");  
	  printf("%6d \t%10ld \t%-28s \t%10.3f\n", nr, pData->lArtNr, pData->cArtBez, pData->Lagerbestand);
	  printf("\nHINWEIS: Sie können den neuen Lagerbestand absolut (z.B. 123.5) oder auch relativ (z.B. +10 oder -10) angeben. Lassen sie das Eingabefeld leer, um den Lagerbestand unverändert zu lassen.\n\n");
	  printf("geänderter Lagerbestand: ");
	  fgets(vBuf, 10, stdin); menge=atof(vBuf);
	  switch (vBuf[0]) {
		  case '+': { pData->Lagerbestand += menge; break;}
		  case '-': {					// Leerlaufprüfung
			  if (pData->Lagerbestand + menge >= 0) pData->Lagerbestand += menge;	// Achtung! Menge ist schon negativ, deshalb +
			  else {
				  printf("Entnahme nicht möglich, da nicht in ausreichender Menge vorrätig!\n");
			  }
			break;
		  }
		  case '\n': { break; }
		  default: pData->Lagerbestand  = menge; break;
	  }
	  printf("Neuer Lagerbestand: %10.3f\n\n", pData->Lagerbestand);
	} else {
	  printf("Fehler! diese Nr. ist nicht vergeben.\n\n");
	}
	return(OK);
}

/// Zeigt die Programmhilfe an.
void showHelp() {
	printf ("\nMaterialverwaltung\n\n");
	printf("Nutzung:	Materialverwaltung [<Artikeldatei.csv>]\n");
	printf("        	Materialverwaltung  <Artikeldatei.csv>  [<Sortierschlüssel>]\n\n");
	printf("        	Der Sortierschlüssel sorgt für eine Sortierung nach:\n");
	printf("        	1= aufsteigenden Artikelnr. (Standard)\n");
	printf("        	2= aufsteigenden ArtikelBezeichnungen\n\n");
	printf("Author: N. Schwirz <s70341@htw-dresden.de>\n\n");
}


// HAUPTPROGRAMM	(Keine zweite Main-Funktion im Projekt dank Preproz.makro; Dies ist die eigentlich Mainfunktion)
#define __MAIN
/// Die Main-Funktion des Projektes. Sie implementiert das Frontend und die Programmlogik welche sie mit den Daten des Listenmoduls verknüpft.
int main (int argc, char* argv[]) {
	DEBUG_INIT

	char z, vBuf[128];
	tList* myList;

	// Prüfung der Aufrufparameter
	if (argc > 3) {
	  printf("Fehler! Ungültige Aufrufparameter.\n");
	  showHelp();
	  exit(FAIL);
	}
	if ((argc == 2) && (strcmp(argv[1], "-?") == 0)) {
	  showHelp();
	  exit(OK);
	}
	char fileName[] = "Artikel.csv";
	  if (argc > 1) {
	  strcpy(fileName, argv[1]);
	}
	sortKey = 1;
	if (argc > 2) {
	  sortKey = atoi(argv[2]);			// Sortierschlüssel für Liste
	}
	
	myList = createList();				// erzeuge leere Liste
	showHeader("(Programmstart)");

	printf("WILLKOMMEN\n");
	printf("==========\n\n");
	printf("Diese simple Materialverwaltung dient der Verwaltung von Artikeln sowie deren Vorrat im Lager.\n");
	printf("Bedient wird sie durch die Eingabe von Menükürzeln. Diese müssen, wie sämtliche Eingaben, mit der Entertaste bestätigt werden.\n");
	printf("In manchen Menüs gibt es zusätzliche Tipps in Form von Hinweisen, wie dem folgendem:\n\n");
	printf("HINWEIS: Geben sie den, in eckigen Klammern stehenden Buchstaben ein, um zum jeweiligen Menüpunkt zu gelangen.\n");
	printf("Die Programm[H]ilfe erreichen sie später z.B. per: [H] oder [?]. (Entertaste nicht vergessen!)\n\n");
	printf("Als nächstes wird nun die Materialdatei, die sämtliche Lagerartikel enthält, eingelesen...\n");
	fgets(vBuf, 3, stdin);
	
	showHeader("(Materialdatei einlesen)");
	loadFromFile(fileName, myList);		// Lese Datei ein
	
	// Mainloop, das ganze Programm läuft quasi in einer großen Schleife...
	do {
	  printf("HAUPTMENÜ:\n");
	  printf("Artikel [N]eu eingeben | [A]uflisten | [S]uchen | [L]öschen | [Z]ugänge/Abgänge verwalten | Programm [B]eenden | Noch Fragen[?] :");
	  fgets(vBuf, 3, stdin); z=toupper(vBuf[0]);
	showHeader("(Hauptmenü)");
	  switch (z) {
	    case 'N': {						// Daten neu eingeben
		showHeader("(Neuen Artikel anlegen)");
		if (inputNewDs(myList) != OK) {
			perror("Fehler! Der neue Eintrag konnte der Liste nicht hinzugefügt werden. Versuchen Sie es noch einmal.\n\n");
		}
		break;
	    }
	  case 'A': {						// Auflisten
		showHeader("(Lagerartikel auflisten)");
		if (listDs(myList) == 0) printf("Die Liste ist leer.\n\n");
		break;
	  }
	  case 'S': {						// Suchen
		showHeader("(Suchen)");
		searchItem(myList);
		break;
	  }
	    case 'L': {						// Löschen
		showHeader("(Artikel löschen)");
		if (deleteDs(myList) == OK) {
			printf("Eintrag gelöscht.\n\n");
		}
		break;
	    }
	    case 'B': {						// Beenden
		showHeader("(Programm beenden > Artikeldatei speichern)");
		saveToFile(fileName, myList);	// Speichere Artikel in Datei
		printf("Programm wird beendet\n\n");
		deleteList(myList);
		DEBUG_STR("Programm wird beendet.")
		return(0);
		break;
	  }
	  case 'Z': {						// Zugänge/ Abgänge
		showHeader("(Zugänge/Abgänge verwalten)");
		materialManagement(myList);
		break;
	  }
	  case '?':
	  case 'H': {						// Programmhilfe anzeigen
		showHeader("(Hilfe)");
		showHelp();
		printf("\n");
		break;
	  }
	  default: {						// andere (=unzulässige) Eingaben
		showHeader("(Hauptmenü)");
		printf("Unzulässige Eingabe. Versuche es erneut!\n\n");
		break;
	  }
	  }
	} while (1);
	// wird nie aufgeführt, siehe obiges return().
};
