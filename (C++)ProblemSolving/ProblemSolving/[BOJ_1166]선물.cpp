#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long n, width, length, height;

void solve() {
	double left = 0, right = 1e9, mid;
	right = min(width, min(length, height));
	for (int i = 0; i < 100000; i++) {
		mid = (left + right) / 2;
		if ((long long)(width / mid) * (long long)(length / mid) * (long long)(height / mid) >= n) left = mid;
		else right = mid;
	}
	cout << left << '\n';
}

int main(void) {
	cin >> n >> width >> length >> height;
		
	cout << fixed;
	cout.precision(10);
	solve();
	return 0;
}