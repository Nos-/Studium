CC = cc
LD = ld
DOXYGEN = doxygen

make_all:	linux linux_debug windows windows_debug doku
			@echo "Alle Ziele erstellt."

linux:
		@echo "Verwende Linux spezifische Systembefehle"
		$(CC) -DLINUX $(CFLAGS) -o Materialverwaltung_l *.c

linux_debug:
		@echo "Verwende Linux spezifische Systembefehle und den Debugmodus"
		$(CC) -g -DLINUX $(CFLAGS) -o Materialverwaltung_ld *.c

windows:
		@echo "Verwende Windows spezifische Systembefehle"
		$(CC) -DWINDOWS $(CFLAGS) -o Materialverwaltung_w *.c

windows_debug:
		@echo "Verwende Windows spezifische Systembefehle und den Debugmodus"
		$(CC) -g -DWINDOWS $(CFLAGS) -o Materialverwaltung_wd *.c

doku:
		@echo "Erstelle Dokumentation"
		$(DOXYGEN)
		@echo "Die Dokumentation sollte sich nun im gleichnamigen Unterverzeichnis befinden"

clean:	
		@echo "Entferne alle erstellten Dateien wieder"
		rm -vr ./Materialverwaltung_* ./Dokumentation/*

help:
		@echo "Auflistung aller Make-Ziele:"
		@echo "make_all               - erstellt alle Ziele"
		@echo "linux, linux_debug     - Linux spezifische Systembefehle mit aus- oder eingeschaltetem Debugmodus"
		@echo "windows, windows_debug - Windows spezifische Systembefehle mit aus- oder eingeschaltetem Debugmodus"
		@echo "clean                  - Entfernt die erstellten Dateien wieder"
		@echo "doku                   - Erstelltung der Dokumentation (Doxygen und ggf. Graphviz müssen installiert sein)"
		
