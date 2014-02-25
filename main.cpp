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

// STD Lib Headers
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>

#include <SFML/Audio.hpp>

// Custom Headers
#include "glFunc.h"

/**
 * main: Entry function for the program. Calls all other functions to get
 * program running.
 *
 * Inputs: argc: Number of arguments input to program
 *         argv: Arguments input to program
 * Outputs: Status of program termination.
 */
int main(int argc, char** argv) {
  // TODO: Check args

  // Init GLUT
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Visualizer");

  // Init GL
  initGL();
  // Set Callbacks
  glutReshapeFunc(reshape);
  glutDisplayFunc(render);
  glutIdleFunc(render);
  glutMainLoop();

  // We should never get here, as GLUT takes over!
  return 1;
}
