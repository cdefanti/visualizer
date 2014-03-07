#include "Turing.h"
#include <iostream>



Turing::Turing(){
	InitTuring(aDef, iDef, saDef, wDef, sDef, 600,600);
}

Turing::Turing(const int *acts, const int *inhibs, const double *smalls, const int *w, const int *syms, const int resW, const int resH){
	InitTuring(acts, inhibs, smalls, w, syms, resW, resH);
}
    
void Turing::InitTuring(const int *acts, const int *inhibs, const double *smalls, const int *w, const int *syms, const int resW, const int resH){
	activators = (int*)malloc(scales*sizeof(int));
	inhibitors = (int*)malloc(scales*sizeof(int));
	weights = (int*)malloc(scales*sizeof(int));
	symmetries = (int*)malloc(scales*sizeof(int));
	smallAmounts = (double*)malloc(scales*sizeof(double));
	
	//Define main variables
	for(int i = 0; i < scales; i++){
		activators[i] = acts[i];
		inhibitors[i] = inhibs[i];
		smallAmounts[i] = smalls[i];
		weights[i] = w[i];
		symmetries[i] = syms[i];
	}

	resWidth = resW;
	resHeight = resH;

	//Setting array sizes
	pattern = (double**)malloc(resWidth*sizeof(double*));

	activatorM = (double***)malloc(scales*sizeof(double**));
	inhibitorM = (double***)malloc(scales*sizeof(double**));
	variationM = (double***)malloc(scales*sizeof(double**));
	aiDiffM = (double***)malloc(scales*sizeof(double**));

	dummy = (double**)malloc(resWidth*sizeof(double*));

	for(int i = 0; i < scales; i ++){
		activatorM[i] = (double**)malloc(resWidth*sizeof(double*));
		inhibitorM[i] = (double**)malloc(resWidth*sizeof(double*));
		variationM[i] = (double**)malloc(resWidth*sizeof(double*));
		aiDiffM[i] = (double**)malloc(resWidth*sizeof(double*));
	}
	for(int i = 0; i < resWidth; i++){
		pattern[i] = (double*)malloc(resHeight*sizeof(double));
		dummy[i] = (double*)malloc(resHeight*sizeof(double));
		for(int k = 0; k < scales; k ++){
			activatorM[k][i] = (double*)malloc(resHeight*sizeof(double));
			inhibitorM[k][i] = (double*)malloc(resHeight*sizeof(double));
			variationM[k][i] = (double*)malloc(resHeight*sizeof(double));
			aiDiffM[k][i] = (double*)malloc(resHeight*sizeof(double));
		}
	}
	
	//Initial randomization of main array
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			pattern[i][j] = (double)rand()/RAND_MAX;
		}
	}
}

void Turing::iterate(){
	Activator();
    RActivator();
	Inhibitor();
    RInhibitor();
	AIDiff();
	Variation();
	UpdatePixels();
	Normalize();
}

double ** Turing::GetArray(){
	return pattern;
}

double Turing::GetPixel(int x, int y){
	return GetMVal(pattern, x, y);
}

double Turing::GetMVal(double **mat, int x, int y){
	if(x >= resWidth || y >= resHeight)
		return GetMVal(mat, x%resWidth, y%resHeight);
	if(x < 0)
		return GetMVal(mat, x+(abs(x/resWidth)+1)*resWidth, y);
	if(y < 0)
		return GetMVal(mat, x, y+(abs(y/resHeight)+1)*resHeight);
	//std::cout<< x << " " << y << std::endl;
	return mat[x][y];
}

void Turing::Activator(){
	for(int i = 0; i < scales; i++){
		Activator(i);
	}
}

void Turing::Activator(int sn){
	SetA(sn);
}

void Turing::RActivator(){
	for(int i = 0; i < scales; i++){
		RActivator(i);
	}
}

void Turing::RActivator(int sn){
	RAvgM(activatorM, sn);
}

void Turing::Inhibitor(){
	for(int i = 0; i < scales; i++){
		Inhibitor(i);
	}
}

void Turing::Inhibitor(int sn){
	SetI(sn);
}

void Turing::RInhibitor(){
	for(int i = 0; i < scales; i++){
		RInhibitor(i);
	}
}

void Turing::RInhibitor(int sn){
	RAvgM(inhibitorM, sn);
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
	AbsMatrixSubtract(activatorM[sn], inhibitorM[sn], aiDiffM[sn], resWidth, resHeight);
}

void Turing::UpdatePixels(){
	//Go through every pixel
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
            int bestv = 0;

			//Find scale with smallest variation
            for(int k = 1; k < scales; k++){
                if(GetMVal(variationM[k],i,j) < GetMVal(variationM[bestv],i,j))
                {
					bestv = k;
                }
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
	double min = GetPixel(0,0);
	double max = GetPixel(0,0);

	//Find min and max values over pattern array
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			if(pattern[i][j] < min)
				min = GetPixel(i,j);
			else
				if(pattern[i][j] > max)
					max = GetPixel(i,j);
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
	AvgH(activators[s], pattern, dummy);
	AvgV(activators[s], dummy, activatorM[s]);
	for(int i = 0; i < blurnum-1; i++){
		AvgH(activators[s], activatorM[s], dummy);
		AvgV(activators[s], dummy, activatorM[s]);
	}
}

void Turing::SetI(int s){
	//Sets the scale s inhibitor
	AvgH(inhibitors[s], pattern, dummy);
	AvgV(inhibitors[s], dummy, inhibitorM[s]);
	for(int i = 0; i < blurnum-1; i++){
		AvgH(inhibitors[s], inhibitorM[s], dummy);
		AvgV(inhibitors[s], dummy, inhibitorM[s]);
	}
}

void Turing::SetV(int s){
	//Sets the scale s variation
	AvgH(varrad, aiDiffM[s], dummy);
	AvgV(varrad, dummy, variationM[s]);
	for(int i = 0; i < blurnum-1; i++){
		AvgH(varrad, variationM[s], dummy);
		AvgV(varrad, dummy, variationM[s]);
	}
}

void Turing::RAvgM(double ***list, int s){
	//Symmetrizes s activator
    double theta = (2 * M_PI)/symmetries[s];
	for(int i = 0; i < resWidth; i++){
		for(int j = 0; j < resHeight; j++){
			double total = GetMVal(list[s], i, j);
			for(int r = 1; r < symmetries[s]; r++){
				int x = i-resWidth/2;
				int y = resHeight/2-j;
				double rad = sqrt((double)x*x+(double)y*y);
                double phi = atan2((double)y,(double)x);
				total += GetMVal(list[s], (int)(rad*cos(phi+r*theta))+resWidth/2, resHeight/2-(int)(rad*sin(phi+r*theta)));
			}
			list[s][i][j] = total/symmetries[s];
		}
	}
	//for(int i = 0; i < resWidth; i++){
	//	for(int j = 0; j < resHeight; j++){
	//		list[s][i][j] = GetMVal(dummy, i, j);
	//	}
	//}
}

void Turing::AbsMatrixSubtract(double **pos, double **neg, double **dest, int x, int y){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
            dest[i][j] = fabs(GetMVal(pos,i,j) - GetMVal(neg,i,j));
		}
	}
}

void Turing::AvgH(int r, double **source, double **dest){
	for(int i = 0; i < resWidth; i++){
		// Process entire window for first pixel
		double total = GetMVal(source,i,-r);
		for (int y = -r+1; y <= r; y++)
			total += GetMVal(source,i,y);
		dest[i][0] = total / (r * 2 + 1);
		// Subsequent pixels just update window total
		for(int j = 0; j < resHeight; j++){
			// Subtract pixel leaving window
			total -= GetMVal(source,i,j-r);

			// Add pixel entering window
			total += GetMVal(source,i,j+r);

			dest[i][j] = total/(r*2 + 1);
		}
	}
}

void Turing::AvgV(int r, double **source, double **dest){
	for(int j = 0; j < resHeight; j++){
		// Process entire window for first pixel
		double total = GetMVal(source,-r,j);
		for (int x = -r+1; x <= r; x++)
			total += GetMVal(source,x,j);
		dest[0][j] = total / (r * 2 + 1);

		// Subsequent pixels just update window total
		for(int i = 0; i < resWidth; i++){
			// Subtract pixel leaving window
			total -= GetMVal(source,i-r,j);

			// Add pixel entering window
			total += GetMVal(source,i+r,j);

			dest[i][j] = total/(r*2 + 1);
		}
	}
}
