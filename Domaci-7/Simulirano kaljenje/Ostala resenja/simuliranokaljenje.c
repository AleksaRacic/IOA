/*
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define D 64 
#define N 20
#define a 0.95
double T0 =  64 * 1024 * 1024;
int s[] = { 173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571 };
int maxiterations = 100000; 

int xoptimal[D] = {0};
int optvalueoptimal = -1;
int optvalues[N][1000000] = {0};
int average_opt[1000000] = { 0 };
int hmin = 1;
int hmax = 10; 

int optfunction(int *x) {
	int F1 = pow(2, 25);
	int F2 = pow(2, 25);
	for (int i = 0; i < D; i++) {
		if (x[i] == 1) F1 -= s[i];
		else if (x[i] == 2) F2 -= s[i];
	}
	int f = 0;
	if (F1 >= 0 && F2 >= 0) f = F1 + F2;
	else f = pow(2, 26);
	return f;
}

void randomizex(int *x) {
	for (int i = 0; i < D; i++) {
		x[i] = (int)(rand() / (RAND_MAX / 3 + 1));
	
	}
}
void generatenewx(int*x, int i, int *newx) {
	int h = (hmin - hmax) *(i-1) / (maxiterations-1) + hmax;
	int places[D] = { 0 };
	
	for (int i = 0; i < h; i++) {
		int index=(int)( rand() / (RAND_MAX / 64 + 1));
		while(places[index]==1) index = (int)(rand() / (RAND_MAX / 64 + 1));
		places[index] = 1;

		int oldval = x[index];
		int newval= (int)(rand() / (RAND_MAX / 3 + 1));
		while(newval==oldval) newval = (int)(rand() / (RAND_MAX / 3 + 1));
		newx[index] = newval;
	}
}


void savedata() {
	FILE* file=NULL;
	fopen_s(&file, "data.txt", "w+");
	fprintf(file, "xoptimal\n");
	for (int i = 0; i < D; i++) {
			if(i!=D-1)fprintf(file, "%d, ",xoptimal[i]);
			else fprintf(file, "%d\n", xoptimal[i]);
	}
	
	fprintf(file, "optvalueoptimal\n");
	fprintf(file, "%d\n", optvalueoptimal);

	fprintf(file, "optvalues\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < maxiterations * 10; j++) {
			if (j != maxiterations * 10-1)fprintf(file, "%d, ", optvalues[i][j]);
			else fprintf(file, "%d\n", optvalues[i][j]);
		}
	}
	fprintf(file, "average_opt\n");
	for (int i = 0; i < maxiterations*10; i++) {
			if (i!= maxiterations * 10 - 1)fprintf(file, "%d, ", average_opt[i]);
			else fprintf(file, "%d\n", average_opt[i]);
	}
	fclose(file);
}
void copyvalues(int x[], int newx[]) {
	for (int i = 0; i < D; i++)
		x[i] = newx[i];
}
int main() {
	int x[D];
	int optvalue = 0;
	
	int newx[D];
	for (int i = 0; i < N; i++) {
		randomizex(x);
		optvalue = optfunction(x);
		if (optvalueoptimal == -1) {
			optvalueoptimal = optvalue;
			for (int p = 0; p < D; p++)
				xoptimal[p] = x[p];
		}
		int localmin=optvalue;
		for (int j = 0; j < 10; j++) {
			optvalue = optfunction(x);
			double T = T0;
			for (int k = 0; k < maxiterations; k++) {
				copyvalues(newx, x);
				generatenewx(x,k,newx);
				int newoptvalue = optfunction(newx);

				int deltaE = newoptvalue - optvalue;
				if (deltaE < 0) {
					copyvalues(x, newx);
					optvalue = newoptvalue;
				}
				else {

					double p = exp(-deltaE / T);
					double number = (double) rand() /RAND_MAX;
					if (number <= p) {
						copyvalues(x, newx);
						optvalue = newoptvalue;
					}
				
				}
				if (optvalue < optvalueoptimal) {
					optvalueoptimal = optvalue;
					for (int p = 0; p < D; p++)
						xoptimal[p] = x[p];
				
				}
				if (localmin > optvalue) localmin = optvalue;

				optvalues[i][j * maxiterations + k] = localmin;
				average_opt[j * maxiterations + k] += (localmin / N);

				T = a * T;
			
			}
			
		
		}
	
	}
	savedata();
	printf("x=(");
	for (int i = 0; i < D; i++) {
		if (i != D - 1)printf("%d,", xoptimal[i]);
		else printf("%d)\n", xoptimal[i]);
	}
	printf("Minimal value of optimizing function is %d\n", optvalueoptimal);
}

*/