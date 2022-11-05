bool next_partition(int* p, int n) {
	int k;
	int i;
	int q = 0;
	
	if (p[0] == 0) {
		p[0] = n;
		return true;
	}
	else {
		for (i = 0; i < n; i++) {
			if (p[i] != 0) {
				k = i;
			}
			else {
				break;
			}
		}
	}
	
	while (k >= 0 && p[k] == 1) {
		q++;
		k--;
	}
	
	if (k < 0) {
		return false;
	}
	
	p[k]--;
	q++;
	
	while (q > p[k]) {
		p[k + 1] = p[k];
		q = q - p[k];
		k++;
	}
	
	p[k + 1] = q;
	k++;
	
	for (i = k + 1; i < n; i++) {
		p[i] = 0;
	}
	
	return true;
}

void driver_next_permutation(void) {
	int n = 7;
	int* p = new int[n];
	
	for (int i = 0; i < n; i++) {
		p[i] = 0;
	}
	
	while (next_partition(p, n)) {
		for (int i = 0; i < n && p[i] > 0; i++) {
			printf("%2d ", p[i]);
		}
		printf("\n");
	}
	
	delete[]p;
}