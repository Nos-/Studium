/** \file Materialverwaltung.c \brief Diese Datei enthält allgemeine Funktionen der Materialverwaltung.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 */

// Includes - auf die Reihenfolge kommts an!
# include <stdio.h>
# include <string.h>

# include "Projekt.h"
# include "List.h"
# include "Materialverwaltung.h"
# include "Frontend.h"

// GLOBALE DEKLARATIONEN

// UNTERPROGRAMME

/// Artikel aus übergebener Datei einlesen und in Liste sortiert einfügen.
/**
 * Gibt #FAIL zurrück, falls ein oder mehr Datensätze nicht richtig gelesen werden konnte, andernfalls #OK.
 */
int loadFromFile(char* filename, tList* pList) {
	int r=0, result=OK, count=0;
	FILE * pFile;
	char buffer[300], meldung[100], *sPtr = "", *sDelim="\t";
	tData* pData;						// Speicherplatz für neuen Eintrag besorgen

	sprintf(meldung, "Lese Artikel aus Datei '%s' ein... (Dies kann einen Moment dauern) \n", filename); puts(meldung);
	DEBUG_STR(meldung)

	pFile = fopen(filename , "rt");
	if (pFile == NULL) {
		result = FAIL;
		sprintf(meldung, "Fehler beim Öffnen der Datei '%s' !", filename); perror (meldung);
		DEBUG_STR(meldung)
		exit (1);	/// \error 1: Die Artikeldatei kann nicht zum Einlesen geöffnet werden.
	}
	else {
		fgets(buffer, 300 , pFile);		// Kopfzeile wird außer fürs Logfile vorerst ignoriert
		sprintf(meldung, "Kopfzeile der Datei (sollte Tab-getrennte Spaltenüberschriften enthalten): %s",buffer);	// Kopfzeile ins Logfile schreiben
		DEBUG_STR(meldung)
		while ( ! feof (pFile) )
		{
			count++;
			pData=malloc(sizeof(tData));// Speicherplatz für neuen Eintrag besorgen

			// Zeile(=Datensatz) einlesen
			if ( fgets(buffer, 300 , pFile) == NULL ) break;
			pData->lArtNr		= atol(strtok_r(buffer,sDelim, &sPtr));
			strncpy(pData->cArtBez, strtok_r(NULL,sDelim, &sPtr), 30);	pData->cArtBez[30]=0;// Termin. 0, für alle Fälle
			pData->Lagerbestand = atof(strtok_r(NULL,sDelim, &sPtr));
			
			// fuege neues Listenelement sortiert ein
			r = addItemToList(pList, pData, &cmpArtikel);
			if (r == OK){
				sprintf(meldung, "%d", count); printf(".");
				DEBUG_STR(meldung)
			} else {
				result = FAIL;
				sprintf(meldung, "Fehler beim Hinzufügen des Artikels Nr.: %d in die Liste!\n", count); perror (meldung);
				DEBUG_STR(meldung)
			}
		}
		fclose (pFile);
	}

	sprintf(meldung, "Es wurden %d Artikel eingelesen.\n\n", count-1); puts(meldung);
	DEBUG_STR(meldung)

	return result;
}

/// Artikel-Datensätze in übergebene Datei speichern.
/**
 * Gibt #FAIL zurrück, falls ein oder mehrere Datensätze nicht richtig gelesen werden konnte, andernfalls #OK.
 */
int saveToFile(char* filename, tList* pList) {
	int result=OK, count=0;
	FILE * pFile;
	char buffer[300], meldung[100];
	tData* pData = getFirst(pList);

	sprintf(meldung, "Speichere Artikel in der Datei '%s' ... (Dies kann einen Moment dauern) \n", filename); puts(meldung);
	DEBUG_STR(meldung)

	pFile = fopen(filename , "wt");
	if (pFile == NULL) {
		result = FAIL;
		sprintf(meldung, "Fehler beim Öffnen der Datei '%s' !", filename); perror (meldung);
		DEBUG_STR(meldung)
		exit (2);	/// \error 2: Die Artikeldatei kann nicht zum Schreiben geöffnet werden.
	}
	else {
		// Kopfzeile in Datei speichern
		sprintf(buffer, "ArtikelNr\tArtikelBez\tLagerbestand\n");	// Datei-Kopfzeile (wird später nicht mit eingelesen)
		sprintf(meldung, "Datei-Kopfzeile (enthält die Spaltenüberschriften mit Tabs getrennt): %s", buffer);
		DEBUG_STR(meldung)
		if ( fputs(buffer, pFile) == EOF ) {
			result = FAIL;
			sprintf(meldung, "Fehler beim Abspeichern der Spaltenüberschriften!"); perror (meldung);
			DEBUG_STR(meldung)				
		}
		
		// Liste Artikelweise abspeichern		
		while ( pData )
		{
			count++;

			// Je 1 Datensatz als 1 Textzeile abspeichern
			sprintf(buffer, "%ld\t%s\t%f\n", pData->lArtNr, pData->cArtBez, pData->Lagerbestand);
			if ( fputs(buffer, pFile) == EOF ) {
				result = FAIL;
				sprintf(meldung, "Fehler beim Abspeichern des Artikels Nr. %d !", count); perror (meldung);
				DEBUG_STR(meldung)				
			} else {
				sprintf(meldung, "%d", count); printf(".");
				DEBUG_STR(meldung)
			}
			pData = getNext(pList);

		}

		fclose (pFile);
	}

	sprintf(meldung, "Es wurden %d Artikel gespeichert.\n\n", count); puts(meldung);
	DEBUG_STR(meldung)

	return result;
}
