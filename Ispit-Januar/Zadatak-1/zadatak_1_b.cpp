#include <algorithm>
#include <iostream>

int R[] = {0, 10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82};

double calculate_resistancy(int* a, int n){
	double groups[n];
	double total = 0.0;
	int i = 0;

	for (i = 0; i < n; i++)
	{
		groups[i] = 0;
	}

	for (i = 0; i < n; i++)
	{
		if (a[i] != 0)
		{
			groups[a[i]] += 1 / (double)R[i];
		}
	}
	for(int i=1; i<n;i++){
		if(groups[i] > 0.0000001) total += 1/groups[i];
	}
	return total;

}

bool next_partition_of_set(int* a, int n) {
	int j;
	int* b = new int[n];
	
	for (j = 0; j < n; j++) {
		b[j] = j == 0 ? 0 : std::max(b[j - 1], a[j - 1] + 1);
	}
	
	for (j = n - 1; j >= 0; j--) {
		if (a[j] < b[j]) {
			a[j]++;
			break;
		}
		else {
			a[j] = 0;
		}
	}
	
	if (j == -1) {
		return false;
	}
	
	delete[]b;
	return true;
}



int main(){
	int n = 13;
	int* a = new int[n];
	int* a_best = new int[n];
	int i;
	double min_err = 8000.0;
	double err;

	double reference;

	std::cin >> reference;
	
	for (i = 0; i < n; i++) {
		a[i] = 0;
	}
	do {
		/*for (i = 0; i < n; i++) {
			printf("%2d ", a[i]);
		}
		printf("\n");
		printf("%f\n\n", calculate_resistancy(a, n));
		*/
		err = abs(calculate_resistancy(a, n) - reference);
		if(err < min_err){
			min_err = err;
			for(int j=0;j<n;j++){
				a_best[j] = a[j];
			}
		}
	} while (next_partition_of_set(a, n));

	for (i = 0; i < n; i++) {
		printf("%2d", a_best[i]);
	}
	printf("\n");
	printf("resistancy: %f\n", calculate_resistancy(a_best, n));
	printf("err: %f\n", min_err);

	for(i = 0; i<n; i++){
        printf("%d: ", i);
        for(int j = 0; j<n; j++){
            if(a_best[j] == i){
                printf("%d, ", R[j]);
            }
        }
        printf("\n");
    }
	
	delete[]a;
	delete[] a_best;
	return 0;
}