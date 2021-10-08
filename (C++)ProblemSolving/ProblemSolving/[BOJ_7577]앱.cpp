#include <iostream>
#include <queue>
using namespace std;

#define MAX_APP 100
#define MAX_COST 10000

const int INF = 987987987;
int n, m;
int memory[MAX_APP+1];
int cost[MAX_APP+1];
int dp[2][MAX_COST + 1];

int switchingCost() {
	int res = INF;

	for (int c = 0; c <= 10000; ++c) {
		dp[0][c] = dp[1][c] = -1;
	}
	dp[0][0] = 0;
	for (int i = 0; i < n; ++i) {
		for (int c = 0; c <= 10000; ++c) {
			dp[1 - i % 2][c] = max(dp[1 - i % 2][c], dp[i % 2][c]);
			if (dp[i % 2][c] == -1 || cost[i] + c > 10000) continue;
			dp[1 - i % 2][c + cost[i]] = max(dp[1 - i % 2][c + cost[i]], dp[i % 2][c] + memory[i]); /*���.. ���⼭ �Ǽ��� �ϴٴ�*/
			/*visited - ó���� �� üũ�� �ʿ��ϴٰ� �������� �ʾҾ���! ��� �ʿ����! �ʱ�ȭ�� �ϸ� ��!*/
		}

	}
	for (int c = 0; c <= 10000; ++c) {
		if (dp[n%2][c] >= m) {
			res = min(res, c);
		}
	}
	return res;
}

int main(void) {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> memory[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> cost[i];
	}

	int answer = switchingCost();
	cout << answer << '\n';

	return 0;
}
