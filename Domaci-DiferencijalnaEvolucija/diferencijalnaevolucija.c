#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define F 0.8
#define CR 0.9
#define Dimension 6
#define N 20
#define R0 15
#define XMIN -10
#define XMAX  10
#define PopulationSize  60
#define M_PI 3.14159265358979323846
double S[] = { 2.424595205726587e-01, 1.737226395065819e-01, 1.315612759386036e-01,
	1.022985539042393e-01, 7.905975891960761e-02, 5.717509542148174e-02,
	3.155886625106896e-02, -6.242228581847679e-03, -6.565183775481365e-02,
	-8.482380513926287e-02, -1.828677714588237e-02, 3.632382803076845e-02,
	7.654845872485493e-02, 1.152250132891757e-01, 1.631742367154961e-01,
	2.358469152696193e-01, 3.650430801728451e-01, 5.816044173713664e-01,
	5.827732223753571e-01, 3.686942505423780e-01 };
double xoptimal[Dimension] = { 0 };
double optvalueoptimal = -1;
double x[PopulationSize][Dimension];
double y[PopulationSize][Dimension];
double optvalue[PopulationSize] = { 0 };
void get_xy(int i, double *x, double*y) {
	*x = R0 * cos(2 * M_PI * i / N);
	*y = R0 * sin(2 * M_PI * i / N);
}
double calculate_signal(double xi, double yi, double xk, double yk, double Ak) {
	double rk = sqrt(pow(xi - xk, 2) + pow(yi - yk, 2));
	return Ak / rk;
}
int check_coords(double *x) {
	return (sqrt(pow(x[0], 2) + pow(x[1], 2)) < R0) && (sqrt(pow(x[2], 2) + pow(x[3], 2)) < R0);
}

double optfunction(double *x) {
	double fopt = 0;
	if (check_coords(x) == 1) {
		for (int i = 0; i < N; i++) {
			double xi, yi; 
			get_xy(i,&xi,&yi);
			double signal = 0;
			double xk= x[0], yk = x[1];
			double Ak = x[4];
			signal += calculate_signal(xi,yi, xk,yk, Ak);
			xk = x[2]; 
			yk = x[3];
			Ak = x[5];
			signal += calculate_signal(xi, yi, xk, yk, Ak);
			signal -= S[i];
			signal = pow(signal, 2);
			fopt += signal;
		}
		return fopt;
	}
	return 100.0;
}

void randomizex(double x[PopulationSize][Dimension]) {
	for (int j = 0; j < PopulationSize; j++) {
		for (int i = 0; i < Dimension; i++) {
			x[j][i] = (double)(rand() / (RAND_MAX / 20.0 + 1.0)) - 10.0;
			
		}
	}
}


void selection(int i, double z[Dimension], double x[PopulationSize][Dimension]) {
	int a, b, c;
	a = (int)(rand() / (RAND_MAX / PopulationSize + 1));
	while (a == i) a = (int)(rand() / (RAND_MAX / PopulationSize + 1));
	b = (int)(rand() / (RAND_MAX / PopulationSize + 1));
	while (b == i || b == a) b = (int)(rand() / (RAND_MAX / PopulationSize + 1));
	c = (int)(rand() / (RAND_MAX / PopulationSize + 1));
	while (c == i || c == a || c == b) c = (int)(rand() / (RAND_MAX / PopulationSize + 1));
	for (int j=0;j<Dimension;j++)
	z[j] = x[a][j] + F * (x[b][j] - x[c][j]);
}
void crossover(int i, double z[Dimension], double x[PopulationSize][Dimension],double y[PopulationSize][Dimension]) {
	int R = (int)(rand() / (RAND_MAX / Dimension +1));
	double r[Dimension] = {0.0};
	for (int j = 0; j < Dimension; j++){
	r[j]= (double)(rand() / (RAND_MAX / 1.0 + 1.0));
	if (r[j] < CR || j == R) y[i][j] = z[j];
	else y[i][j] = x[i][j];
	}
}


void main() {
	randomizex(x);
	do {
		for (int i = 0; i < PopulationSize; i++) {
			double z[Dimension];
			selection(i, z, x);
			crossover(i, z, x, y);

			double fyi = optfunction(y[i]);
			double fxi = optfunction(x[i]);
			if (fyi < fxi) {
				for (int j = 0; j < Dimension; j++)
					x[i][j] = y[i][j];
			}
			double minimum = optfunction(x[i]);
			if (optvalueoptimal > minimum || optvalueoptimal == -1) {
				optvalueoptimal = minimum;
				for (int j = 0; j < Dimension; j++)
					xoptimal[j] = x[i][j];
			}
			if (optvalueoptimal <= 1e-14)break;
		}
	} while (optvalueoptimal > 1e-14);
	printf("x=(");
	for (int i = 0; i < Dimension; i++) {
		if (i != Dimension - 1)printf("%f,", xoptimal[i]);
		else printf("%f)\n", xoptimal[i]);
	}
	printf("Minimal value of optimizing function is %e\n", optvalueoptimal);
}

