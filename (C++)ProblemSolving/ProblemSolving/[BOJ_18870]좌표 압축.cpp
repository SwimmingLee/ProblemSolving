#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int n;
int sidx = 0;
int arr[1000000];
int sorted_arr[1000000];

int search(int val) {
	int s, m, e;
	s = 0;
	e = sidx - 1;
	while (s <= e) {
		m = (s + e) / 2;
		if (sorted_arr[m] == val) return m;
		if (sorted_arr[m] > val) e = m - 1;
		else s = m + 1;
	}
	return m;
}


void solve() {
	for (int i = 0; i < n; i++) {
		cout << search(arr[i]) << ' ';
	}
}


int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	set<int> chk;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		if (chk.find(arr[i]) == chk.end()) {
			sorted_arr[sidx++] = arr[i];
			chk.insert(arr[i]);
		}
	}
	sort(sorted_arr, sorted_arr + sidx);
	solve();
	return 0;
}