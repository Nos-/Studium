/// @file binaere_suche.c Beispiel einer rekursiven Implementierung einer Binären Suche

# include <stdio.h>
# include <stdlib.h>


int zeige_arrayelemente (int array[], int anz);
int bin_suche(int val_array[], int element_anz, int suchausdruck);

int main()
{
	int	werte_array[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int 	anz=16;		// Anzahl der zu durchsuchenden Arrayelemente
	int 	sa =10;		// Suchausdruck
	int	fundstelle=0;	// Nr. des Arrayelements, mit dem gesuchten Suchausdr.
	char vBuf[128];

	printf("Beispiel einer Suche basierend auf einem 'binärem Baum' in einem sortierten Array.\n");
	printf("Zu durchsuchendes Array: ");
	zeige_arrayelemente(werte_array, anz);
	printf("\nWonach soll gesucht werden? ");
	fgets(vBuf, 128, stdin);
	sa = atoi(vBuf);

	fundstelle=bin_suche(werte_array, anz, sa);
	if (fundstelle >= 0) {
		printf("Fundstelle: %d. Element (=%d, Pointer: %p).\n", fundstelle, werte_array[fundstelle], &werte_array[fundstelle]);
	} else {
		printf("Suchausdruck nicht gefunden.\n");
	}
	return(0);
}

/// Binäre Suche eines Suchausdrucks in einem (aufsteigend) sortierten Wertearray.
/// @param val_array[]	Das Array mit den zu durchsuchenden Werten
/// @param element_anz	Anzahl der Elemente in val_array[]
/// @param suchausdruck	Der Wert, nach dem gesucht werden soll
/// @return Fundstelle (falls nichts gefunden wird, wird -1 zurückgegeben)
int bin_suche(int val_array[], int element_anz, int suchausdruck)
{
	printf("\n");
	zeige_arrayelemente(val_array, element_anz);
	printf(", (%d Element(e))\n", element_anz);
	int m=0;
	int pos=element_anz / 2;	// Da Int., keine Nachkommastellen bei Div.!
	if ((val_array[0] != suchausdruck) && (!pos))
	{ // Suchausdruck nicht gef., rekursiver Aufstieg
		printf("Suchausdruck nicht gefunden!\n");
		return(-1);	// Eigentlich ungültiger Wert zur Kennzeichnung des Suchmisserfolgs
	}
	if (val_array[pos] == suchausdruck)
	{ // Suchausdruck gef., rekursiver Aufstieg
		printf("Suchausdruck gefunden!\n");
		return(pos);
	}
	if (suchausdruck > val_array[pos])
	{	// rekursiver Abstieg in den rechten Teilbaum
		printf("%d>%d Daher neue Suche im RECHTEM TEILBAUM", suchausdruck, val_array[pos]);
		m=bin_suche(val_array+pos, element_anz - pos, suchausdruck);
		if (m >= 0) {
			pos = pos+m;
		} else {
			pos = m;
		}
	}
	if (suchausdruck < val_array[pos])
	{	// rekursiver Abstieg in den linken Teilbaum
		printf("%d<%d Daher neue Suche im LINKEM TEILBAUM", suchausdruck, val_array[pos]);
		m=bin_suche(val_array, pos, suchausdruck);
		pos = m;
	}
	return(pos);
}

/// Anzeigen der Elemente des übergebenen Arrays.
/// @param array[]	Das auszugebende Array
/// @param anz		Anzahl der Arrayelemente
int zeige_arrayelemente (int array[], int anz)
{
	int i;

	for (i=0;i<anz;i++) {
		printf("%d ", array[i]);
	}

	return(0);
}
