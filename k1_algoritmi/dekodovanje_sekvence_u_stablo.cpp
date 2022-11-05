void SequenceToSpanningTree(int* P, int len, int* T) {
	int i;
	int j;
	int q = 0;
	int n = len + 2;
	int* V = new int[n];
	
	for (i = 0; i < n; i++) {
		V[i] = 0;
	}
	
	for (i = 0; i < len; i++) {
		V[P[i] - 1] += 1;
	}
	
	for (i = 0; i < len; i++) {
		for (j = 0; j < n; j++) {
			if (V[j] == 0) {
				V[j] = -1;
				T[q++] = j + 1;
				T[q++] = P[i];
				V[P[i] - 1]--;
				break;
			}
		}
	}
	
	j = 0;
	for (i = 0; i < n; i++) {
		if (V[i] == 0 && j == 0) {
			T[q++] = i + 1;
			j++;
		}
		else if (V[i] == 0 && j == 1) {
			T[q++] = i + 1;
			break;
		}
	}
	
	delete[]V;
}

void main(void) {
	int P[] = {1, 2, 2};
	int len = sizeof(P) / sizeof(P[0]);
	
	int* T = new int[2 * (len + 1)];
	SequenceToSpanningTree(P, len, T);
	
	for (int i = 0; i < 2 * (len + 1); i++) {
		printf(" %d", T[i]);
		if ((i + 1) % 2 == 0 && i < 2 * len) {
			printf("  - ");
		}
	}
	printf("\n");
	
	delete[]T;
}