long long stirling(long long n, long long k) {
	if (n == k) return 1;
	if (n == 0 || k == 0) return 0;
	return stirling(n - 1, k) * k + stirling(n - 1, k - 1);
}