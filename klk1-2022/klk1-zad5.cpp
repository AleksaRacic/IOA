#include <cstdlib>
#include <climits>
#include <stdio.h>

#define ITERATIONS 100000000

void random_permutation(int n, int *p){
    int i,j,s;
    for(i=n-1; i>0; i--){
        j = (rand() % i);
        if(i!=j){
            s = p[i];
            p[i] = p[j];
            p[j] = s;
        }
    }
}

int opt_function(const int N, int* P){
    int sum = 0;
    for(int i = 0; i < N; i++){
        sum += P[i]/(i+1);
    }
    return sum;

}

int main(void){
    srand(100);
    int N = 23;
    int* P = new int[N];
    int* P_min = new int[N];
    int sum;
	int min_sum = INT_MAX;

    for(int i = 0; i<N; i++){
        P[i] = i+1;
    }

    for(int i = 0; i<ITERATIONS; i++){
        random_permutation(N,P);
        sum = opt_function(N,P);

        if(sum < min_sum){
            min_sum = sum;
            for(int j = 0; j<N; j++){
                P_min[j] = P[j];
            }
        }
    }

    printf("Minimalna suma za N = %d je %d\n", N, min_sum);
    printf("Permutacija: ");
    for(int i = 0; i<N; i++){
        printf("%d ", P_min[i]);
    }
    printf("\n");

    delete[] P;
	delete[] P_min;
}