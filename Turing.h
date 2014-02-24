#include <random>
#include <ctime>
#include <string>

const int scales = 5,
		  varrad = 1,
		  blurnum = 3;

class Turing 
{
public :
	Turing();
    Turing(int acts[5], int inhibs[5], double smalls[5], int w[5], int syms[5], int resW, int resH);

	//~Turing() {}

	void iterate();
	double ** GetArray();
	double GetPixel(int x, int y);

	double **pattern;

private :
	int activators[scales], inhibitors[scales], weights[scales], symmetries[scales], resWidth, resHeight;
	double smallAmounts[scales];
	double **activatorM[scales], **inhibitorM[scales], **variationM[scales], **aiDiffM[scales];

	void Activator(), Activator(int sn);
	void Inhibitor(), Inhibitor(int sn);
	void Variation(), Variation(int sn);
	void AIDiff(), AIDiff(int sn);
	void UpdatePixels();
	void Normalize();

	void SetA(int s);
	void SetI(int s);
	void SetV(int s);

	void DMatrixSubtract(double **pos, double **neg, double **dest, int x, int y);
	void AvgH(int r, double **source, double **dest);
	void AvgV(int r, double **source, double **dest);
};