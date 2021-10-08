#include <iostream>
using namespace std;

int primePercentA, primePercentB;
bool isPrime[20];
int comb[20][20];

int combination(int n, int r) {
	if (r == 0 || n == r) return 1;
	int& ret = comb[n][r];
	if (ret != 0) return comb[n][r];
	
	return ret = combination(n - 1, r) + combination(n - 1, r - 1);
}

double exponent(int percent, int exp) {
	double prob = (double)percent / 100;
	double ret = 1;
	for (int i = 0; i < exp; ++i) {
		ret *= prob;
	}
	//cout << percent << " " << exp << " " << ret << endl;
	return ret;
}

void init() {
	for (int i = 0; i < 20; ++i) isPrime[i] = true;
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i * i < 20; ++i) {
		if (isPrime[i]) {
			for (int j = i * i; j < 20; j += i) {
				isPrime[j] = false;
			}
		}
	}
}
double primeProduct() {
	
	double nonPrimeProbablityA, nonPrimeProbablityB;
	nonPrimeProbablityA = nonPrimeProbablityB = 0;
	for (int i = 0; i <= 18; ++i) {
		if (!isPrime[i]) {
			double n = combination(18, i);
			nonPrimeProbablityA += n * exponent(primePercentA, i) * exponent(100 - primePercentA, 18 - i);
			nonPrimeProbablityB += n * exponent(primePercentB, i) * exponent(100 - primePercentB, 18 - i);
		}
	}
	return 1 - (nonPrimeProbablityA * nonPrimeProbablityB);
}

int main(void) {
	int TC;
	cin >> TC;
	cout << fixed;
	cout.precision(6);
	init();
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> primePercentA >> primePercentB;
		double answer = primeProduct();
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}