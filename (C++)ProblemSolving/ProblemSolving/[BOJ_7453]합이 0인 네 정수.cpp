#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int arr[4][4000];
int darr[16000000];
int N;

int upper(int val) {
	int start, mid, end;
	start = 0;
	end = N * N - 1;
	int res = -1;
	while (start <= end) {
		mid = (start + end) / 2;
		if (darr[mid] <= val) {
			start = mid + 1;
			if (res < mid) {
				res = mid;
			}
		}
		else end = mid - 1;
	}
	return res;
}

int lower(int val) {
	int start, mid, end;
	start = 0;
	end = N * N - 1;

	int res = N * N;
	while (start <= end) {
		mid = (start + end) / 2;
		if (darr[mid] < val) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
			if (res > mid) {
				res = mid;
			}
		}
	}
	return res;
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	long long answer = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> arr[0][i] >> arr[1][i] >> arr[2][i] >> arr[3][i];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			darr[i * N + j] = arr[2][i] + arr[3][j];
		}
	}

	sort(darr, darr + N * N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int upper_idx = upper(-(arr[0][i] + arr[1][j]));
			int lower_idx = lower(-(arr[0][i] + arr[1][j]));
			int cnt = upper_idx - lower_idx + 1;
			answer += cnt;
		}
	}
	cout << answer;
	return 0;
}