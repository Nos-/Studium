#############################################################################
# Makefile for building: medienverwaltung
# Generated by qmake (2.01a) (Qt 4.8.6) on: Di. Sep 23 02:22:30 2014
# Project:  ../medienverwaltung/medienverwaltung.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++-64 CONFIG+=debug CONFIG+=declarative_debug -o Makefile ../medienverwaltung/medienverwaltung.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I../medienverwaltung -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I../medienverwaltung -I.
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../medienverwaltung/main.cpp \
		../medienverwaltung/mainwindow.cpp \
		../medienverwaltung/mediaWidget.cpp \
		../medienverwaltung/treeitem.cpp \
		../medienverwaltung/treemodel.cpp moc_mainwindow.cpp \
		moc_mediaWidget.cpp \
		moc_treemodel.cpp \
		qrc_medienverwaltung.cpp
OBJECTS       = main.o \
		mainwindow.o \
		mediaWidget.o \
		treeitem.o \
		treemodel.o \
		moc_mainwindow.o \
		moc_mediaWidget.o \
		moc_treemodel.o \
		qrc_medienverwaltung.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		../medienverwaltung/medienverwaltung.pro
QMAKE_TARGET  = medienverwaltung
DESTDIR       = 
TARGET        = medienverwaltung

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9][^0-9]*\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: ../medienverwaltung/medienverwaltung.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++-64 CONFIG+=debug CONFIG+=declarative_debug -o Makefile ../medienverwaltung/medienverwaltung.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/declarative_debug.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++-64 CONFIG+=debug CONFIG+=declarative_debug -o Makefile ../medienverwaltung/medienverwaltung.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/medienverwaltung1.0.0 || $(MKDIR) .tmp/medienverwaltung1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/medienverwaltung1.0.0/ && $(COPY_FILE) --parents ../medienverwaltung/mainwindow.h ../medienverwaltung/mediaWidget.h ../medienverwaltung/treeitem.h ../medienverwaltung/treemodel.h .tmp/medienverwaltung1.0.0/ && $(COPY_FILE) --parents ../medienverwaltung/medienverwaltung.qrc .tmp/medienverwaltung1.0.0/ && $(COPY_FILE) --parents ../medienverwaltung/main.cpp ../medienverwaltung/mainwindow.cpp ../medienverwaltung/mediaWidget.cpp ../medienverwaltung/treeitem.cpp ../medienverwaltung/treemodel.cpp .tmp/medienverwaltung1.0.0/ && (cd `dirname .tmp/medienverwaltung1.0.0` && $(TAR) medienverwaltung1.0.0.tar medienverwaltung1.0.0 && $(COMPRESS) medienverwaltung1.0.0.tar) && $(MOVE) `dirname .tmp/medienverwaltung1.0.0`/medienverwaltung1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/medienverwaltung1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_mediaWidget.cpp moc_treemodel.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_mediaWidget.cpp moc_treemodel.cpp
moc_mainwindow.cpp: ../medienverwaltung/mediaWidget.h \
		../medienverwaltung/treemodel.h \
		../medienverwaltung/mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) ../medienverwaltung/mainwindow.h -o moc_mainwindow.cpp

moc_mediaWidget.cpp: ../medienverwaltung/treemodel.h \
		../medienverwaltung/mediaWidget.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) ../medienverwaltung/mediaWidget.h -o moc_mediaWidget.cpp

moc_treemodel.cpp: ../medienverwaltung/treemodel.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) ../medienverwaltung/treemodel.h -o moc_treemodel.cpp

compiler_rcc_make_all: qrc_medienverwaltung.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_medienverwaltung.cpp
qrc_medienverwaltung.cpp: ../medienverwaltung/medienverwaltung.qrc \
		../medienverwaltung/resources/default.txt
	/usr/lib/x86_64-linux-gnu/qt4/bin/rcc -name medienverwaltung ../medienverwaltung/medienverwaltung.qrc -o qrc_medienverwaltung.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: ../medienverwaltung/main.cpp ../medienverwaltung/mainwindow.h \
		../medienverwaltung/mediaWidget.h \
		../medienverwaltung/treemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../medienverwaltung/main.cpp

mainwindow.o: ../medienverwaltung/mainwindow.cpp ../medienverwaltung/mainwindow.h \
		../medienverwaltung/mediaWidget.h \
		../medienverwaltung/treemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o ../medienverwaltung/mainwindow.cpp

mediaWidget.o: ../medienverwaltung/mediaWidget.cpp ../medienverwaltung/mediaWidget.h \
		../medienverwaltung/treemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mediaWidget.o ../medienverwaltung/mediaWidget.cpp

treeitem.o: ../medienverwaltung/treeitem.cpp ../medienverwaltung/treeitem.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o treeitem.o ../medienverwaltung/treeitem.cpp

treemodel.o: ../medienverwaltung/treemodel.cpp ../medienverwaltung/treeitem.h \
		../medienverwaltung/treemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o treemodel.o ../medienverwaltung/treemodel.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_mediaWidget.o: moc_mediaWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mediaWidget.o moc_mediaWidget.cpp

moc_treemodel.o: moc_treemodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_treemodel.o moc_treemodel.cpp

qrc_medienverwaltung.o: qrc_medienverwaltung.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_medienverwaltung.o qrc_medienverwaltung.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

