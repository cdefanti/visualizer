#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T22:23:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualizer
TEMPLATE = app

INCLUDEPATH += ./lib/glm-0.9.2.7

FFTWDIR = /usr/local/Cellar/fftw/3.3.3

QMAKE_LIBDIR += $$FFTWDIR/lib \

LIBS += -lfftw3f \
        -lfftw3 \
        -lfftw3l \
        -framework sfml-audio \
        -framework sfml-system \
        -framework sfml-graphics \
        -framework sfml-window

INCLUDEPATH += $$FFTWDIR/include

SOURCES += main.cpp\
        mainwindow.cpp \
    glrenderer.cpp \
    SequentialSoundStreamer.cpp \
    Vars.cpp \
    Turing.cpp

HEADERS  += mainwindow.h \
    glrenderer.h \
    SequentialSoundStreamer.h \
    Turing.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    shaders/turing.f.glsl \
    shaders/turing.v.glsl \
    shaders/test.vs.glsl \
    shaders/test.fs.glsl \
    shaders/aidiff.f.glsl \
    shaders/aidiff.v.glsl \
    shaders/soundwave.f.glsl \
    shaders/soundwave.v.glsl
