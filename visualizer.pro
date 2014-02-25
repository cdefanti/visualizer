#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T22:23:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualizer-qt
TEMPLATE = app

INCLUDEPATH += ./lib/glm-0.9.2.7

FFTWDIR = /usr/local/Cellar/fftw/3.3.3

QMAKE_LIBDIR += $$FFTWDIR/lib \

LIBS += -lfftw3f \
        -lfftw3 \
        -lfftw3l \
        -framework sfml-audio \
        -framework sfml-system

INCLUDEPATH += $$FFTWDIR/include

SOURCES += main.cpp\
        mainwindow.cpp \
    glrenderer.cpp \
    SequentialSoundStreamer.cpp

HEADERS  += mainwindow.h \
    glrenderer.h \
    SequentialSoundStreamer.h

FORMS    += mainwindow.ui
