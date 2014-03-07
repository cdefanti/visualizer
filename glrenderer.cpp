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

glm::vec3 glrenderer::HSVtoRGB(float h, float s, float v)
{
    glm::vec3 res;
    int i;
    float f, p, q, t;
    if( s == 0 ) {
        // achromatic (grey)
        res = glm::vec3(v);
        return res;
    }
    h /= M_PI / 3.f;			// sector 0 to 5
    i = floor( h );
    f = h - i;			// factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );
    switch( i ) {
        case 0:
            res.r = v;
            res.g = t;
            res.b = p;
            break;
        case 1:
            res.r = q;
            res.g = v;
            res.b = p;
            break;
        case 2:
            res.r = p;
            res.g = v;
            res.b = t;
            break;
        case 3:
            res.r = p;
            res.g = q;
            res.b = v;
            break;
        case 4:
            res.r = t;
            res.g = p;
            res.b = v;
            break;
        default:		// case 5:
            res.r = v;
            res.g = p;
            res.b = q;
            break;
    }
    return res;
}

void glrenderer::renderToTexture()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    GLenum buffer[1] = {GL_COLOR_ATTACHMENT0_EXT};

    glBindTexture(GL_TEXTURE_1D, soundTex);
    double *dataAbs = soundstream_->getFFTAbs();
    double *dataPhase = soundstream_->getFFTPhase();
    float pixelrow[800 * 3];
    for (int i = 0; i < buffersize_; i++)
    {
        if (i >= 800) break;
        glm::vec3 color = HSVtoRGB(dataPhase[i], 1, dataAbs[i]);
        pixelrow[3 * i] = color.r;
        pixelrow[3 * i + 1] = color.g;
        pixelrow[3 * i + 2] = color.b;
    }
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 800, 0, GL_FLOAT, GL_RGBA, pixelrow);
    glUseProgram(shaders[0]);
    soundTexLoc_ = glGetUniformLocation(shaders[0], "soundTex");
    glUniform1i(soundTexLoc_, 0);
    pixelTexLoc_ = glGetUniformLocation(shaders[0], "pixelsTex");
    glUniform1i(pixelTexLoc_, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, soundTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pixels_[pingpong]);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pixels_[1 - pingpong], 0);

    glDrawBuffers(1, buffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("buffer failed: %d\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0,0,800,800);

    // The fullscreen quad's FBO
    GLuint quad_VertexArrayID;
    glGenVertexArraysAPPLE(1, &quad_VertexArrayID);
    glBindVertexArrayAPPLE(quad_VertexArrayID);

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    GLuint quad_vertexbuffer;
    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,800,800);
    pingpong = 1 - pingpong;
}

void glrenderer::renderFFT(double *dataAbs) {
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glColor3f(0.0, 1.0, 0.0);
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
  if (soundstream_->getStatus() == sf::Sound::Playing)
  {
    //double *dataAbs = soundstream_->getFFTAbs();
    //renderFFT(dataAbs);
    renderToTexture();
  }
  //renderGrid(-1, 1, -1, 1, 0.01, 0.01);
}

void glrenderer::initShaders()
{
  std::string vs = "/Users/connor/visualizer/shaders/soundwave.v.glsl";
  std::string fs = "/Users/connor/visualizer/shaders/soundwave.f.glsl";

  shaders.push_back(initShader(vs, fs));
}

void glrenderer::initBuffers()
{
    // create frame buffers
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    float res[2] = {800, 800};
    /*
    glGenRenderbuffers(1, &dbo);
    glBindRenderbuffer(GL_RENDERBUFFER, dbo);
    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH_COMPONENT,
                          res[0], res[1]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                          GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
                          dbo);
    */
    /*
    vbo = (GLuint*)malloc(scales * 2 * sizeof(GLuint));
    for (int i = 0; i < scales; i++)
    {
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + 2 * i, GL_TEXTURE_RECTANGLE_ARB, vbo[2 * i], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + 2 * i + 1, GL_TEXTURE_RECTANGLE_ARB, vbo[2 * i + 1], 0);
    }
    */
    float pixels[(int)(res[0] * res[1])][3];
    for(int i = 0; i < res[0] * res[1]; i++)
    {
        /*
        pixels[i][0] = ((float)rand())/RAND_MAX;
        pixels[i][1] = ((float)rand())/RAND_MAX;
        pixels[i][2] = ((float)rand())/RAND_MAX;
        */
        pixels[i][0] = 0;
        pixels[i][1] = 0;
        pixels[i][2] = 0;
    }

    for (int i = 0; i < 2; i++)
    {
        glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
        glGenTextures(1, &pixels_[i]);
        glBindTexture(GL_TEXTURE_2D, pixels_[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     res[0], res[1],
                     0, GL_FLOAT, GL_RGB, pixels);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, pixels_[i], 0);
    }

    glGenTextures(1, &soundTex);
    glBindTexture(GL_TEXTURE_1D, soundTex);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, res[0], 0, GL_FLOAT, GL_RGBA, 0);

    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void glrenderer::initSoundStream()
{
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
  pingpong = 0;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, 0, 2, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0, 0, -5.f);
  shaders.clear();
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glDisable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  initShaders();
  initBuffers();
  initSoundStream();
}

void glrenderer::paintGL()
{
    render();
}

void glrenderer::updateGL()
{
    // get new time
    t_ = (float)etimer_.elapsed() / 1000.f;
    float dt = t_ - last_t_;
    last_t_ = t_;
    sound_t_ += dt;
    /*
    // update variance
    for (int i = 0; i < scales; i++)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_RECTANGLE_ARB, fbo);
        glUseProgram(shaders[0]);
        glDrawBuffer(vbo[2 * i + pingpong]);
        glBindTexture(GL_TEXTURE_RECTANGLE_ARB, vbo[2 * i + pingpong]);
        glUseProgram(shaders[0]);
        glDrawBuffer(vbo[2 * i + (1 - pingpong)]);
    }

    pingpong = (1 - pingpong);
    */
    update();
}
