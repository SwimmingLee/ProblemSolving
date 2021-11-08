#include <iostream>
using namespace std;

#define MAX_STICK 21
int N;
int L, R;

long long cache[MAX_STICK][MAX_STICK][MAX_STICK];

void pole() {
	cache[1][1][1] = 1;
	for (int n = 2; n < MAX_STICK; ++n) {
		for (int l = 1; l <= n; ++l) {
			for (int r = 1; r <= n; ++r) {
				cache[n][l][r] = cache[n - 1][l - 1][r] + cache[n - 1][l][r - 1] + (n - 2) * cache[n - 1][l][r];
			}
		}
	}
	return;
}

int main(void) {
	int T;
	cin >> T;
	pole();
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> L >> R;
		long long answer = cache[N][L][R];
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}