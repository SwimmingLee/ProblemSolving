#include <iostream>
#include <string>
using namespace std;

string num;
int swap_cnt;
int dp[1000000][10];
//  dp[720(6!)][10]으로 줄일 수 있음! 
int maxinumPrice(int n, int s) {
	int& ret = dp[n][s];
	if (ret != 0) return dp[n][s];
	//int ret = 0;

	if (s == 0) {
		for (int i = 0; i < num.size(); ++i) {
			ret = ret * 10 + num[i] - '0';
		}
		return ret;
	}
	for (int i = 0; i < (int)num.size() - 1; ++i) {
		int max_idx = i + 1;
		for (int j = i + 1; j < num.size(); ++j) { /*남들 코드보다 알았다...이렇게 그리디하게 해도 될줄 왜 생각 못했을까*/
			if (num[max_idx] <= num[j]) max_idx = j;
		}
		swap(num[i], num[max_idx]);
		ret = max(ret, maxinumPrice(stoi(num), s - 1));
		swap(num[i], num[max_idx]);
		// 이걸 좀 더 그리디하게 할 수도 있음! 굳이 DP를 쓰지 않아도 됐음!
		// test_case가 많을 때는 DP가 그래도 나름 유리함
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		cin >> num >> swap_cnt;
		int answer = maxinumPrice(stoi(num), swap_cnt);
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}