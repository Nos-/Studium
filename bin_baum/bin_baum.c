/** \file bin_baum.c Diese Datei Beschäftigt sich mit Binären Bäumen.
  * 
  * \author Nos <Nos-@github.com>
  * \version 0.1
  */

# include <stdio.h>
# include <stdlib.h>


/// Typdeklaration eines binären Wurzelbaumes
/**
  * Diese rekursive Datenstruktur dient der Strukturierung von Daten mittels Pointern. Sie soll später zur transparenten Datenspeicherung dienen, ohne das es erheblich wäre, wie diese Daten intern verarbeitet werden.
  * \bug Fehler in der Deklaration suchen und beheben.
  */
typedef struct tbinBaum {
   int * Wert = 0;			///< Nutzdaten ("Knoten"): Pointer auf eine Integer- Zahl (welche mit einem NULL-Pointer initialisiert wird)
   tbinBaum * LinkerSohn  = NULL;	///< Pointer auf linken Teilbaum
   tbinBaum * RechterSohn = NULL;	///< Pointer auf rechten Teilbaum
} tBinBaum;


/// Ein Element mit einem bestimmten Wert (im Baum) suchen und einen Pointer, der darauf zeigt, zurückgeben.
/**
  * \param BinBaum	Der zu durchsuchende binäre (Teil-)Baum
  * \param Suchausdruck	Der zu suchende Ausdruck
  * \return		Pointer auf das gesuchte Element; bei Misserfolg Nullpointer
  */
tBinBaum * ElemSuchen(tBinBaum * BinBaum, char * Suchausdruck[])
{
  if (BinBaum->Wert == Suchausdruck) {	// Suchausdr. gefunden
    return (BinBaum);
  }
  if (BinBaum->Wert < Suchausdruck) {	// Weitersuchen im linken Teilbaum
    if (BinBaum->LinkerSohn != NULL) {
      return(ElemSuchen(BinBaum->LinkerSohn, Suchausdruck));
    } else {
      return(NULL);	// Suchausdr. nicht gefunden
    }
  }
  if (BinBaum->Wert > Suchausdruck) {	// Weitersuchen im rechten Teilbaum
    if (BinBaum->RechterSohn != NULL) {
      return(ElemSuchen(BinBaum->RechterSohn, Suchausdruck));
    } else {
      return(NULL);	// Suchausdr. nicht gefunden
    }
  }
}

/// Fügt (dem binärem Baum) den übergebenen Wert hinzu, falls noch nicht enthalten, und gibt einen Pointer darauf zurrück.
/**
  * Das hinzufügen erfolgt intern automatisch als neues "Blatt" am, vom Wert her ähnlichsten, "Knoten" des Baumes. \warning Unter Umständen kann hierduch ein unbalancierter, also unausgewogener, und somit ungünstiger Baum entstehen, was den Vorteil eines binären Baumes etwa im Vergleich zu einer Liste reduzieren bis aufheben würde.
  *
  * \param BinBaum	Der binäre (Teil-)Baum, der erweitert werden soll
  * \param Wert		Der anzuhängende Wert
  * \return		Pointer auf das, ggf. neu angelegte, Element mit dem gewünschten Wert
  */
tBinBaum * ElemHinzufuegen(tBinBaum * BinBaum, int Wert)
{
   if (BinBaum->Wert == Wert) {	// Suchausdr. gefunden, Anlegen überflüssig
     return (BinBaum);
  }
  if (BinBaum->Wert < Wert) {	// Weitersuchen im linken Teilbaum
    if (BinBaum->LinkerSohn == NULL) {
      BinBaum->LinkerSohn = malloc(sizeof(tBinBaum));	// Hinzuzufügendes Element als neues Blatt anlegen
      return(BinBaum->LinkerSohn);
    } else {
      ElemHinzufuegen(BinBaum->LinkerSohn, Wert);
    }
  }
  if (BinBaum->Wert > Wert) {	// Weitersuchen im rechten Teilbaum
    if (BinBaum->RechterSohn == NULL) {
      BinBaum->LinkerSohn = malloc(sizeof(tBinBaum));	// Hinzuzufügendes Element als neues Blatt anlegen
      return(BinBaum->RechterSohn);
    } else {
      ElemHinzufuegen(BinBaum->RechterSohn, Wert);
    }
  }
  
}

/// Den übergebenen Wert (aus dem Baum) entfernen und diesen neuaufbauen.
tBinBaum * ElemEntfernen(tBinBaum * BinBaum, int Wert)
{
	/// \todo Funktionalität implementieren...
}

/// Den übergebenen Baum neu ausbalancieren. (Hauptsächlich für die interne Verwendung)
tBinBaum * BaumNeuAusbalancieren(tBinBaum * BinBaum)
{
	/// \todo Funktionalität implementieren...
}

int main ()
{
  
  return(0);
}
