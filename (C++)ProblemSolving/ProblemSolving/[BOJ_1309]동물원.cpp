#include <iostream>
using namespace std;

const int MOD = 9901;
int N;
int dp[2][100000];

int zoo(int shape, int n) {
	
	int& ret = dp[shape][n];
	if (ret != 0) return dp[shape][n];

	if (shape == 0) {
		ret = ((2 * zoo(1, n - 1)) % MOD + zoo(0, n - 1)) % MOD; /*오버플로우 조심. 마지막에만 하면 오버플로우가 날 수 있음*/
	}
	else {
		ret = (zoo(0, n - 1) + zoo(1, n - 1)) % MOD;
	}
	return ret % MOD;
}

int main(void) {
	cin >> N;
	dp[0][0] = 3;
	dp[1][0] = 2;

	cout << zoo(0, N-1) << '\n';
	return 0;
}