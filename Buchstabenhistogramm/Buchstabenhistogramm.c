/// Zählt die Häufigkeit der Buchstaben, des ihm per Standardeingabe übergebenen Textes und gibt diese als Prozentangabe aus. Kann mit dem Filter `sort -n` auch noch sortiert werden.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
	double letterCount[255] = {};
	int i = 0;
	long len = 0;
	char letter;

	// Zeichenhäufigkeit zählen
	while (!feof(stdin)) {
		// Daten von Standardin lesen
		letter = getchar();			// Stdin auslesen
		letterCount[(int)letter] += 1;
		len++;
	}

	// Zeichenhäufigkeit normieren
	for(i=0; i<=255; i++) {
		letterCount[i] = letterCount[i] / len * 100;
	}

//	printf("Buchstabenhäufigkeitsverteilung\n");
	for(i=32; i<=128; i++) {				// nur Buchstaben, Zahlen und übliche Sonderzeichen ausgeben
		printf("%3.2f%% , %c\n", letterCount[i], (char)i);
	}

	return 0;
}
