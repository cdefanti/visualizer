// STD Lib Headers
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "Turing.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
        // create a quad
		int rw = 640;
		int rh = 360;
		Turing *test = new Turing();
		test->iterate();

		int i = test->GetPixel(0,0);

    //Keeps terminal from closing after showing results in Windows
	std::cout<<"\n\nPress ENTER to exit the Matrix";
	std::cin.ignore(std::cin.rdbuf()->in_avail()+1);
	return 0;
}
