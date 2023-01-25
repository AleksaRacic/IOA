#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUMCORDS 3
#define w 0.729
#define c1 1.494
#define c2 1.494
#define Vmax 1
#define MAXITERATIONS 100000
#define PopulationSize 60
#define Slength 6

double A[NUMCORDS]= { 1,4,0 };
double B[NUMCORDS] = { 3,2,0 };
double C[NUMCORDS] = { 2,7,1 };
double D[NUMCORDS] = { 6,3,3 };
double E[NUMCORDS] = { 7,6,5 };
double F[NUMCORDS] = { 5,7,4 };

double gbest[Slength] = { 0 };
double optimal_path = -1;
double pbest[PopulationSize][Slength] = { 0 };
double S[PopulationSize][Slength] = { 0 };
double Vn[PopulationSize][Slength] = { 0 };
double calc_distance(double* X, double* S, int offset) {
	double distance = 0;
	for (int i = 0; i < NUMCORDS; i++) {
		distance += pow((X[i] - S[i + offset]), 2);
	}
	distance = sqrt(distance);
	return distance;
}
double opt_function(double *S) {
	double path = 0;
	path += calc_distance(A, S, 0);
	path += calc_distance(B, S, 0);
	path += calc_distance(C, S, 0);

	path += calc_distance(D, S, 3);
	path += calc_distance(E, S, 3);
	path += calc_distance(F, S, 3);

	path += calc_distance(S, S, 3);

	return path;

}

void calculate_speed(double* Vn, double* pbest, double* gbest, double* Xn , double  Vn1[Slength]) {
	//double  Vn1[NUMCORDS] = { 0 };
	double firstrandom = (double)rand()/RAND_MAX;
	double secondrandom = (double) rand() / RAND_MAX;
	for (int i = 0; i < Slength; i++) {
		// w*Vn-1
		Vn1[i] += w * Vn[i];
		// c1*rand()*(pbest-Xn-1)
		Vn1[i] += c1 * firstrandom * (pbest[i] - Xn[i]);
		// c2*rand()*(gbest-Xn-1)
		Vn1[i] += c2 * secondrandom * (gbest[i] - Xn[i]);
		if (Vn1[i] > Vmax) Vn1[i] = Vmax;
		else if (Vn1[i] < -Vmax)Vn1[i] = -Vmax;
		Vn[i] = Vn1[i];
	}
}

void calculate_newposition(double* Xn, double* Vn, double Xn1[Slength]) {
	for (int i = 0; i < Slength; i++)
		Xn1[i] = Xn[i] + Vn[i];
}
void init_S() {
	for (int i = 0; i < PopulationSize; i++) {
		for (int j = 0; j < Slength; j++) {
			if (j == 2 || j == 5) {
				//z opseg 0-4
				S[i][j] = (double)(rand() / (RAND_MAX / 4.0 + 1));

			}
			else{
				//x,y opseg 0-10
				S[i][j] = (double)(rand() / (RAND_MAX / 10.0 + 1));
			}
			pbest[i][j] = S[i][j];
			Vn[i][j]= (double)rand() / RAND_MAX;
		}
	}
}
void main() {
	int iterations = 0;
	int notFound = 1;
	init_S();
	while (notFound) {
		for (int i = 0; i < PopulationSize; i++) {
			double  Vn1[Slength] = { 0 };
			calculate_speed(Vn[i], pbest[i], gbest, S[i], Vn1);
			double  Xn1[Slength] = { 0 };
			double  XOptimal[Slength] = { 0 };
			calculate_newposition(S[i], Vn1, Xn1);
			double path=opt_function(S[i]);
			double newpath=opt_function(Xn1);
			for (int j = 0; j < Slength; j++) {
				S[i][j] = Xn1[j];
			}
			if (newpath < path) {
				for (int j = 0; j < Slength; j++) {
					pbest[i][j] = Xn1[j];
					XOptimal[j] = Xn1[j];
				}
				
			}
			else {
				for (int j = 0; j < Slength; j++) {
					XOptimal[j] = pbest[i][j];
				}
			}
			double optlocal = path > newpath ? newpath : path;
			if (optimal_path == -1) {
				for (int j = 0; j < Slength; j++) {
					gbest[j] = XOptimal[j];
				}
				optimal_path = opt_function(gbest);
			}
			else if (optimal_path > optlocal) {
				int found = 1;

				for (int j = 0; j < Slength; j++) {
					double diff= fabs(gbest[j] - XOptimal[j]);
					if (diff > 1e-3) {
						found = 0;
					}
					gbest[j] = XOptimal[j];
				}
				
				optimal_path = newpath;
				if (found) { notFound = 0; 
				break;
				}
			}
			if (!notFound) break;
		}
		iterations++;
		if (iterations > MAXITERATIONS)break;
	}
	for (int i = 0; i < Slength; i++) {
		if (i != Slength - 1)printf("%lf, ", gbest[i]);
		else printf("%lf)\n", gbest[i]);
	}
	printf("Minimal value of optimizing function is %lf\n", optimal_path);
}