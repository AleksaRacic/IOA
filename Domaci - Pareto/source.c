#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define I 1.0 //A
#define MAXNUMITERATIONS 1000000
#define delta 0.01 //m
#define tau 58.0*1000000
#define pi 3.14159265358979323846
#define MINA 0.01
#define MAXA 0.05
#define MINB 0.1
#define MAXB 0.4
#define MINS 0.5*0.000001
#define MAXS 3.0*0.000001

typedef struct X{
double a;
double b;
double S;
}X;

typedef struct Sol {
	double H;
	double R;
}Sol;

X solutionsx[MAXNUMITERATIONS];
int paretoptimalx[MAXNUMITERATIONS] = {0};

Sol solutions[MAXNUMITERATIONS];
Sol paretoptimal[MAXNUMITERATIONS];

unsigned int paretonumber = 0;

void initialize_solutions() {
	for (int i = 0; i < MAXNUMITERATIONS; i++) {
		solutionsx[i].a = (double)rand() / RAND_MAX * ( MAXA - MINA ) + MINA;
		solutionsx[i].b = (double)rand() / RAND_MAX * ( MAXB - MINB) + MINB;
		solutionsx[i].S = (double)rand() / RAND_MAX * (MAXS - MINS) + MINS;
	}
}
double calc_z0(double b) {
	double z0 = b / 2 + delta;
	return z0;
}
double calc_N(double b, double S) {
	double N = b * sqrt(pi / (4.0 * S));
	return N;
}
double calc_magnetic_field_intensity(double a, double b,double S) {
	double z0 = calc_z0(b);
	double N = calc_N(b, S);
	double H = (N * I / (2 * b)) * ((z0 + b / 2) / sqrt(pow(a, 2) + pow(z0 + b / 2, 2)) - (z0 - b / 2) / sqrt(pow(a, 2) + pow(z0 - b / 2, 2)));
	return H;
}

double calc_resistance(double a, double b, double S) {
	double R = (2 * pi * a * b) / (tau * S) * sqrt(pi / (4 * S));
	return R;
}

void savedata() {
	FILE* file;
	file = fopen("data.txt", "w+");
	fprintf(file, "%u\n", paretonumber);
	for (int i = 0; i < paretonumber; i++) {
		if (i != paretonumber - 1)fprintf(file, "%lf;%lf,", paretoptimal[i].H, paretoptimal[i].R);
		else fprintf(file, "%lf;%lf\n", paretoptimal[i].H, paretoptimal[i].R);
	}

	for (int i = 0; i < MAXNUMITERATIONS; i++) {
		if (paretoptimalx[i] == 0) {
			if(i!=MAXNUMITERATIONS-1)fprintf(file, "%lf;%lf,", solutions[i].H, solutions[i].R);
			else fprintf(file, "%lf;%lf", solutions[i].H, solutions[i].R);
		}
	}
	fclose(file);
}

int main() {
	initialize_solutions();
	for (int i = 0; i < MAXNUMITERATIONS; i++) {
		solutions[i].H = calc_magnetic_field_intensity(solutionsx[i].a, solutionsx[i].b, solutionsx[i].S);
		solutions[i].R = calc_resistance(solutionsx[i].a, solutionsx[i].b, solutionsx[i].S);
	}
	for (int i = 0; i < MAXNUMITERATIONS; i++) {
		int ispareto = 1;
		for (int j = 0; j < MAXNUMITERATIONS; j++) {
			if (i == j) continue;
			if ((solutions[j].H > solutions[i].H ) && (solutions[j].R < solutions[i].R)) {
				ispareto = 0;
				break;

			}
			
		}
		if (ispareto == 1) {
			paretoptimal[paretonumber].H = solutions[i].H;
			paretoptimal[paretonumber].R = solutions[i].R;
			paretoptimalx[i] = 1;
			paretonumber++;
		}
		
	}
	savedata();
}