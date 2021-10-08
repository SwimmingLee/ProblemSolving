#include <iostream>
using namespace std;

int n;
int dp[1001][1001];
int gift[1001];

int insertGift(int s, int i) {
	if (i == n) return 0;

	int& ret = dp[s][i];
	if (ret != -1) return dp[s][i];

	ret = insertGift(s, i + 1);
	if (s < gift[i])
		ret = max(ret, insertGift(gift[i], i + 1) + 1);

	return ret;
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> gift[i];
		for (int s = 0; s < 1000; ++s) {
			dp[s][i] = -1;
		}
	}
	
	cout << insertGift(0, 0) << '\n';
	return 0;
}