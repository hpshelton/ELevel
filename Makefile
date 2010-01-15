#############################################################################
# Makefile for building: ELevel.app/Contents/MacOS/ELevel
# Generated by qmake (2.01a) (Qt 4.6.0) on: Thu Jan 14 22:38:27 2010
# Project:  ELevel.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.6/mkspecs/macx-g++ -macx -o Makefile ELevel.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -arch i386 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -gdwarf-2 -arch i386 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Qt4.6/mkspecs/macx-g++ -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -I. -Isrc/dataModel -Isrc/editCard -Isrc/elevel -Isrc/preferences -Isrc -Iobj -F/Library/Frameworks
LINK          = g++
LFLAGS        = -headerpad_max_install_names -arch i386
LIBS          = $(SUBLIBS) -F/Library/Frameworks -L/Library/Frameworks -framework QtGui -framework QtCore 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/dataModel/card.cpp \
		src/dataModel/cardSection.cpp \
		src/dataModel/deck.cpp \
		src/dataModel/testStat.cpp \
		src/elevel/elevel.cpp \
		src/elevel/mainWindow.cpp \
		src/elevel/viewState.cpp \
		src/editCard/drawingGraphicsView.cpp \
		src/elevel/cardAreaGUI.cpp \
		src/elevel/splashScreen.cpp \
		src/preferences/preferences.cpp \
		src/preferences/preferencesGUI.cpp obj/moc_mainWindow.cpp \
		obj/moc_viewState.cpp \
		obj/moc_cardAreaGUI.cpp \
		obj/moc_splashScreen.cpp \
		obj/moc_preferences.cpp \
		obj/moc_preferencesGUI.cpp \
		obj/qrc_ELevel.cpp
OBJECTS       = obj/card.o \
		obj/cardSection.o \
		obj/deck.o \
		obj/testStat.o \
		obj/elevel.o \
		obj/mainWindow.o \
		obj/viewState.o \
		obj/drawingGraphicsView.o \
		obj/cardAreaGUI.o \
		obj/splashScreen.o \
		obj/preferences.o \
		obj/preferencesGUI.o \
		obj/moc_mainWindow.o \
		obj/moc_viewState.o \
		obj/moc_cardAreaGUI.o \
		obj/moc_splashScreen.o \
		obj/moc_preferences.o \
		obj/moc_preferencesGUI.o \
		obj/qrc_ELevel.o
DIST          = /usr/local/Qt4.6/mkspecs/common/unix.conf \
		/usr/local/Qt4.6/mkspecs/common/mac.conf \
		/usr/local/Qt4.6/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.6/mkspecs/qconfig.pri \
		/usr/local/Qt4.6/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.6/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.6/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.6/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.6/mkspecs/features/debug.prf \
		/usr/local/Qt4.6/mkspecs/features/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/x86.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.6/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.6/mkspecs/features/qt.prf \
		/usr/local/Qt4.6/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.6/mkspecs/features/moc.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.6/mkspecs/features/resources.prf \
		/usr/local/Qt4.6/mkspecs/features/uic.prf \
		/usr/local/Qt4.6/mkspecs/features/yacc.prf \
		/usr/local/Qt4.6/mkspecs/features/lex.prf \
		/usr/local/Qt4.6/mkspecs/features/include_source_dir.prf \
		ELevel.pro
QMAKE_TARGET  = ELevel
DESTDIR       = 
TARGET        = ELevel.app/Contents/MacOS/ELevel

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-gdwarf-2 \
		-arch \
		i386 \
		-Wall \
		-W


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

all: Makefile ELevel.app/Contents/PkgInfo ELevel.app/Contents/Resources/empty.lproj ELevel.app/Contents/Info.plist ELevel.app/Contents/Resources/icon.icns $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) ELevel.app/Contents/MacOS/ || $(MKDIR) ELevel.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ELevel.pro  /usr/local/Qt4.6/mkspecs/macx-g++/qmake.conf /usr/local/Qt4.6/mkspecs/common/unix.conf \
		/usr/local/Qt4.6/mkspecs/common/mac.conf \
		/usr/local/Qt4.6/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.6/mkspecs/qconfig.pri \
		/usr/local/Qt4.6/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.6/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.6/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.6/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.6/mkspecs/features/debug.prf \
		/usr/local/Qt4.6/mkspecs/features/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/x86.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.6/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.6/mkspecs/features/qt.prf \
		/usr/local/Qt4.6/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.6/mkspecs/features/moc.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.6/mkspecs/features/resources.prf \
		/usr/local/Qt4.6/mkspecs/features/uic.prf \
		/usr/local/Qt4.6/mkspecs/features/yacc.prf \
		/usr/local/Qt4.6/mkspecs/features/lex.prf \
		/usr/local/Qt4.6/mkspecs/features/include_source_dir.prf \
		/Library/Frameworks/QtGui.framework/QtGui.prl \
		/Library/Frameworks/QtCore.framework/QtCore.prl
	$(QMAKE) -spec /usr/local/Qt4.6/mkspecs/macx-g++ -macx -o Makefile ELevel.pro
/usr/local/Qt4.6/mkspecs/common/unix.conf:
/usr/local/Qt4.6/mkspecs/common/mac.conf:
/usr/local/Qt4.6/mkspecs/common/mac-g++.conf:
/usr/local/Qt4.6/mkspecs/qconfig.pri:
/usr/local/Qt4.6/mkspecs/features/qt_functions.prf:
/usr/local/Qt4.6/mkspecs/features/qt_config.prf:
/usr/local/Qt4.6/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt4.6/mkspecs/features/default_pre.prf:
/usr/local/Qt4.6/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt4.6/mkspecs/features/mac/dwarf2.prf:
/usr/local/Qt4.6/mkspecs/features/debug.prf:
/usr/local/Qt4.6/mkspecs/features/default_post.prf:
/usr/local/Qt4.6/mkspecs/features/mac/default_post.prf:
/usr/local/Qt4.6/mkspecs/features/mac/x86.prf:
/usr/local/Qt4.6/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt4.6/mkspecs/features/warn_on.prf:
/usr/local/Qt4.6/mkspecs/features/qt.prf:
/usr/local/Qt4.6/mkspecs/features/unix/thread.prf:
/usr/local/Qt4.6/mkspecs/features/moc.prf:
/usr/local/Qt4.6/mkspecs/features/mac/rez.prf:
/usr/local/Qt4.6/mkspecs/features/mac/sdk.prf:
/usr/local/Qt4.6/mkspecs/features/resources.prf:
/usr/local/Qt4.6/mkspecs/features/uic.prf:
/usr/local/Qt4.6/mkspecs/features/yacc.prf:
/usr/local/Qt4.6/mkspecs/features/lex.prf:
/usr/local/Qt4.6/mkspecs/features/include_source_dir.prf:
/Library/Frameworks/QtGui.framework/QtGui.prl:
/Library/Frameworks/QtCore.framework/QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Qt4.6/mkspecs/macx-g++ -macx -o Makefile ELevel.pro

ELevel.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) ELevel.app/Contents || $(MKDIR) ELevel.app/Contents 
	@$(DEL_FILE) ELevel.app/Contents/PkgInfo
	@echo "APPL????" >ELevel.app/Contents/PkgInfo
ELevel.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) ELevel.app/Contents/Resources || $(MKDIR) ELevel.app/Contents/Resources 
	@touch ELevel.app/Contents/Resources/empty.lproj
	
ELevel.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) ELevel.app/Contents || $(MKDIR) ELevel.app/Contents 
	@$(DEL_FILE) ELevel.app/Contents/Info.plist
	@sed -e "s,@ICON@,icon.icns,g" -e "s,@EXECUTABLE@,ELevel,g" -e "s,@TYPEINFO@,????,g" /usr/local/Qt4.6/mkspecs/macx-g++/Info.plist.app >ELevel.app/Contents/Info.plist
ELevel.app/Contents/Resources/icon.icns: images/icon.icns
	@$(CHK_DIR_EXISTS) ELevel.app/Contents/Resources/ || $(MKDIR) ELevel.app/Contents/Resources/ 
	@$(DEL_FILE) ELevel.app/Contents/Resources/icon.icns
	@$(COPY_FILE) images/icon.icns ELevel.app/Contents/Resources/icon.icns
dist: 
	@$(CHK_DIR_EXISTS) obj/ELevel1.0.0 || $(MKDIR) obj/ELevel1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/ELevel1.0.0/ && $(COPY_FILE) --parents src/defines.h src/dataModel/card.h src/dataModel/cardSection.h src/dataModel/deck.h src/dataModel/testStat.h src/editCard/drawingGraphicsScene.h src/editCard/drawingGraphicsView.h src/elevel/mainWindow.h src/elevel/viewState.h src/elevel/cardAreaGUI.h src/elevel/splashScreen.h src/preferences/preferences.h src/preferences/algorithm.h src/preferences/preferencesGUI.h obj/ELevel1.0.0/ && $(COPY_FILE) --parents src/ELevel.qrc obj/ELevel1.0.0/ && $(COPY_FILE) --parents src/dataModel/card.cpp src/dataModel/cardSection.cpp src/dataModel/deck.cpp src/dataModel/testStat.cpp src/elevel/elevel.cpp src/elevel/mainWindow.cpp src/elevel/viewState.cpp src/editCard/drawingGraphicsView.cpp src/elevel/cardAreaGUI.cpp src/elevel/splashScreen.cpp src/preferences/preferences.cpp src/preferences/preferencesGUI.cpp obj/ELevel1.0.0/ && (cd `dirname obj/ELevel1.0.0` && $(TAR) ELevel1.0.0.tar ELevel1.0.0 && $(COMPRESS) ELevel1.0.0.tar) && $(MOVE) `dirname obj/ELevel1.0.0`/ELevel1.0.0.tar.gz . && $(DEL_FILE) -r obj/ELevel1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r ELevel.app
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: obj/moc_mainWindow.cpp obj/moc_viewState.cpp obj/moc_cardAreaGUI.cpp obj/moc_splashScreen.cpp obj/moc_preferences.cpp obj/moc_preferencesGUI.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) obj/moc_mainWindow.cpp obj/moc_viewState.cpp obj/moc_cardAreaGUI.cpp obj/moc_splashScreen.cpp obj/moc_preferences.cpp obj/moc_preferencesGUI.cpp
obj/moc_mainWindow.cpp: src/elevel/viewState.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h \
		src/elevel/cardAreaGUI.h \
		src/elevel/mainWindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/elevel/mainWindow.h -o obj/moc_mainWindow.cpp

obj/moc_viewState.cpp: src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h \
		src/elevel/viewState.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/elevel/viewState.h -o obj/moc_viewState.cpp

obj/moc_cardAreaGUI.cpp: src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/elevel/viewState.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h \
		src/elevel/cardAreaGUI.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/elevel/cardAreaGUI.h -o obj/moc_cardAreaGUI.cpp

obj/moc_splashScreen.cpp: src/elevel/splashScreen.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/elevel/splashScreen.h -o obj/moc_splashScreen.cpp

obj/moc_preferences.cpp: src/preferences/algorithm.h \
		src/dataModel/deck.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/testStat.h \
		src/preferences/preferences.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/preferences/preferences.h -o obj/moc_preferences.cpp

obj/moc_preferencesGUI.cpp: src/preferences/preferences.h \
		src/preferences/algorithm.h \
		src/dataModel/deck.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/testStat.h \
		src/preferences/preferencesGUI.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/preferences/preferencesGUI.h -o obj/moc_preferencesGUI.cpp

compiler_rcc_make_all: obj/qrc_ELevel.cpp
compiler_rcc_clean:
	-$(DEL_FILE) obj/qrc_ELevel.cpp
obj/qrc_ELevel.cpp: src/ELevel.qrc \
		images/splash.png \
		images/test.png \
		images/ellipse.png \
		images/newCard.png \
		images/newDeck.png \
		images/icon.png \
		images/save.png \
		images/rectangle.png \
		images/editCard.png \
		images/line.png \
		images/text.png \
		images/open.png \
		images/eLevel.png \
		images/selection.png
	/Developer/Tools/Qt/rcc -name ELevel src/ELevel.qrc -o obj/qrc_ELevel.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
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

obj/card.o: src/dataModel/card.cpp src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/card.o src/dataModel/card.cpp

obj/cardSection.o: src/dataModel/cardSection.cpp src/dataModel/cardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/cardSection.o src/dataModel/cardSection.cpp

obj/deck.o: src/dataModel/deck.cpp src/dataModel/deck.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/testStat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/deck.o src/dataModel/deck.cpp

obj/testStat.o: src/dataModel/testStat.cpp src/dataModel/testStat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/testStat.o src/dataModel/testStat.cpp

obj/elevel.o: src/elevel/elevel.cpp src/elevel/mainWindow.h \
		src/elevel/viewState.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h \
		src/elevel/cardAreaGUI.h \
		src/elevel/splashScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/elevel.o src/elevel/elevel.cpp

obj/mainWindow.o: src/elevel/mainWindow.cpp src/elevel/mainWindow.h \
		src/elevel/viewState.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h \
		src/elevel/cardAreaGUI.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/mainWindow.o src/elevel/mainWindow.cpp

obj/viewState.o: src/elevel/viewState.cpp src/elevel/viewState.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/viewState.o src/elevel/viewState.cpp

obj/drawingGraphicsView.o: src/editCard/drawingGraphicsView.cpp src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/drawingGraphicsScene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/drawingGraphicsView.o src/editCard/drawingGraphicsView.cpp

obj/cardAreaGUI.o: src/elevel/cardAreaGUI.cpp src/elevel/cardAreaGUI.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/elevel/viewState.h \
		src/dataModel/deck.h \
		src/dataModel/testStat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/cardAreaGUI.o src/elevel/cardAreaGUI.cpp

obj/splashScreen.o: src/elevel/splashScreen.cpp src/elevel/splashscreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/splashScreen.o src/elevel/splashScreen.cpp

obj/preferences.o: src/preferences/preferences.cpp src/preferences/preferences.h \
		src/preferences/algorithm.h \
		src/dataModel/deck.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/testStat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/preferences.o src/preferences/preferences.cpp

obj/preferencesGUI.o: src/preferences/preferencesGUI.cpp src/preferences/preferencesGUI.h \
		src/preferences/preferences.h \
		src/preferences/algorithm.h \
		src/dataModel/deck.h \
		src/dataModel/card.h \
		src/dataModel/CardSection.h \
		src/editCard/drawingGraphicsScene.h \
		src/editCard/drawingGraphicsView.h \
		src/dataModel/cardSection.h \
		src/editCard/DrawingGraphicsScene.h \
		src/dataModel/testStat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/preferencesGUI.o src/preferences/preferencesGUI.cpp

obj/moc_mainWindow.o: obj/moc_mainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_mainWindow.o obj/moc_mainWindow.cpp

obj/moc_viewState.o: obj/moc_viewState.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_viewState.o obj/moc_viewState.cpp

obj/moc_cardAreaGUI.o: obj/moc_cardAreaGUI.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_cardAreaGUI.o obj/moc_cardAreaGUI.cpp

obj/moc_splashScreen.o: obj/moc_splashScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_splashScreen.o obj/moc_splashScreen.cpp

obj/moc_preferences.o: obj/moc_preferences.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_preferences.o obj/moc_preferences.cpp

obj/moc_preferencesGUI.o: obj/moc_preferencesGUI.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_preferencesGUI.o obj/moc_preferencesGUI.cpp

obj/qrc_ELevel.o: obj/qrc_ELevel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/qrc_ELevel.o obj/qrc_ELevel.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

