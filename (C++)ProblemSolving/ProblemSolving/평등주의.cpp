#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_ARRAY	100000
#define MAX_SIZE	1e9

int N, K;
int A[MAX_ARRAY];


bool diffPossible(int step) {
	int minCutting[MAX_ARRAY] = { 0, };

	int diff = MAX_SIZE+1;
	for (int i = 0; i < N; ++i) {
		diff = min(A[i], diff);
		minCutting[i] = diff;
		diff += step;
	}

	diff = MAX_SIZE + 1;
	for (int i = N - 1; i >= 0; --i) {
		diff = min(A[i], diff);
		minCutting[i] = min(diff, minCutting[i]);
		diff += step;
	}

	long long sum = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i] - minCutting[i] > 0) {
			sum += A[i] - minCutting[i];
			if (sum > K) {
				return false;
			}
		}
	}
	return true;
}

int makeEqual(int start, int last) {
	int ret = last;
	int mid;

	while (start <= last) {
		mid = (start + last) / 2;

		// 인접한 숫자간 차이(mid)를 최대 K번 연산을 통해 만들 수 있는가?
		if (diffPossible(mid)) {
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
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> K;
		int maxNum = 0;
		for (int i = 0; i < N; ++i) {
			cin >> A[i];
			maxNum = max(maxNum, A[i]);
		}

		int answer = makeEqual(0, MAX_SIZE);
		cout << '#' << tc << ' ' << answer << '\n';

	}
	return 0;
}