bool next_partition_of_set(int* a, int n) {
	int j;
	int* b = new int[n];
	
	for (j = 0; j < n; j++) {
		b[j] = j == 0 ? 0 : max(b[j - 1], a[j - 1] + 1);
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

void driver_next_partition_of_set(void) {
	int n = 4;
	int* a = new int[n];
	int i;
	
	for (i = 0; i < n; i++) {
		a[i] = 0;
	}
	
	do {
		for (i = 0; i < n; i++) {
			printf("%2d ", a[i]);
		}
		printf("\n");
	} while (next_partition_of_set(a, n));
	
	delete[]a;
}