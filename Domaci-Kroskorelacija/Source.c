
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define D 31 
#define CROSSMIN  -4
#define CROSSMAX  6
#define AUTOMIN  -18
#define  AUTOMAX  12
#define KCYCL 31
#define N 20
#define a 0.95
#define NUMOFZEROS 15
#define NUMOFONES 15
double T0 = 64 * 1024 * 1024;
int x0[] = { 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 };
int maxiterations = 100000;

int xoptimal[D] = { 0 };
int optvalueoptimal = -1;
int crossoptimal = 0;
int autooptimal = 0;
int optvaluenotset = -1;

int hmin = 1;
int hmax = 10;

int calc_crosscor(int  xoptimal[D]) {
	int samebits = 0;
	int diffbits = 0;
	for (int i = 0; i < D; i++) {
		if (xoptimal[i] == x0[i]) samebits++;
		else diffbits++;

	}
	return samebits - diffbits;

}
int calc_autocor(int  xoptimal[D], int *newx) {
	int samebits = 0;
	int diffbits = 0;
	for (int i = 0; i < D; i++) {
		if (xoptimal[i] == newx[i]) samebits++;
		else diffbits++;

	}
	return samebits - diffbits;

}

void get_cyclk(int* x, int* newx, int k) {
	int cnt = 0;
	for (int i = k; i < D; i++) {
		newx[cnt] = x[i];
		cnt++;
	}
	for (int i = 0; i < k; i++) {
		newx[cnt] = x[i];
		cnt++;
	}
}
int optfunction(int* x, int correctcros, int correctauto) {
	int numberofcros = 0;
	int numberofauto = 0;
	int crosscor = calc_crosscor(x);
	int autocor;
		if (crosscor > CROSSMIN && crosscor < CROSSMAX) numberofcros++;
		
	for (int i = 1; i < KCYCL; i++) {
		int newx[D] = { 0 };
		get_cyclk(x, newx, i);
		crosscor = calc_crosscor(newx);
		if (crosscor > CROSSMIN && crosscor < CROSSMAX) numberofcros++;
		
	}

	for (int i = 1; i < KCYCL; i++) {
		int newx[D] = { 0 };
		get_cyclk(x, newx, i);
		autocor = calc_autocor(x,newx);
		if (autocor > AUTOMIN && autocor < AUTOMAX) numberofauto++;
	}
	correctcros = numberofcros;
	correctauto = numberofauto;
	return numberofcros + numberofauto;
}

void randomizex(int x[D]) {
	int usedindexes[D] = { 0 };
	int index;
	for (int i = 0; i < NUMOFZEROS; i++) {
		index = (int)(rand() / (RAND_MAX / 31 + 1));
		while (usedindexes[index] == 1) index = (int)(rand() / (RAND_MAX / 31 + 1));
		usedindexes[index] = 1;
		x[index] = 0;

	}
	for (int i = 0; i < NUMOFONES; i++) {
		index = (int)(rand() / (RAND_MAX / 31 + 1));
		while (usedindexes[index] == 1) index = (int)(rand() / (RAND_MAX / 31 + 1));
		usedindexes[index] = 1;
		x[index] = 1;

	}

	index = index = (int)(rand() / (RAND_MAX / 31 + 1));
	while (usedindexes[index] == 1) index = (int)(rand() / (RAND_MAX / 31 + 1));

	x[index] = (int)(rand() / (RAND_MAX / 2 + 1));
}
void generatenewx(int* x, int i, int* newx) {
	int h = (hmin - hmax) * (i - 1) / (maxiterations - 1) + hmax;
	int places[D] = { 0 };
	int one = 1;
	int numofones = 0;
	for (int i = 0; i < D; i++) {
		if (x[i] == 1) numofones++;
	}
	if (numofones > D - numofones) one = 0;

	for (int i = 0; i < h; i++) {
		int index = (int)(rand() / (RAND_MAX / 31 + 1));
		if (one)
			while (places[index] == 1 || x[index]==1) index = (int)(rand() / (RAND_MAX / 31 + 1));
		else  while (places[index] == 1 || x[index] == 0) index = (int)(rand() / (RAND_MAX / 31 + 1));
		places[index] = 1;

		if (one) one = 0;
		else one = 1;
		int oldval = x[index];
		int newval = oldval == 1 ? 0 : 1;
		newx[index] = newval;
	}
	
}


void copyvalues(int x[], int newx[]) {
	for (int i = 0; i < D; i++)
		x[i] = newx[i];
}

int get_decimal(int *x) {
	int k = 0;
	int number = 0;
	for (int i = D-1; i >= 0; i--) {
		number += x[i] * pow(2, k);
		k++;
	}
	return number;
}

int main() {
	int x[D];
	int optvalue = 0;
	int correctcros = 0, correctauto = 0;
	int newx[D];
	for (int i = 0; i < N; i++) {
		randomizex(x);
		optvalue = optfunction(x, correctcros, correctauto);
		if (optvaluenotset == -1) {
			optvaluenotset = 1;
			optvalueoptimal = optvalue;
			for (int p = 0; p < D; p++)
				xoptimal[p] = x[p];
		}

		for (int j = 0; j < 10; j++) {
			optvalue = optfunction(x, correctcros, correctauto);
			double T = T0;
			for (int k = 0; k < maxiterations; k++) {
				copyvalues(newx, x);
				generatenewx(x, k, newx);
				int newcorrectcros = 0, newcorrectauto = 0;
				int newoptvalue = optfunction(newx, newcorrectcros, newcorrectauto);

				int deltaE = optvalue - newoptvalue;
				if (deltaE < 0) {
					copyvalues(x, newx);
					optvalue = newoptvalue;
					correctcros = newcorrectcros;
					correctauto = newcorrectauto;
				}
				else {

					double p = exp(-deltaE / T);
					double number = (double)rand() / RAND_MAX;
					if (number <= p) {
						copyvalues(x, newx);
						optvalue = newoptvalue;
						correctcros = newcorrectcros;
						correctauto = newcorrectauto;
					}

				}
				if (optvalue > optvalueoptimal) {
					optvalueoptimal = optvalue;
					for (int p = 0; p < D; p++)
						xoptimal[p] = x[p];
					crossoptimal = correctcros;
					autooptimal = correctauto;

				}
				if (optvalueoptimal == 61) break;

				T = a * T;

			}
			if (optvalueoptimal == 61) break;

		}
		if (optvalueoptimal == 61) break;
	}

	printf(" Binary value x = (");
	for (int i = 0; i < D; i++) {
		if (i % 4>0 || i==0)printf("%d", xoptimal[i]);
		else printf(" %d", xoptimal[i]);
	}
	printf(")\n");
	printf(" Decimal value x = %d", get_decimal(xoptimal));
}
