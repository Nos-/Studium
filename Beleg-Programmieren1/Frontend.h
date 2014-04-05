/** \file Frontend.h \brief Diese Datei enthält das Frontend-Headerfile der Materialverwaltung.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 */

#ifndef __FILE_FRONTEND_H
#define __FILE_FRONTEND_H

// extern typedef tList;						//* Funktionierte nicht

void showHeader(char text[]);
int listDs(tList* pList);
int cmpArtikel (void*pItList,void*pItNew);
int cmpArtikelNr (void*pItList,void*pItNew);
int cmpArtikelBez (void*pItList,void*pItNew);
int searchItem (tList* pList);
int inputNewDs(tList* pList);
int deleteDs(tList* pList);
int materialManagement(tList* pList);
void showHelp();
int main (int argc, char* argv[]);

int sortKey;

#endif	// __FILE_FRONTEND_H
