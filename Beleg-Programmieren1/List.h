/** \file List.h \brief Diese Datei enthält das vorgegebene Headerfile zum Listenmodul der Materialverwaltung.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 */

/*  bitte in alle Quellfiles eintragen! 
Name:			s. oben
Studiengruppe:	s. oben
MatrNr:			s. oben
*/


#ifndef __FILE_LIST_H
#define __FILE_LIST_H

/* Datenstruktur eines Listenverbindungselementes */
/// Typdeklaration des Connectors (=Listen(verkettungs)element)
/**
 * Er stellt den Datentyp der eigentlichen Listenelemente dar, die untereinander verbunden (=connected) - oder besser: verkettet - sind.
 */
typedef struct tcnct {
	struct	tcnct* pPrev;				///< Zeigt auf das vorherige Element, NULL falls 1. Element
	struct	tcnct* pNext;				///< Zeigt auf das nachfolgende Element, NULL falls letztes Element	
//*	tData*	pData;						///< Zeigt auf die eigentlichen Daten, dem Datensatz des Listenelements
	void*	pData;						///< Zeigt auf die eigentlichen Daten, dem Datensatz des Listenelements
} tCnct;	/* Datentyp fuer Connector */
// typedef struct tcnct tCnct;

/// Typdeklaration der "Doppelt verketteten Liste"
/**
 * *Eine Doppelt verkettete Liste* muss zur Laufzeit dynamisch per `createList()` erzeugt und nach Gebrauch per `deleteList()` wieder gelöscht werden.
 * Sie besteht aus Listenelementen vom Typ `tCnct`, die miteinander verkettet werden. 
 * 
 * Schematische Darstellung:
 * \dot digraph G {
 *	  "Doppelt verkettete Liste" -> "Listenverbinder_1" [taillabel = "Head"]
 *	  "Doppelt verkettete Liste" -> "Listenverbinder_n" [taillabel = "Current"]
 *	  "Doppelt verkettete Liste" -> "Listenverbinder_2" [taillabel = "Tail"]
 *	  "Listenverbinder_1" -> "Listenverbinder_2"
 *	  "Listenverbinder_2" -> "Listenverbinder_1"
 *	  "Listenverbinder_1" -> "Datensatz_1"
 *	  "Listenverbinder_2" -> "Datensatz_2"
 *	  "Listenverbinder_2" -> "..."
 *	  "..." -> "Listenverbinder_2"
 *	  "..." -> "Listenverbinder_n"
 *	  "Listenverbinder_n" -> "..."
 *	  "Listenverbinder_n" -> "Datensatz_n"
 *	} \enddot
 */
typedef struct tlist {
	tCnct*	pHead;						///< Zeigt auf das erste Listenelement
	tCnct*	pTail;						///< Zeigt auf das letzte Listenelement
	tCnct*	pCurrent;					///< Zeigt auf das aktuelle Listenelement
//	*binTree pbintreeIndex; ///< Zeigt auf einen Such-Index, realisiert mittels eines *binären Suchbaumes* für besonders effizienten Zugriff.
//	int*	pChanged;	///< Gibt an, das die Liste bzw. die Datensätze der Listenelemente verändert wurden. Beim nächsten Indexzugriff wird dieser automatisch aktualisiert (d.h. der Index wird neu aufgebaut).
} tList;	/* Datentyp fuer die Liste */
// typedef struct tlist tList;


#define OK 1
#define FAIL 0
/*-------------------------------------------------------------------------*/
/* Prototypen fuer die Funktionen                                          */

/* List.h */
/*------------------------------------------------------------------------*/
/* Datenstruktur eines Listenverbindungselementes                         */

tList * createList(void);                           /* erzeuge leere Liste */
int     deleteList(tList* pList);                   /* loesche leere Liste */

int    insertBehind  (tList* pList, void *pItemIns);/* fuege ein hinter %  */
int    insertBefore  (tList* pList, void *pItemIns);/* fuege ein vor    %  */
int    insertHead    (tList* pList, void *pItemIns);/* fuege vorn ein      */
int    insertTail    (tList* pList, void *pItemIns);/* fuege hinten ein    */
int    addItemToList (tList* pList, 		        /* fuege sortiert ein  */
                     void * pItem,
                     int(*fcmp)(void*pItList,void*pItNew));

void   removeItem    (tList* pList);                /* loesche %           */

void* getSelected    (tList* pList);                /* gib aktuellen DS    */
void* getFirst       (tList* pList);                /* gib ersten DS       */
void* getLast        (tList* pList);                /* gib letzten DS      */
void* getNext        (tList* pList);                /* gib naechsten DS    */
void* getPrev        (tList* pList);                /* gib vorigen DS      */
void* getIndexed     (tList* pList,int Idx);        /* gib DS lt. Index    */

#endif	// __FILE_LIST_H
