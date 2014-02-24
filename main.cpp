// STD Lib Headers
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <random>
#include <ctime>
#include "Turing.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int rw = 600;
int rh = 600;



int main()
{
	std::srand((unsigned int)time(NULL));
	Turing *testr = new Turing();
	Turing *testg = new Turing();
	//Turing *testb = new Turing();
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
		sf::Uint8 *pixels = new sf::Uint8[rw*rh*4];

		texture.create(rw, rh);
		sf::Sprite sprite(texture);

		testr->iterate();
		testg->iterate();
		//testb->iterate();

		for(int i = 0; i < rw ; i++){
			for(int j = 0; j < rh; j++){
				pixels[4*(i*rh+j)] = (int)(testr->GetPixel(i,j)*255);
				pixels[4*(i*rh+j)+1] = (int)(testg->GetPixel(i,j)*255);
				pixels[4*(i*rh+j)+2] = (int)(testr->GetPixel(i,j)*255)+(int)(testg->GetPixel(i,j)*255);
				pixels[4*(i*rh+j)+3] = 255;
			}
		}

		texture.update(pixels);
			
		window.draw(sprite);

        // end the current frame
       window.display();
    }

    //Keeps terminal from closing after showing results in Windows
	//std::cout<<"\n\nPress ENTER to exit the Matrix";
	//std::cin.ignore(std::cin.rdbuf()->in_avail()+1);
	return 0;
}