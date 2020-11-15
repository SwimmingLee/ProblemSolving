#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void compareSolid(vector<long long>& arr) {
	int left, right;
	left = 0;
	right = arr.size() - 1;
	long long dist = 987987987987L;
	int dist_left, dist_right;
	dist_left = dist_right = 0;
	while (left < right) {
		long long tmp = arr[left] + arr[right];
		if (abs(tmp) < abs(dist)) {
			dist = tmp;
			dist_left = left;
			dist_right = right;
		}
		
		if (tmp < 0) {
			left++;
		}
		else {
			right--;
		}
	}
	cout << arr[dist_left] << ' ' << arr[dist_right] << '\n';
}

int main(void) {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<long long> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	compareSolid(arr);
	return 0;
}