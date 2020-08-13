#include <iostream>
using namespace std;

int gcd(int u, int v) {
	if (u % v == 0) return v;
	return gcd(v, u % v);
}

int main(void) {
	int N, M, L;
	cin >> N >> M >> L;
	cout << N / gcd(N, L) * (M - 1);
	return 0;
}