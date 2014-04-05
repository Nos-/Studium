/** \file Materialverwaltung.h \brief Diese Datei enthält das Headerfile des Materialverwaltungsmoduls.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 */


#ifndef __FILE_MATVERW_H
#define __FILE_MATVERW_H

# include "List.h"	//*

// extern typedef tList;

int loadFromFile(char* filename, tList* pList);
int saveToFile(char* filename, tList* pList);

/// Typdeklaration der Datensatzstruktur. Sie enthält die eigentlichen Nutzdaten
typedef struct tdata {
	char	cArtBez[255];				// max. 255 Zeichen lang, damit beim Speichern die Feldlänge in ein Byte passt; NOTE: Alternativ Pointer verw. (und an malloc() & Co. denken!) /// Die Artikelbezeichnung
	long	lArtNr;						/// Die Artikelnummer (Ganzzahlig)
	double	Lagerbestand;				/// Menge dieses Gutes (sollte >= Null sein).
} tData;
// typedef struct tdata tData;			//* Überbleibsel von Modularisierungsversuchen, wird vielleicht noch gebraucht


#endif	// __FILE_MATVERW_H
