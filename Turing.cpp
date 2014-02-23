#include "Turing.h"


int ac[scales] = {100, 20, 10, 5, 1},
	in[scales] = {200, 40, 20, 10, 2},
	ws[scales] = {1,1,1,1,1},
	sy[scales] = {3,2,2,2,2};
double sa[scales] = {.05, .04, .03, .02, .01};

Turing::Turing(){
	Turing(ac, in, sa, ws, sy, 640, 360);
}
    
Turing::Turing(int acts[scales], int inhibs[scales], double smalls[scales], int w[scales], int syms[scales], int resW, int resH){
	//Define main variables
	std::copy(acts, acts+scales, activators);
	std::copy(inhibs, inhibs+scales, inhibitors);
	std::copy(w, w+scales, weights);
	std::copy(syms, syms+scales, symmetries);
	std::copy(smalls, smalls+scales, smallAmounts);

	//Setting array sizes
	pattern = (double**)malloc(resWidth*sizeof(double*));
	for(int i = 0; i < scales; i ++){
		activatorM[i] = (double**)malloc(resWidth*sizeof(double*));
		inhibitorM[i] = (double**)malloc(resWidth*sizeof(double*));
		variationM[i] = (double**)malloc(resWidth*sizeof(double*));
		aiDiffM[i] = (double**)malloc(resWidth*sizeof(double*));
	}
	for(int i = 0; i < resWidth; i++){
		pattern[i] = (double*)malloc(resHeight*sizeof(double));
		for(int k = 0; k < scales; k ++){
			activatorM[k][i] = (double*)malloc(resHeight*sizeof(double));
			inhibitorM[k][i] = (double*)malloc(resHeight*sizeof(double));
			variationM[k][i] = (double*)malloc(resHeight*sizeof(double));
			aiDiffM[k][i] = (double*)malloc(resHeight*sizeof(double));
		}
	}

	//Initial randomization of main array
	std::srand(time(NULL)); 
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			pattern[i][j] = (double)rand()/RAND_MAX;
		}
	}
}

double ** Turing::iterate(){
	Activator();
	Inhibitor();
	AIDiff();
	Variation();
	UpdatePixels();
	return pattern;
}

void Turing::Activator(){
	for(int i = 0; i < scales; i++){
		Activator(i);
	}
}

void Turing::Activator(int sn){
	SetA(sn);
}

void Turing::Inhibitor(){
	for(int i = 0; i < scales; i++){
		Inhibitor(i);
	}
}

void Turing::Inhibitor(int sn){
	SetI(sn);
}

void Turing::Variation(){
	for(int i = 0; i < scales; i++){
		Variation(i);
	}
}

void Turing::Variation(int sn){
	SetV(sn);
}

void Turing::AIDiff(){
	for(int i = 0; i < scales; i++){
		AIDiff(i);
	}
}

void Turing::AIDiff(int sn){
	DMatrixSubtract(activatorM[sn], inhibitorM[sn], aiDiffM[sn], resWidth, resHeight);
}

void Turing::UpdatePixels(){
	//Go through every pixel
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			int bestv = 0;

			//Find scale with smallest variation
			for(int k = 1; k < scales; k++){
				if(variationM[k][i][j] > variationM[bestv][i][j])
					bestv = k;
			}

			//Update each pixel
			if(activatorM[bestv][i][j] > inhibitorM[bestv][i][j])
				pattern[i][j] += smallAmounts[bestv];
			else 
				pattern[i][j] -= smallAmounts[bestv];
		}
	}
}

void Turing::Normalize(){
	double min = pattern[0][0];
	double max = pattern[0][0];

	//Find min and max values over pattern array
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			if(pattern[i][j] < min)
				min = pattern[i][j];
			else
				if(pattern[i][j] > max)
					max = pattern[i][j];
		}
	}

	//Normalize each pixel of the pattern
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			pattern[i][j] = (pattern[i][j] - min)/(max - min);
		}
	}
}

void Turing::SetA(int s){
	//Sets the scale s activator
	AvgH(activators[s], pattern, activatorM[s]);
	AvgV(activators[s], pattern, activatorM[s]);
}

void Turing::SetI(int s){
	//Sets the scale s inhibitor
	AvgH(inhibitors[s], pattern, inhibitorM[s]);
	AvgV(inhibitors[s], pattern, inhibitorM[s]);
}

void Turing::SetV(int s){
	//Sets the scale s variation
	AvgH(varrad, aiDiffM[s], variationM[s]);
	AvgV(varrad, aiDiffM[s], variationM[s]);
}

void Turing::DMatrixSubtract(double **pos, double **neg, double **dest, int x, int y){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			dest[i][j] = pos[i][j] - neg[i][j];
		}
	}
}

void Turing::AvgH(int r, double **source, double **dest){
	for(int i = 0; i < resWidth; i++){
		// Process entire window for first pixel
		double total = source[i][0];
		for (int y = 1; y <= r; y++)
			total += source[i][y];
		dest[i][0] = total / (r * 2 + 1);

		// Subsequent pixels just update window total
		for(int j = 0; j < resHeight; j++){
			// Subtract pixel leaving window
			if(j-r >= 0)
				total -= source[i][j - r];

			// Add pixel entering window
			if(j+r < resHeight)
				total += source[i][j + r];

			dest[i][j] = total/(r*2 + 1);
		}
	}
}

void Turing::AvgV(int r, double **source, double **dest){
	for(int j = 0; j < resWidth; j++){
		// Process entire window for first pixel
		double total = source[0][j];
		for (int x = 1; x <= r; x++)
			total += source[x][j];
		dest[0][j] = total / (r * 2 + 1);

		// Subsequent pixels just update window total
		for(int i = 0; i < resHeight; i++){
			// Subtract pixel leaving window
			if(i-r >= 0)
				total -= source[i-r][j];

			// Add pixel entering window
			if(i+r < resHeight)
				total += source[i+r][j];

			dest[i][j] = total/(r*2 + 1);
		}
	}
}