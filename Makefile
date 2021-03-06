#############################################################################
# Makefile for building: visualizer.app/Contents/MacOS/visualizer
# Generated by qmake (2.01a) (Qt 4.8.6) on: Tue Feb 25 18:18:15 2014
# Project:  visualizer.pro
# Template: app
# Command: /usr/local/bin/qmake -o Makefile visualizer.pro
#############################################################################

####### Compiler, tools and options

CC            = clang
CXX           = clang++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -arch x86_64 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -stdlib=libc++ -O2 -arch x86_64 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Cellar/qt/HEAD/mkspecs/unsupported/macx-clang -I. -I/usr/local/Cellar/qt/HEAD/lib/QtCore.framework/Versions/4/Headers -I/usr/local/Cellar/qt/HEAD/lib/QtCore.framework/Versions/4/Headers -I/usr/local/Cellar/qt/HEAD/lib/QtGui.framework/Versions/4/Headers -I/usr/local/Cellar/qt/HEAD/lib/QtGui.framework/Versions/4/Headers -I/usr/local/Cellar/qt/HEAD/lib/QtOpenGL.framework/Versions/4/Headers -I/usr/local/Cellar/qt/HEAD/lib/QtOpenGL.framework/Versions/4/Headers -I/usr/local/Cellar/qt/HEAD/include -Ilib/glm-0.9.2.7 -I/usr/local/Cellar/fftw/3.3.3/include -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -I. -F/usr/local/Cellar/qt/HEAD/lib
LINK          = clang++
LFLAGS        = -headerpad_max_install_names -stdlib=libc++ -arch x86_64
LIBS          = $(SUBLIBS) -F/usr/local/Cellar/qt/HEAD/lib -L/usr/local/Cellar/fftw/3.3.3/lib -L/usr/local/Cellar/qt/HEAD/lib -lfftw3f -lfftw3 -lfftw3l -framework sfml-audio -framework sfml-system -framework sfml-graphics -framework QtOpenGL -L/usr/local/Cellar/qt/HEAD/lib -F/usr/local/Cellar/qt/HEAD/lib -framework QtGui -framework QtCore -framework OpenGL -framework AGL 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/local/bin/qmake
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
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.9

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		glrenderer.cpp \
		SequentialSoundStreamer.cpp \
		Vars.cpp \
		Turing.cpp moc_mainwindow.cpp \
		moc_glrenderer.cpp
OBJECTS       = main.o \
		mainwindow.o \
		glrenderer.o \
		SequentialSoundStreamer.o \
		Vars.o \
		Turing.o \
		moc_mainwindow.o \
		moc_glrenderer.o
DIST          = /usr/local/Cellar/qt/HEAD/mkspecs/common/unix.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/mac.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/gcc-base.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/gcc-base-macx.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/clang.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/qconfig.pri \
		/usr/local/Cellar/qt/HEAD/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/qt_functions.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/qt_config.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/exclusive_builds.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/default_pre.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/default_pre.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/release.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/default_post.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/default_post.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/x86_64.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/objective_c.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/shared.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/warn_on.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/qt.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/unix/opengl.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/unix/thread.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/moc.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/rez.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/sdk.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/resources.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/uic.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/yacc.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/lex.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/include_source_dir.prf \
		visualizer.pro
QMAKE_TARGET  = visualizer
DESTDIR       = 
TARGET        = visualizer.app/Contents/MacOS/visualizer

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-O2 \
		-arch \
		x86_64 \
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

all: Makefile visualizer.app/Contents/PkgInfo visualizer.app/Contents/Resources/empty.lproj visualizer.app/Contents/Info.plist $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) visualizer.app/Contents/MacOS/ || $(MKDIR) visualizer.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: visualizer.pro  /usr/local/Cellar/qt/HEAD/mkspecs/unsupported/macx-clang/qmake.conf /usr/local/Cellar/qt/HEAD/mkspecs/common/unix.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/mac.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/gcc-base.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/gcc-base-macx.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/common/clang.conf \
		/usr/local/Cellar/qt/HEAD/mkspecs/qconfig.pri \
		/usr/local/Cellar/qt/HEAD/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/qt_functions.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/qt_config.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/exclusive_builds.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/default_pre.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/default_pre.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/release.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/default_post.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/default_post.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/x86_64.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/objective_c.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/shared.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/warn_on.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/qt.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/unix/opengl.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/unix/thread.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/moc.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/rez.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/sdk.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/resources.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/uic.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/yacc.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/lex.prf \
		/usr/local/Cellar/qt/HEAD/mkspecs/features/include_source_dir.prf \
		/usr/local/Cellar/qt/HEAD/lib/QtOpenGL.framework/QtOpenGL.prl \
		/usr/local/Cellar/qt/HEAD/lib/QtGui.framework/QtGui.prl \
		/usr/local/Cellar/qt/HEAD/lib/QtCore.framework/QtCore.prl
	$(QMAKE) -o Makefile visualizer.pro
/usr/local/Cellar/qt/HEAD/mkspecs/common/unix.conf:
/usr/local/Cellar/qt/HEAD/mkspecs/common/mac.conf:
/usr/local/Cellar/qt/HEAD/mkspecs/common/gcc-base.conf:
/usr/local/Cellar/qt/HEAD/mkspecs/common/gcc-base-macx.conf:
/usr/local/Cellar/qt/HEAD/mkspecs/common/clang.conf:
/usr/local/Cellar/qt/HEAD/mkspecs/qconfig.pri:
/usr/local/Cellar/qt/HEAD/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Cellar/qt/HEAD/mkspecs/features/qt_functions.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/qt_config.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/exclusive_builds.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/default_pre.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/default_pre.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/release.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/default_post.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/default_post.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/x86_64.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/objective_c.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/shared.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/warn_on.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/qt.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/unix/opengl.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/unix/thread.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/moc.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/rez.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/mac/sdk.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/resources.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/uic.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/yacc.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/lex.prf:
/usr/local/Cellar/qt/HEAD/mkspecs/features/include_source_dir.prf:
/usr/local/Cellar/qt/HEAD/lib/QtOpenGL.framework/QtOpenGL.prl:
/usr/local/Cellar/qt/HEAD/lib/QtGui.framework/QtGui.prl:
/usr/local/Cellar/qt/HEAD/lib/QtCore.framework/QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile visualizer.pro

visualizer.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) visualizer.app/Contents || $(MKDIR) visualizer.app/Contents 
	@$(DEL_FILE) visualizer.app/Contents/PkgInfo
	@echo "APPL????" >visualizer.app/Contents/PkgInfo
visualizer.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) visualizer.app/Contents/Resources || $(MKDIR) visualizer.app/Contents/Resources 
	@touch visualizer.app/Contents/Resources/empty.lproj
	
visualizer.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) visualizer.app/Contents || $(MKDIR) visualizer.app/Contents 
	@$(DEL_FILE) visualizer.app/Contents/Info.plist
	@sed -e "s,@SHORT_VERSION@,1.0,g" -e "s,@TYPEINFO@,????,g" -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,visualizer,g" -e "s,@TYPEINFO@,????,g" /usr/local/Cellar/qt/HEAD/mkspecs/unsupported/macx-clang/Info.plist.app >visualizer.app/Contents/Info.plist
dist: 
	@$(CHK_DIR_EXISTS) .tmp/visualizer1.0.0 || $(MKDIR) .tmp/visualizer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/visualizer1.0.0/ && $(COPY_FILE) --parents mainwindow.h glrenderer.h SequentialSoundStreamer.h Turing.h .tmp/visualizer1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp glrenderer.cpp SequentialSoundStreamer.cpp Vars.cpp Turing.cpp .tmp/visualizer1.0.0/ && $(COPY_FILE) --parents mainwindow.ui .tmp/visualizer1.0.0/ && (cd `dirname .tmp/visualizer1.0.0` && $(TAR) visualizer1.0.0.tar visualizer1.0.0 && $(COMPRESS) visualizer1.0.0.tar) && $(MOVE) `dirname .tmp/visualizer1.0.0`/visualizer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/visualizer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r visualizer.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_mainwindow.cpp moc_glrenderer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_glrenderer.cpp
moc_mainwindow.cpp: glrenderer.h \
		SequentialSoundStreamer.h \
		mainwindow.h
	/usr/local/Cellar/qt/HEAD/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ mainwindow.h -o moc_mainwindow.cpp

moc_glrenderer.cpp: SequentialSoundStreamer.h \
		glrenderer.h
	/usr/local/Cellar/qt/HEAD/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ glrenderer.h -o moc_glrenderer.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/local/Cellar/qt/HEAD/bin/uic mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp glFunc.h \
		mainwindow.h \
		glrenderer.h \
		SequentialSoundStreamer.h \
		Turing.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		glrenderer.h \
		SequentialSoundStreamer.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

glrenderer.o: glrenderer.cpp glrenderer.h \
		SequentialSoundStreamer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glrenderer.o glrenderer.cpp

SequentialSoundStreamer.o: SequentialSoundStreamer.cpp SequentialSoundStreamer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SequentialSoundStreamer.o SequentialSoundStreamer.cpp

Vars.o: Vars.cpp Turing.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Vars.o Vars.cpp

Turing.o: Turing.cpp Turing.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Turing.o Turing.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_glrenderer.o: moc_glrenderer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glrenderer.o moc_glrenderer.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

