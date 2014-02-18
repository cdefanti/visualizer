#include "glFunc.h"
#include <time.h>
#include <SFML/Audio.hpp>
#include <string>

/* 
 * shaders: a list of all GLuints that link to a shader
 */
std::vector<GLuint> shaders;

/*
 * t: current time
 */
float t;

/*
 * last_t: last time
 */
float last_t;

/*
 * tu: uniform position for t
 */
static GLuint tu;

/*
 * sb: sound buffer for program
 */
sf::SoundBuffer *sb;

/*
 * sound_t: time of current sound
 */
float sound_t;

void printShaderLog(GLuint obj) {
  GLsizei maxLength, length;
  glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  GLchar* log = (GLchar*)malloc(maxLength);
  glGetShaderInfoLog(obj, maxLength, &length, log);
  std::cerr << log << std::endl;
  free(log);
}

void printProgramLog(GLuint obj) {
  GLsizei maxLength, length;
  glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  GLchar* log = (GLchar*)malloc(maxLength);
  glGetProgramInfoLog(obj, maxLength, &length, log);
  std::cerr << log << std::endl;
  free(log);
}

GLint initShader(std::string &vertFileName, std::string &fragFileName) {
  GLint shaderProgram = glCreateProgram();

  // First, verify that the shader filenames are valid
  std::fstream vertFile(vertFileName.c_str());
  std::fstream fragFile(fragFileName.c_str());
  if (!vertFile)
    std::cerr << "Invalid vertex shader file: " << vertFileName << std::endl;
  if (!fragFile)
    std::cerr << "Invalid fragment shader file: " << fragFileName << std::endl;

  // Next, get the shader contents
  std::string vertSourceStr, fragSourceStr;
  std::getline(vertFile, vertSourceStr, '\0');
  std::getline(fragFile, fragSourceStr, '\0');
  const char* vertSource = vertSourceStr.c_str();
  const char* fragSource = fragSourceStr.c_str();

  // Now we can set up the shader program objects
  // First compile
  GLuint vertShader, fragShader;
  vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertSource, NULL);
  glCompileShader(vertShader);
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragSource, NULL);
  glCompileShader(fragShader);

  // Bind the sub-programs to main shader program
  glAttachShader(shaderProgram, vertShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);

  // Attach uniforms
  glGetUniformLocation(shaderProgram, "t");

  // Print out debugging info
  std::cerr << "shader program log:\n";
  printProgramLog(shaderProgram);
  std::cerr << "vertex shader log:\n";
  printShaderLog(vertShader);
  std::cerr << "fragment shader log:\n";
  printShaderLog(fragShader);

  // And we're done! Return the program object
  return shaderProgram;
}

void reshape(int w, int h) {
}

void renderGrid(float minx, float maxx, float miny, float maxy, float dx, float dy) {
  glUseProgram(shaders[0]);
  for(float u = minx; u < maxx; u += dx) {
    glBegin(GL_TRIANGLE_STRIP);
    for(float v = miny; v <= maxy; v += dy) {
      glVertex2f(u, v);
      glVertex2f(u+1, v);
    }
    glEnd();
  }
  glUseProgram(0);
}

void render() {
  // get new time
  t = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
  float dt = t - last_t;
  last_t = t;
  sound_t += dt;
  glUseProgram(shaders[0]);
  glUniform1f(tu, t);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  renderGrid(-1, 1, -1, 1, 0.01, 0.01);
  glutSwapBuffers();
}

void initShaders() {
  std::string vs = "shaders/test.vs.glsl";
  std::string fs = "shaders/test.fs.glsl";
  shaders.push_back(initShader(vs, fs));
}

void initGL() {
  t = 0;
  last_t = 0;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, 1, 10);
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0, 0, -5.f);
  shaders.clear();
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glDisable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  initShaders();
  initSoundBuffer();
}
