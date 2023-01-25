#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define velicinaF pow(2, 25)
#define hmin 1
#define hmax 3


void randomNiz(int** niz) {
	for (int i = 0; i < 64; i++) {
		niz[i] = rand() % 3;
	}
}

int optimizacionaFunkcija(int *niz, int *s) {
	int F1 = velicinaF;
	int F2 = velicinaF;
	for (int i = 0; i < 64; i++) {
		if (niz[i] == 1) {
			F1 -= s[i];
			continue;
		}
		if (niz[i] == 2) {
			F2 -= s[i];
			continue;
		}
	}
	if (F1 < 0 || F2 < 0) { 
		return  pow(2, 26); 
	}
	else {
		return F1 + F2;
	}
	
}

void generisiNoviNiz(int* niz,int iteracija, int*stariNiz) {

	for (int i = 0; i < 64; i++) {
		niz[i] = stariNiz[i];
	}
	int num = ((hmin - hmax) / (100000 - 1)) * (iteracija - 1) + hmax;
	int cnt = 0;
	int tmp[64] = { 0 };
	while (cnt < num) {
		int random = rand() % 64;
		if (tmp[random] == 0) {
			cnt++;
			tmp[random] = 1;
		}
	}
	for (int i = 0; i < 64; i++) {
		if (tmp[i] == 1) {
			niz[i] = rand() % 3;
		}
	}
}


int istorijaResenja[20][1000000];
int grafikSrednja[1000000] = { 0 };

int main() {
	int s[] = { 173669, 275487, 1197613, 1549805, 502334,
		217684, 1796841, 274708, 631252, 148665, 150254,
		4784408, 344759, 440109, 4198037, 329673, 28602,
		144173, 1461469, 187895, 369313, 959307, 1482335,
		2772513, 1313997, 254845, 486167, 2667146, 264004,
		297223, 94694, 1757457, 576203, 8577828, 498382,
		8478177, 123575, 4062389, 3001419, 196884, 617991,
		421056, 3017627, 131936, 1152730, 2676649, 656678,
		4519834, 201919, 56080, 2142553, 326263, 8172117,
		2304253, 4761871, 205387, 6148422, 414559, 2893305,
		2158562, 465972, 304078, 1841018, 1915571 };

	int najboljeResenje[64];
	int optVrednost = -1;

	int trenutnoResenje[64];

	for (int k = 0; k < 20; k++) {
		randomNiz(trenutnoResenje);
		if (optVrednost == -1) {
			optVrednost = optimizacionaFunkcija(trenutnoResenje,s);
			for (int i = 0; i < 64; i++) {
				najboljeResenje[i] = trenutnoResenje[i];
			}
		}
		int pomocna = optimizacionaFunkcija(trenutnoResenje,s);
		for (int i = 0; i < 10; i++) {
			double T = 64 * 1024 * 1024;
			for (int j = 0; j < 100000; j++) {
				int novNiz[64] = { 0 };
				generisiNoviNiz(novNiz, j, trenutnoResenje);
				int optNovo = optimizacionaFunkcija(novNiz, s);
				int optStaro = optimizacionaFunkcija(trenutnoResenje, s);
				//
				//DeltaE = Fnovo - Fstaro
				int DeltaE = optNovo - optStaro;
				if (DeltaE < 0) {
					for (int tmp = 0; tmp < 64; tmp++) {
						trenutnoResenje[tmp] = novNiz[tmp];
					}
				}
				else {
					double p = exp(-DeltaE / T);
					double random = (double) rand() / RAND_MAX;
					if (random <= p) {
						for (int tmp = 0; tmp < 64; tmp++) {
							trenutnoResenje[tmp] = novNiz[tmp];
						}
					}
				}
				if (optimizacionaFunkcija(trenutnoResenje, s) < optVrednost) {
					for (int i = 0; i < 64; i++) {
						najboljeResenje[i] = trenutnoResenje[i];
					}
					optVrednost = optimizacionaFunkcija(trenutnoResenje, s);
				}
				if (optimizacionaFunkcija(trenutnoResenje, s) < pomocna) {
					pomocna = optimizacionaFunkcija(trenutnoResenje, s);
				}
				istorijaResenja[k][i * 100000 + j] = pomocna;
				grafikSrednja[i * 100000 + j] += pomocna / 20;
				T *= 0.95;
			}
		}
	}

	

	printf("Vrednost optimizacione funkcije je: %d\n", optVrednost);
	printf("Niz vrednosti je: (");
	for (int i = 0; i < 64; i++)
	{
		if (i == 63) {
			printf("%d) ", najboljeResenje[i]);
			break;
		}
		printf("%d, ", najboljeResenje[i]);
		
	}

	FILE *f;
	fopen_s(&f, "vrednostiZaPajton.txt", "w+");
	for (int i = 0; i < 1000000; i++) {
		fprintf(f, "%d ", grafikSrednja[i]);
	}
	fprintf(f, "\n");

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 1000000; i++) {
			fprintf(f, "%d ", istorijaResenja[j][i]);
		}
		fprintf(f, "\n");
	}

	fclose(f);

	return 0;
}