#ifndef GLRENDERER_H
#define GLRENDERER_H

// GL Headers
#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

// GLM
#include <glm/glm.hpp>

// STD Lib headers
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <vector>

// QT headers
#include <QGLWidget>
#include <Qt>
#include <QTimer>
#include <QElapsedTimer>

// custom files/headers
#include "SequentialSoundStreamer.h"

class glrenderer : public QGLWidget
{
    Q_OBJECT
public:
    glrenderer() :
    buffersize_(2205) {}
    /**
     * @brief loadShaders
     */
    void loadShaders();

    /**
     * @brief loadSoundFile
     * @param filename
     */
    void loadSoundFile(const std::string &filename);
private:
    /**
     * prints out any compilation errors, etc. generated from the
     * creation of this GL object
     *
     * Inputs: shader: shader object ID
     */
    void printShaderLog(GLuint obj);

    /**
     * prints out any compilation errors, etc. generated from the
     * creation of this GL object
     *
     * Inputs: shader: shader object ID
     */
    void printProgramLog(GLuint obj);

    /**
     * generates a shader program object from the given vertex and
     * fragment source files.
     *
     * Inputs: vertFileName: vertex shader source filename
     *         fragFileName: fragment shader source filename
     * Output: shader program object
     */
    GLint initShader(std::string &vertFileName, std::string &fragFileName);
    /**
     * generates a bunch of shaders.
     */
    void initShaders();

    /**
     * renderGrid: Renders a grid of points to be passed to a shader. The positions
     * of the points are somewhat arbitrary, since they will be sent to the shader
     * anyways.
     *
     * Inputs: minx: minimum x value
     *         maxx: maximum x value
     *         miny: minimum y value
     *         maxy: maximum y value
     *         dx: how far apart each vertex is in the x direction
     *         dy: how far apart each vertex is in the y direction
     */
    void renderGrid(float minx, float maxx, float miny, float maxy, float dx, float dy);

    /**
     * called during the "paintGL" callback. Runs approximately 60FPS,
     * although this number is not static and cannot be assumed!
     */
    void render();

    void initSoundStream();
    void renderFFT(double *dataAbs);

    glm::vec2 dim_;

    /**
     * shaders: a list of all GLuints that link to a shader
     */
    std::vector<GLuint> shaders;

    /**
     * t: current time
     */
    float t_;

    /**
     * last_t: last time
     */
    float last_t_;

    /**
     * soundstream: streams sound data
     */
    sfe::SequentialSoundStreamer *soundstream_;

    /**
     * sound_t: time of current sound
     */
    float sound_t_;

    size_t buffersize_;

    QTimer timer_;
    QElapsedTimer etimer_;
protected:
    /**
     * initializeGL: Calls several functions to setup the initial GL state.
     */
    void initializeGL();
    void paintGL();
    void updateGL();
    /**
     * Callback for reshaping the window
     * Inputs: w: new width of the window, in pixels
     *         h: new height of the window, in pixels
     */
    void resizeGL(int width, int height);

};

#endif // GLRENDERER_H
