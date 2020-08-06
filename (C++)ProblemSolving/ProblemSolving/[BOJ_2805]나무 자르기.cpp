#include <iostream>
#include <algorithm>
using namespace std;

int arr[1000000];

int main(void) {
	int	n, length;
	cin >> n >> length;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int total = -987987987;
	int left, right, mid;
	left = 0;
	right =	1e9;
	while (left <= right) {
		mid = (left + right) / 2;
		long long sum = 0;
		for (int i = 0; i < n; i++) {
			int part = arr[i] - mid;
			sum += part > 0 ? part : 0;
		}
	
		if (sum >= length) {
			total = max(total, mid);
			left = mid + 1;
		}
		else right = mid - 1;
	
	}

	cout << total << '\n';

	return 0;
}