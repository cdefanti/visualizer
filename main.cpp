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

// Custom Headers
#include "glFunc.h"
#include "Turing.h"

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <random>
#include <ctime>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief main Entry function for the program. Calls all other functions to get
 * program running.
 *
 * @param argc Number of arguments input to program
 * @param argv Arguments input to program
 * @return Status of program termination.
 */
/*
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
*/

int rw = 600;
int rh = 600;



int main(int argc, char** argv)
{
    std::srand((unsigned int)time(NULL));
    Turing *testr = new Turing();
    Turing *testg = new Turing();
    Turing *testb = new Turing();
    sf::Uint8 *pixels = new sf::Uint8[rw*rh*4];
    // create the window
    sf::RenderWindow window(sf::VideoMode(rw, rh), "My window");

    //run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // create a quad


        sf::VertexArray quad(sf::Quads, 4);
        sf::Texture texture;


        texture.create(rw, rh);
        sf::Sprite sprite(texture);

        testr->iterate();
        testg->iterate();
        testb->iterate();

        for(int i = 0; i < rw ; i++){
            for(int j = 0; j < rh; j++){
                pixels[4*(i*rh+j)] = ((int)(testb->GetPixel(i,j)*255)+(int)(testg->GetPixel(i,j)*255))/2;
                pixels[4*(i*rh+j)+1] = ((int)(testr->GetPixel(i,j)*255)+(int)(testb->GetPixel(i,j)*255))/2;
                pixels[4*(i*rh+j)+2] = ((int)(testr->GetPixel(i,j)*255)+(int)(testg->GetPixel(i,j)*255))/2;
                pixels[4*(i*rh+j)+3] = 255;
            }
        }

        texture.update(pixels);

        window.draw(sprite);

        // end the current frame
       window.display();
    }
    free(pixels);
    //Keeps terminal from closing after showing results in Windows
    //std::cout<<"\n\nPress ENTER to exit the Matrix";
    //std::cin.ignore(std::cin.rdbuf()->in_avail()+1);
    return 0;
}
