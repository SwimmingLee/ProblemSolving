#include <iostream>
#include <algorithm>
using namespace std;

int len;
int query;
int arr[300001];
int parr[300001];
int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> len >> query;
	for (int i = 0; i < len; i++)
		cin >> arr[i];
	sort(arr, arr + len);
	parr[0] = arr[0];
	for (int i = 1; i < len; i++) {
		parr[i] = parr[i - 1] + arr[i];
	}
	for (int i = 0; i < query; i++) {
		int left, right;
		cin >> left >> right;
		if (left - 2 < 0) cout << parr[right - 1] << '\n';
		else cout << parr[right - 1] - parr[left - 2] << '\n';
	}
	return 0;
}