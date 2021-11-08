#include <iostream>
using namespace std;

int N, K;
int W[200000];
int S[200000];

bool isPossible(int level) {
	int j = 0;
	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (W[i] <= level) {
			cnt++;
		}
		else {
			cnt = 0;
		}

		if (cnt == S[j]) {
			j += 1;
			cnt = 0;
			if (j == K) {
				return true;
			}
		}
		
	}

	return false;
}

int opticalWearLevel(int start, int last) {
	int ret = last;
	int mid;
	while (start <= last) {
		mid = (start + last) / 2;

		if (isPossible(mid)) {
			last = mid - 1;
			if (ret > mid) {
				ret = mid;
			}
		}
		else {
			start = mid + 1;
		}
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> K;
		for (int i = 0; i < N; ++i) {
			cin >> W[i];
		}
		for (int i = 0; i < K; ++i) {
			cin >> S[i];
		}
		int answer = opticalWearLevel(0, 200000);
		cout << '#' << tc << ' ' << answer << '\n';

	}
	return 0;
}