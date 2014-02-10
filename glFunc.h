#ifndef GL_FUNC_H_
#define GL_FUNC_H_

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

// STD Lib headers
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <vector>

/*
 * printShaderLog: prints out any compilation errors, etc. generated from the
 * creation of this GL object
 *
 * Inputs: shader: shader object ID
 */
void printShaderLog(GLuint obj);

/*
 * printProgramLog: prints out any compilation errors, etc. generated from the
 * creation of this GL object
 *
 * Inputs: shader: shader object ID
 */
void printProgramLog(GLuint obj);

/*
 * initShader: generates a shader program object from the given vertex and
 * fragment source files.
 *
 * Inputs: vertFileName: vertex shader source filename
 *         fragFileName: fragment shader source filename
 * Output: shader program object
 */
GLint initShader(std::string &vertFileName, std::string &fragFileName);

/* 
 * reshape: Callback for reshaping the window
 * Inputs: w: new width of the window, in pixels
 *         h: new height of the window, in pixels
 */
void reshape(int w, int h);

/*
 * renderGrid: Renders a grid of points to be passed to a shader. The positions
 * of the points are somewhat arbitrary, since they will be sent to the shader
 * anyways.
 *
 * Inputs: w: width of grid in points
 *         h: height of grid in points
 */
void renderGrid(int w, int h);

/*
 * render: Callback for passively updating GL. Runs approximately 60FPS,
 * although this number is not static and cannot be assumed!
 */
void render();

/*
 * loadShaders: Searches through a list of shaders and initializes them using
 * initShader for each one.
 */
void loadShaders();

/*
 * initGL: Calls several functions to setup the initial GL state.
 */
void initGL();

#endif
