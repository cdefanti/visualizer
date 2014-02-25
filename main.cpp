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


#include <QtGui/QApplication>
#include "mainwindow.h"

/*
 * main: Entry function for the program. Calls all other functions to get
 * program running.
 *
 * Inputs: argc: Number of arguments input to program
 *         argv: Arguments input to program
 * Outputs: Status of program termination.
 */
int main(int argc, char** argv) {
  QApplication a(argc, argv);
  a.setApplicationName("visualizer");

  MainWindow window;
  window.move(300, 100);
  if (argc == 3) window.resize(atoi(argv[1]), atoi(argv[2]));
  window.resize(800, 800);

  window.show();

  return a.exec();
  return 1;
}
