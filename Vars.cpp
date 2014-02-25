#include "Turing.h"

const int Turing::scales = 5;
const int Turing::varrad = 2;
const int Turing::blurnum = 1;

const int Turing::aDef[5] = {100, 64, 16, 4, 1},
	Turing::iDef[5] = {200, 128, 32, 8, 2},
	Turing::wDef[5] = {1,1,1,1,1},
	Turing::sDef[5] = {3,2,2,2,2};
const double Turing::saDef[5] = {.05, .04, .03, .02, .01};