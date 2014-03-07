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
//#include "Turing.h"

const int scales = 5;
const int varrad = 2;
const int blurnum = 1;

const int aDef[5] = {100, 64, 16, 4, 1},
    iDef[5] = {200, 128, 32, 8, 2},
    wDef[5] = {1,1,1,1,1},
    sDef[5] = {3,2,2,2,2};
const double saDef[5] = {.05, .04, .03, .02, .01};

class glrenderer : public QGLWidget
{
    Q_OBJECT
public:
    glrenderer() :
    buffersize_(2205) {}
    /**
     * @brief loadShaders loads all available shaders
     */
    void loadShaders();

    /**
     * @brief loadSoundFile loads a sound file at a given filename
     * @param filename the location of the file to be played
     */
    void loadSoundFile(const std::string &filename);
private:
    /**
     * @brief printShaderLog prints out any compilation errors, etc. generated from the
     * creation of this GL object
     *
     * @param obj shader object ID
     */
    void printShaderLog(GLuint obj);

    /**
     * @brief prints out any compilation errors, etc. generated from the
     * creation of this GL object
     *
     * @param obj shader object ID
     */
    void printProgramLog(GLuint obj);

    /**
     * @brief initShader generates a shader program object from the given vertex and
     * fragment source files
     * @param vertFileName vertex shader source filename
     * @param fragFileName fragment shader source filename
     * @return shader program object
     */
    GLint initShader(std::string &vertFileName, std::string &fragFileName);
    /**
     * @brief initShaders generates a bunch of shaders.
     */
    void initShaders();

    /**
     * @brief initBuffers initializes frame buffer objects for render to texture procedures
     */
    void initBuffers();

    /**
     * @brief renderGrid Renders a grid of points to be passed to a shader. The positions
     * of the points are somewhat arbitrary, since they will be sent to the shader
     * anyways.
     *
     * @param minx minimum x value
     * @param maxx maximum x value
     * @param miny minimum y value
     * @param maxy maximum y value
     * @param dx how far apart each vertex is in the x direction
     * @param dy how far apart each vertex is in the y direction
     */
    void renderGrid(float minx, float maxx, float miny, float maxy, float dx, float dy);

    /**
     * @brief render called during the "paintGL" callback. Runs approximately 60FPS,
     * although this number is not static and cannot be assumed!
     */
    void render();

    void initSoundStream();
    void renderFFT(double *dataAbs);
    void renderToTexture();
    glm::vec3 HSVtoRGB(float h, float s, float v);

    glm::vec2 dim_;

    /**
     * @brief shaders a list of all GLuints that link to a shader
     */
    std::vector<GLuint> shaders;

    /**
     * @brief t current time
     */
    float t_;

    /**
     * @brief last_t time of last frame
     */
    float last_t_;

    /**
     * @brief soundstream used to stream sound data
     */
    sfe::SequentialSoundStreamer *soundstream_;

    /**
     * @brief sound_t time of current sound
     */
    float sound_t_;

    /**
     * @brief fbo pixel buffer object for the output pixels
     */
    GLuint fbo;
    /**
     * @brief vbo pixel buffer object for calculating variance
     */
    GLuint *vbo;

    GLuint dbo;

    GLuint pixels_[2];
    GLuint soundTex;

    GLuint soundTexLoc_, pixelTexLoc_;

    size_t buffersize_;

    QTimer timer_;
    QElapsedTimer etimer_;

    int pingpong;
protected:
    /**
     * @brief initializeGL Calls several functions to setup the initial GL state.
     */
    void initializeGL();
    void paintGL();
    void updateGL();
    /**
     * @brief resizeGL callback for reshaping the window
     * @param w new width of the window, in pixels
     * @param h new height of the window, in pixels
     */
    void resizeGL(int width, int height);

};

#endif // GLRENDERER_H
