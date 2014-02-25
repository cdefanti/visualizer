#ifndef TURING_H
#define TURING_H

#include <random>
#include <ctime>
#include <string>

class Turing 
{
public :
	Turing();
    Turing(const int acts[5], const int inhibs[5], const double smalls[5], const int w[5], const int syms[5], const int resW, const int resH);

	~Turing() {}

	void iterate();
	double ** GetArray();
	double GetPixel(int x, int y);
	void AbsMatrixSubtract(double **pos, double **neg, double **dest, int x, int y);

private :
	static const int scales, varrad, blurnum;
	static const int aDef[5], iDef[5], wDef[5], sDef[5];
	static const double saDef[5];

	int *activators, *inhibitors, *weights, *symmetries, resWidth, resHeight;
	double *smallAmounts;
	double **pattern, ***activatorM, ***inhibitorM, ***variationM, ***aiDiffM, **dummy;

	void InitTuring(const int acts[5], const int inhibs[5], const double smalls[5], const int w[5], const int syms[5], const int resW, const int resH);

	void Activator(), Activator(int sn);
	void RActivator(), RActivator(int sn);
	void Inhibitor(), Inhibitor(int sn);
	void RInhibitor(), RInhibitor(int sn);
	void Variation(), Variation(int sn);
	void AIDiff(), AIDiff(int sn);
	void UpdatePixels();
	void Normalize();

	void SetA(int s);
	void SetI(int s);
	void SetV(int s);
	void RAvgM(double ***list, int s);

	double GetMVal(double** mat, int x, int y);

	
	void AvgH(int r, double **source, double **dest);
	void AvgV(int r, double **source, double **dest);
};

#endif