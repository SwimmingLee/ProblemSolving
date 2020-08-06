#include <iostream>
#include <algorithm>
using namespace std;

int arr[100000];

bool search(int n, int val) {
	int left, right, mid;
	left = 0;
	right = n - 1;

	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == val) return true;

		if (arr[mid] > val) right = mid - 1;
		else left = mid + 1;
	}
	return false;
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int val;
		cin >> val;
		if (search(n, val)) cout << "1\n";
		else cout << "0\n";
	}
	return 0;
}