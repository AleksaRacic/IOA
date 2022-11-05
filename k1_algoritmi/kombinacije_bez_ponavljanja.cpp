void combinations_without_repetition(int n, int k) {
	int i;
	int j;
	bool b;
	int *P = new int[k];
	
	for (i = 0; i < k; i++) {
		P[i] = i + 1;
	}
	
	do {
		for (i = 0; i < k; i++) {
			printf("%3d ", P[i]);
		}
		printf("\n");
		
		b = false;
		for (i = k - 1; i >= 0; i--) {
			if (P[i] < n - k + 1 + i) {
				P[i]++;
				for (j = i + 1; j < k; j++) {
					P[j] = P[j - 1] + 1;
				}
				b = true;
				break;
			}
		}
	} while (b);
	
	if (P != nullptr) delete[]p;
}