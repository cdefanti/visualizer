#include "glFunc.h"

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
  std::cerr << "vertex shader log:\n";
  printShaderLog(fragShader);

  // And we're done! Return the program object
  return shaderProgram;
}

void reshape(int w, int h) {
}

void render() {
}

void initShaders() {
}

void initGL() {
}
