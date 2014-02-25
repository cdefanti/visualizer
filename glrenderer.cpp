#include "glrenderer.h"

void glrenderer::printShaderLog(GLuint obj) {
  GLsizei maxLength, length;
  glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  GLchar* log = (GLchar*)malloc(maxLength);
  glGetShaderInfoLog(obj, maxLength, &length, log);
  std::cerr << log << std::endl;
  free(log);
}

void glrenderer::printProgramLog(GLuint obj) {
  GLsizei maxLength, length;
  glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  GLchar* log = (GLchar*)malloc(maxLength);
  glGetProgramInfoLog(obj, maxLength, &length, log);
  std::cerr << log << std::endl;
  free(log);
}

GLint glrenderer::initShader(std::string &vertFileName, std::string &fragFileName) {
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

void glrenderer::resizeGL(int width, int height) {
    height = (height < 1) ? 1 : height;
    width = (width < 1) ? 1 : width;

    glViewport(0, 0, width, height);
    dim_ = glm::vec2(width, height);

    updateGL();
}

void glrenderer::renderGrid(float minx, float maxx, float miny, float maxy, float dx, float dy) {
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

void glrenderer::renderFFT(double *dataAbs) {
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < buffersize_; i++) {
    double x = -1 + 2.f / buffersize_ * i;
    double y = dataAbs[i] / (65536);
    glVertex2d(x, y);
  }
  glEnd();
}

void glrenderer::render() {
  //glUseProgram(shaders[0]);
  //glUniform1f(tu, t);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  double *dataAbs = soundstream_->getFFTAbs();
  renderFFT(dataAbs);
  //renderGrid(-1, 1, -1, 1, 0.01, 0.01);
}

void glrenderer::initShaders() {
  std::string vs = "shaders/test.vs.glsl";
  std::string fs = "shaders/test.fs.glsl";
  shaders.push_back(initShader(vs, fs));
}

void glrenderer::initSoundStream() {
  soundstream_ = new sfe::SequentialSoundStreamer(buffersize_);
}

void glrenderer::loadSoundFile(const std::string &filename)
{
    soundstream_->stop();
    sf::SoundBuffer buffer;
    buffer.loadFromFile(filename);
    soundstream_->load(buffer);
    soundstream_->play();
}

void glrenderer::initializeGL() {
  connect(&timer_, SIGNAL(timeout()), this, SLOT(updateGL()));
  timer_.setInterval(0);
  timer_.start();
  etimer_.start();
  t_ = 0;
  last_t_ = 0;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, 0, 2, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0, 0, -5.f);
  shaders.clear();
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glDisable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  //initShaders();
  initSoundStream();
}

void glrenderer::paintGL()
{
    render();
}

void glrenderer::updateGL()
{
    // get new time
    float t = (float)etimer_.elapsed() / 1000.f;
    float dt = t_ - last_t_;
    last_t_ = t_;
    sound_t_ += dt;
    update();
}
