#include <stdio.h>
#include <climits>
#include <math.h>

int opt_function(const int N, int* P){
    int sum = 0;
    for(int i = 0; i < N; i++){
        sum += P[i]/(i+1);
    }
    return sum;

}

int next_permutation(const int N, int* P) {
	int s;
	int* first = &P[0];
	int* last = &P[N - 1];
	int* k = last - 1;
	int* l = last;
	
	while (k > first) {
		if (*k < *(k + 1)) {
			break;
		}
		k--;
	}
	
	if (*k > *(k + 1)) {
		return 0;
	}
	
	while (l > k) {
		if (*l > *k) {
			break;
		}
		l--;
	}
	
	s = *k;
	*k = *l;
	*l = s;
	
	first = k + 1;
	while (first < last) {
		s = *first;
		*first = *last;
		*last = s;
		
		first++;
		last--;
	}
	
	return 1;
}

int rows = 13;

int main(int argc, char *argv[]) {
	int N;
	if(argc<2) N = 3;
    else N = atoi(argv[1]);

	int** P_history = new int*[rows];
	for (int i = 0; i < rows; ++i)
    	P_history[i] = new int[N];

	int* P = new int[N];
    int sum;
	int min_sum = INT_MAX;
	int min_count = 0;
	
	for (int i = 0; i < N; i++) {
		P[i] = i + 1;
	}
	
	do {
        sum = opt_function(N,P);

		if(sum == min_sum && min_count < rows){
			for(int i = 0; i<N; i++){
				P_history[min_count][i] = P[i];
			}
			min_count++;
		}

		if(sum < min_sum){
			min_sum = sum;
			for(int i = 0; i<N; i++){
				P_history[0][i] = P[i];
			}
			min_count = 1;
		}
        

	} while (next_permutation(N, P));
	printf("Minimalna suma za N = %d je %d\n", N, min_sum);
	printf("Broj permutacija je %d:\n", min_count);
	for(int k = 0; k < min_count; k++){
		for(int i = 0; i<N; i++){
			printf("%d ", P_history[k][i]);
	}
		printf("\n");
	}
	

	delete[] P;
	for (int i = 0; i < rows; ++i)
    	delete[] P_history[i];
	delete[] P_history;
    return 0;
}