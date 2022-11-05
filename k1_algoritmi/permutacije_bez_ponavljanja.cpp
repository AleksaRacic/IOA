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

void main(void) {
	int N = 5;
	int* P = new int[N];
	
	for (int i = 0; i < N; i++) {
		P[i] = i + 1;
	}
	
	do {
		for (int i = 0; i < N; i++) {
			printf("%2d ", P[i]);
		}
		printf("\n");
	} while (next_permutation(N, P));
	
	delete[]P;
}