#include "glFunc.h"

/* 
 * shaders: a list of all GLuints that link to a shader
 */
std::vector<GLuint> shaders;

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

void renderGrid(int w, int h) {
  // (w - 1) * (h - 1) quads, 4 vertices per quad
  int num_verts = (w - 1) * 6;
  GLfloat verts[num_verts * 3];
  GLfloat norms[num_verts * 3];
  glEnableClientState(GL_VERTEX_ARRAY);
  glUseProgram(shaders[0]);
  for (int i = 0; i < h - 1; i++)
  {
    for (int j = 0; j < w - 1; j++)
    {
      for (int k = 0; k < 18; k += 6)
      {
        norms[6 * j + k] = (((k % 3) == 1) ? 1 : 0);
      }
      for (int k = 0; k < 18; k += 6)
      {
        verts[6 * j + k] = i + ((j == 2) ? 1 : 0);
        verts[6 * j + k + 1] = j + ((j == 2) ? 1 : 0);
        verts[6 * j + k + 2] = 0;
        verts[6 * j + k + 3] = i + ((j > 0) ? 1 : 0);
        verts[6 * j + k + 4] = j + ((j < 2) ? 1 : 0);
        verts[6 * j + k + 5] = 0;
      }
    }
    glVertexPointer(3, GL_FLOAT, 0, &verts[0]);
    glNormalPointer(GL_FLOAT, 0, &norms[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, num_verts);
  }
  glUseProgram(0);
  glDisableClientState(GL_VERTEX_ARRAY);
  /*
  glColor3f(0, 1, 0);
  for(float u = 0; u < h; u++) {
    glBegin(GL_TRIANGLE_STRIP);
    for(float v = 0; v <= w; v++) {
      glVertex2f(u, v);
      glVertex2f(u+1, v);
    }
    glEnd();
  }
  */
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  renderGrid(10, 10);
  glutSwapBuffers();
}

void initShaders() {
  std::string vs = "shaders/test.vs.glsl";
  std::string fs = "shaders/test.fs.glsl";
  shaders.push_back(initShader(vs, fs));
}

void initGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1, 1, 50);
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0, 0, -40.f);
  shaders.clear();
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glDisable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  initShaders();
}
