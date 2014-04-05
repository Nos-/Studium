/** \file Projekt.h \brief Diese Datei enthält sonstige Funktionen für alle Module der Materialverwaltung.
 * 
 * Sie ist Bestandteil der Belegarbeit Programmieren1, Aufgabe 2: Materialverwaltung bei Herrn Prof. Beck.
 * \author Name: N. Schwirz
 * \version 0.1.1
 * 
 * 
 * \remark Aufruf mit: `gcc -D{LINUX|WINDOWS} *.c`
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// #include <stdarg.h>

// Debugmodus standardmäßig (de)aktivieren. Wirkt sich auch auf die Dokumentation (`make doku`) aus!
// #define DEBUG

/** \def DEBUG
 * \brief Das Preprozessorsymbol DEBUG (de)aktiviert die Miteinkompilierung von Makros für Debugmeldungen.
 *
 * Zur Verwendung der folgenden Preprozessorinstruktionen muss beim Kompilieren das Symbol #DEBUG definiert sein, da sie ansonsten ignoriert werden (sogar in der mit `make doku` erstellten Dokumantation). Dies kann entweder mittels `-DDEBUG` Parameter beim Kompilieren oder am Beginn dieser Datei (bzw. in der Datei, die diese Headerdatei einbindet) geschehen.
 */

#ifndef LOGFILE
	/// Protokolldatei für den Debugmodus
	#define LOGFILE "logfile.txt"
#endif

#ifdef DEBUG

	#ifndef DEBUG_INIT
		/// Logdatei Neuerstellen oder leeren, falls schon existent.
		/**
		 * Verwendung: `DEBUG_INIT`
		 * 
		 * Dieses Preprozessorsymbol sollte in entspr. Dateien ganz am Anfang eingebunden werden, da die folgenden Makros ggf. darauf aufbauen!
		 * 
		 * Enthaltene Funktionalität:
		 * * Erstellt die Protokolldatei (siehe: #LOGFILE) neu bzw. leert sie, falls sie schon existiert.
		 * 
		 * \error 100: Logdatei konnte nicht erstellt/ zum Schreiben geöffnet werden.
		 */
		#define DEBUG_INIT \
		FILE* DEBUG_logFile;\
		DEBUG_logFile=fopen(LOGFILE,"w");\
		if (DEBUG_logFile==NULL){\
			perror("Logdatei konnte nicht erstellt/ zum Schreiben geöffnet werden.");\
			exit(100);\
		}\
		fprintf(DEBUG_logFile,"Datum und Zeit der Kompilierung: %s %s ( %s )\n", __DATE__ , __TIME__ , __FILE__);\
		fclose(DEBUG_logFile);
		// Weitere Vorbereitungsschritte bitte hier eintragen
	#endif

	#ifndef DEBUG_STR
		/// Text an Logdatei anhängen.
		/**
		 * Vorraussetzung: Erfordert einen vorherigen Aufruf des Makros #DEBUG_INIT, sofern noch nicht geschehen.
		 * 
		 * Verwendung: `DEBUG_STR(<Text>)`
		 * 
		 * \error 101: Logdatei konnte nicht zum Anhängen geöffnet werden.
		 */
		#define DEBUG_STR(s) \
		{ FILE* DEBUG_logfile2;\
		DEBUG_logfile2=fopen("logfile.txt","a");\
			if (DEBUG_logfile2==NULL){\
					perror("Logdatei konnte nicht zum Anhängen geöffnet werden");\
					exit(101);\
			}\
		fprintf(DEBUG_logfile2,"%s\n",s);\
		fclose(DEBUG_logfile2);};
		// Es werden hier umschließende geschweifte Klammern verwendet, um den Code vom restlichen Prog. abzukapseln; die hier verw. Variablen sind somit lokal
	#endif
#else
	#ifndef DEBUG_INIT
		# define DEBUG_INIT
	#endif
	#ifndef DEBUG_STR(s)
		# define DEBUG_STR(s) 			//tue nichts (da Debugmodus deativiert)
	#endif
#endif

// Plattformspezifische Makros
#if defined LINUX						  // Gibt an, das es sich um ein linuxartiges Betriebssystem handelt
	#define CLEAR \
		if (system("clear") != 0) {\
			DEBUG_STR("system(clear) fehlgeschlagen.") \
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); \
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); \
		};
#elif defined WINDOWS					// Gibt an, das es sich um ein windowsartiges Betriebssystem handelt
	#define CLEAR \
		if (system("cls") != 0) {\
			DEBUG_STR("system(clear) fehlgeschlagen.") \
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); \
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); \
		};
#else 									// Fallback für andere Betriebssysteme
	/// Betriebssystemunabhängige Befehle, um den Bildschirm zu löschen.
	/**
	 * Je nachdem welches Betriebssystem-Preprozessorsymbol definiert ist, wird ein entsprechender Betriebssystemspezifischer Befehl verwendet.
	 * 
	 * Unterstützte Betriebssystemsymbole:
	 * * *LINUX*	  : `system(clear)`
	 * * *WINDOWS* : `system(cls)`
	 * 
	 * Vorraussetzung: Erfordert ggf. einen vorherigen Aufruf des Makros #DEBUG_INIT, sofern noch nicht geschehen.
	 * 
	 * Verwendung: `CLEAR`
	 * 
	 * Falls das Leeren des Bildschirms (per system()-Befehl) fehlschlägt, wird einfach die Fallbackvariante (Leerzeilen per printf()) verwendet.
	 * Außerdem wird auch per #DEBUG_STR ein entspr. Eintrag in der Protokolldatei (siehe #LOGFILE) vermerkt.
	 */
	#define CLEAR \
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); \
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#endif
