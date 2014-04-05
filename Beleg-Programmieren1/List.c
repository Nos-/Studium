/** \file List.c \brief Diese Datei enthält das Listenmodul der Materialverwaltung.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 *
 * Es wird versucht die Liste nach außen hin zu kapseln, so das sich von außen her nur um die Nutzdaten gekümmert werden braucht. Auf die Liste sollte deshalb von außerhalb nur mit den hier bereitgestellten Funktionen und möglichst nicht direkt zugegriffen werden.
 */

// Includes - auf die Reihenfolge kommts an!
# include <stdio.h>
# include <stdlib.h>

# include "Projekt.h"
# include "Materialverwaltung.h"
# include "List.h"
# include "Frontend.h"

// GLOBALE DEKLARATIONEN


// UNTERPROGRAMME

/// Erzeugt eine leere Liste
/**
 * Es wird ein Pointer auf die erzeugte Liste zurückgegeben. Im Fehlerfall ist dies ein Nullpointer.
 */
tList * createList(void) {
	// Liste erstellen und initialisieren
	tList * pList = NULL;
	pList = malloc(sizeof(tList));		// Liste auf dem Heap (!) anlegen, damit sie zurückgegeben werden kann
	if (pList) {
		pList->pHead=NULL;
		pList->pTail=NULL;
		pList->pCurrent=NULL;
	} else {
		perror("Fehler bei der Erstellung der Liste!");
	}
	
	return(pList);
}

/// Löscht die übergebene Liste samt Inhalt
int deleteList(tList* pList) {
	for (getFirst(pList); pList->pCurrent; removeItem(pList));// alle Listenelemente löschen
	free(pList);						// Die Liste selbst entfernen
	return OK;
}

/// Fügt ein neues Listenelement (samt übergebenen Datensatz) hinter dem Aktuellem ein und macht dieses Listenelement zum Aktuellen.
/**
 * Im Zweifelsfall wird das neue Listenelement einfach am Listenende angehangen
 */
int insertBehind (tList* pList, void *pItemIns) {
	if (pList->pCurrent) {				// Gibt es bereits andere Elemente in der Liste?

		// Falls ja, erstelle ein Connectorelement und Initialisiere es
		tCnct* pConnectorItem; 			// Listenelement auf dem Heap (!) anlegen, damit es zurückgegeben werden kann
		pConnectorItem = malloc(sizeof(tCnct));
		if (! pList) {
			perror("Fehler beim Einfügen eines neuen Listenelementes hinter dem Aktuellen!");
			return(FAIL);
		}
		pConnectorItem->pData=((tData*)pItemIns);// Nutzdaten an neues Listenelement anhängen

		// neues Element eingliedern (Pointer anpassen)
		pConnectorItem->pPrev = pList->pCurrent;
		pConnectorItem->pNext = pList->pCurrent->pNext;
		pList->pCurrent->pNext = pConnectorItem;
		if (pConnectorItem->pNext != NULL) {
			pConnectorItem->pNext->pPrev = pConnectorItem;
		} else {
			pList->pTail = pConnectorItem;
		}

		pList->pCurrent = pConnectorItem;// Neues Element wird aktuelles Element
	} else {
		insertTail(pList, pItemIns);	// Im Zweifel das Neue Element am Listenende anhängen
	}

	return OK;
}

/// Fügt ein neues Listenelement (samt übergebenen Datensatz) vor dem Aktuellem ein und macht dieses Listenelement zum Aktuellen.
/**
 * Im Zweifelsfall wird das neue Listenelement einfach am Listenanfang eingefügt
 */
int    insertBefore  (tList* pList, void *pItemIns) {
	if (pList->pCurrent) {				// Gibt es bereits andere Elemente in der Liste?

		// Falls ja, erstelle ein Connectorelement und Initialisiere es
		tCnct* pConnectorItem; 			// Listenelement auf dem Heap (!) anlegen, damit es zurückgegeben werden kann
		pConnectorItem = malloc(sizeof(tCnct));
		if (! pList) {
			perror("Fehler beim Einfügen eines neuen Listenelementes vor dem Aktuellen!");
			return(FAIL);
		}

		pConnectorItem->pData=((tData*)pItemIns);// Nutzdaten an neues Listenelement anhängen

		// neues Element eingliedern (Pointer anpassen)
		pConnectorItem->pNext = pList->pCurrent;
		pConnectorItem->pPrev = pList->pCurrent->pPrev;
		pList->pCurrent->pPrev = pConnectorItem;
		if (pConnectorItem->pPrev != NULL) {
			pConnectorItem->pPrev->pNext = pConnectorItem;
		} else {
			pList->pHead=pConnectorItem;
		}

		pList->pCurrent=pConnectorItem;	// Neues Element wird aktuelles Element
	} else {
		insertHead(pList, pItemIns);	// Im Zweifel das Neue Element am Listenanfang einfügen
	}
	
	return OK;
}

/// Fügt ein neues Listenelement (samt übergebenen Datensatz) am Listenanfang ein und macht dieses Listenelement zum Aktuellen.
int insertHead (tList* pList, void *pItemIns) {

	// Connectorelement erstellen und Initialisieren
	tCnct* pConnectorItem; 				// Listenelement auf dem Heap (!) anlegen, damit es zurückgegeben werden kann
	pConnectorItem = malloc(sizeof(tCnct));
	if (! pList) {
		perror("Fehler beim Einfügen eines neuen Listenelementes an den Listenanfang!");
		return(FAIL);
	}
	pConnectorItem->pPrev=NULL;			// Das erste Element hat keinen Vorgänger

	pConnectorItem->pData=((tData*)pItemIns);// Nutzdaten an neues Listenelement anhängen

	// neues Element eingliedern (Pointer anpassen)
	pConnectorItem->pNext = pList->pHead;
	pList->pHead = pConnectorItem;
	pList->pCurrent = pConnectorItem;	// Neues Element wird aktuelles Element
	if (pConnectorItem->pNext != NULL) {// Wenn es bereits ein Folgeelement in der Liste gibt, dann trage das neue Element als seinen Vorgänger ein.
		pConnectorItem->pNext->pPrev = pConnectorItem;
	}	else {							// Ansonsten ist das neue Element auch das Letzte und bedarf einer Anpassung des Tail-Pointers der Liste
		pList->pTail = pConnectorItem;
	}
	return OK;
}

/// Fügt ein neues Listenelement (samt übergebenen Datensatz) am Listenende ein und macht dieses Listenelement zum Aktuellen.
int    insertTail    (tList* pList, void *pItemIns) {

	// Connectorelement erstellen und Initialisieren
	tCnct* pConnectorItem; 				// Listenelement auf dem Heap (!) anlegen, damit es zurückgegeben werden kann
	pConnectorItem = malloc(sizeof(tCnct));
	if (! pList) {
		perror("Fehler beim Einfügen eines neuen Listenelementes an das Listenende!");
		return(FAIL);
	}
	pConnectorItem->pNext=NULL;			// Das letzte Element hat keinen Nachfolger
	
	pConnectorItem->pData=((tData*)pItemIns);// Nutzdaten an neues Listenelement anhängen

	// neues Element eingliedern (Pointer anpassen)
	pConnectorItem->pPrev = pList->pTail;
	pList->pTail = pConnectorItem;
	pList->pCurrent = pConnectorItem;	// Neues Element wird aktuelles Element
	if (pConnectorItem->pPrev != NULL) {// Wenn es bereits ein Folgeelement in der Liste gibt, dann trage das neue Element als seinen Vorgänger ein.
		pConnectorItem->pPrev->pNext = pConnectorItem;
	}	else {							// Ansonsten ist das neue Element auch das Erste und bedarf einer Anpassung des Head-Pointers der Liste
		pList->pHead = pConnectorItem;
	}
	return OK;
}

/// Fügt ein neues Listenelement (samt übergebenen Datensatz) an passender Stelle ein und macht dieses Listenelement zum Aktuellen.
/**
 * An welcher Stelle das übergebene Element eingefügt wird, wird von der im 3. Param. übergebenen (Vergleichs-)Funktion gesteuert.
 * Durch die Verwendung unterschiedlicher Vergleichsfunktionen sind somit verschiedene Sortierkriterien etwa eine Sortierungen nach unterschiedlichen Feldern möglich
 */
int addItemToList (tList* pList,
                     void * pItem,
                     int(*fcmp)(void*pItList,void*pItNew)) {

	// Sonderfallbehandlung (Leere Liste etc.)
	if (getSelected(pList) == NULL) {
		if (getFirst(pList) == NULL) {
			insertHead(pList, pItem);
			return OK;
		}
	}

	// im vorderen Listenbereich nach passender Position suchen
	if (fcmp(pList, pItem) > 0) {
		while (fcmp(pList, pItem) > 0) {
			if (getPrev(pList)==NULL) {	// Im Zweifelsfall am Listenanfang einfügen
				insertHead(pList, pItem);
				return OK;
			}
		}
		insertBehind(pList, pItem);
	} else {

		// im hintern Listenbereich nach passender Position suchen
		while (fcmp(pList, pItem) < 0) {
			if (getNext(pList)==NULL) {	// Im Zweifelsfall am Listenende einfügen
				insertTail(pList, pItem);
				return OK;
			}
		}
		insertBefore(pList, pItem);
	}			
	
	return OK;
}

/// Löscht das aktuelle Listenelement samt anhängendem Datenelement.
/**
 * Achtung! Weist ggf. NULL-Pointer zu, falls nötig.
 */
void   removeItem    (tList* pList) {
	tCnct* pOldItem = pList->pCurrent;	// Zu löschendes Element merken

	if (pList->pCurrent) { 				// gibt es überhaupt ein aktuelles Element in der Liste?

		// Element ausgliedern (Pointer anpassen)
		if (pList->pCurrent->pNext) {	// Nachfolger existent?
			pList->pCurrent->pNext->pPrev = pList->pCurrent->pPrev;
		} else {
			if (pList->pCurrent->pPrev) pList->pCurrent->pPrev->pNext = NULL;
			pList->pTail = pList->pCurrent->pPrev;
		}
		if (pList->pCurrent->pPrev) {	// Vorgänger existent?
			pList->pCurrent->pPrev->pNext = pList->pCurrent->pNext;
		} else {
			if (pList->pCurrent->pNext) pList->pCurrent->pNext->pPrev = NULL;
			pList->pHead = pList->pCurrent->pNext;
		}

		// Nächstes Element wird aktuelles Element
		pList->pCurrent = pList->pCurrent->pNext;	// Achtung! Enth. ggf. Nullpointer., um Listenende anzuzeigen

		// Listenelement samt Nutzdaten löschen
		free(pOldItem->pData);
		free(pOldItem);	
	} else {
//		printf("Fehler: Die Liste ist bereits leer.\n");
	}
}

/// Gibt (einen Pointer auf) den Datensatz des aktuellen Listenelements zurück.
/**
 * Achtung! Gibt NULL-Pointer zurrück, falls die Liste leer ist.
 */
void* getSelected (tList* pList) {
	void* pItemData = NULL;
	if (pList->pCurrent) {
		pItemData = pList->pCurrent->pData;
	}
	return(pItemData);
}

/// gibt (einen Pointer auf) den Datensatz des ersten Listenelements zurück und macht dieses Listenelement zum Aktuellen.
/**
 * Achtung! Gibt NULL-Pointer zurrück, falls die Liste leer ist.
 */
void* getFirst (tList* pList) {
	void* pItemData = NULL;
	if (pList->pHead) {
		pItemData = pList->pHead->pData;
		pList->pCurrent = pList->pHead;	// 1. Listenelement zum Aktuellen machen
	}
	return(pItemData);
}

/// gibt (einen Pointer auf) den Datensatz des letzten Listenelements zurück und macht dieses Listenelement zum Aktuellen.
/**
 * Achtung! Gibt NULL-Pointer zurrück, falls die Liste leer ist.
 */
void* getLast (tList* pList) {
	void* pItemData = NULL;
	if (pList->pTail) {
		pItemData = pList->pTail->pData;
		pList->pCurrent = pList->pTail;	// Letztes Listenelement zum Aktuellen machen
	}
	return(pItemData);
}

/// gibt (einen Pointer auf) den Datensatz des nächsten Listenelements zurück und macht dieses Listenelement zum Aktuellen.
/**
 * Sollte das aktuelle Listenelement schon das letzte der Liste sein (z.B. in einer leeren Liste), wird ein Nullpointer (!) zurückgegeben.
 */
void* getNext (tList* pList) {
	void* pItemData = NULL;
	if (pList->pCurrent) {
		if (pList->pCurrent->pNext) {
			pList->pCurrent = pList->pCurrent->pNext;	// Nachfolgendes Listenelement zum Aktuellen machen
			pItemData = pList->pCurrent->pData;
		}
	}
	return(pItemData);
}

/// gibt (einen Pointer auf) den Datensatz des vorhergehenden Listenelements zurück und macht dieses Listenelement zum Aktuellen.
/**
 * Sollte das aktuelle Listenelement schon das erste der Liste sein, wird ein Nullpointer (!) zurückgegeben.
 */
void* getPrev (tList* pList) {
	void* pItemData = NULL;
	if (pList->pCurrent) {
		if (pList->pCurrent->pPrev) {
			pItemData = pList->pCurrent->pPrev->pData;
			pList->pCurrent = pList->pCurrent->pPrev;	// Vorangehendes Listenelement zum Aktuellen machen
		}
	}
	return(pItemData);
}

/// gibt (einen Pointer auf) den Datensatz eines Listenelements mit einem bestimmten Index (Listenpositionsnr.) zurück und macht dieses Listenelement zum Aktuellen.
/**
 * Sollte kein Listenelement mit dem gewünschten Index (der Nr. des Listenelements) existieren, wird ein Nullpointer (!) zurückgegeben.
 */
void* getIndexed (tList* pList,int Idx) {
	int i;

	void* pItemData = NULL;
	if (Idx > 0) pItemData = getFirst(pList);

	// Suche das Idx. Element, breche ab, falls nicht in der Liste
	for (i=0; i < Idx-1; i++) {
		if (pItemData == NULL) {
			break;						// For-Schleife abbrechen, falls Listenende erreicht
		}
		pItemData = getNext(pList);
	}

	return(pItemData);					// Gebe das entspr. Element (bzw. einen Nullpointer, falls nicht existent) zurrück
};
