#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#define MAX_NUM 100001

int N;
int arr[MAX_NUM];

int segtree[1 << 18];

void init() {
	for (int i = 0; i < (1 << 18); ++i) {
		segtree[i] = 0;
	}
}

int segSearch(int idx, int first, int last, int left, int right) {
	int ret = 0;

	if (last < left || right < first) return 0;
	else if (left <= first && last <= right) return segtree[idx];


	int mid = (first + last) / 2;
	ret = segSearch((idx << 1) + 1, first, mid, left, right);
	ret += segSearch((idx << 1) + 2, mid + 1, last, left, right);

	return ret;
}

void segUpdate(int idx, int first, int last, int val) {

	if (last < val || val < first) return;
	else if (first == last) {
		++segtree[idx];
		return;
	}

	int mid = (first + last) / 2;
	segUpdate((idx << 1) + 1, first, mid, val);
	segUpdate((idx << 1) + 2, mid + 1, last, val);
	segtree[idx] = segtree[(idx << 1) + 1] + segtree[(idx << 1) + 2];
	return;
}

long long solve() {
	long long ret = 0;
	for (int i = 0; i < N; ++i) {
		ret += (long long)segSearch(0, 0, N - 1, arr[i], N - 1);
		segUpdate(0, 0, N-1, arr[i]-1);
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		init();
		for (int i = 0; i < N; ++i) {
			cin >> arr[i];
		}
		long long answer = solve();
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}