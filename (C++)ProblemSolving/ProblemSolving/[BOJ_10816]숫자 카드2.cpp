#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[500000];

int upperBound(int var) {
	int start, mid, end;
	start = 0;
	end = N - 1;

	int res = -1;
	while (start <= end) {
		mid = (start + end) / 2;

		if (arr[mid] <= var) {
			start = mid + 1;
			if (res < mid) 
				res = mid;
		} else{
			end = mid - 1;
		}
	}
	return res;
}

int lowerBound(int var) {
	int start, mid, end;
	start = 0;
	end = N - 1;
	int res = N;
	while (start <= end) {
		mid = (start + end) / 2;

		if (arr[mid] < var) {
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
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + N);
	cin >> M;
	for (int i = 0; i < M; i++) {
		int var;
		cin >> var;
		cout << upperBound(var) -  lowerBound(var) + 1 << ' ';
	}
	return 0;
}