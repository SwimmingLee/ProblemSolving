#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
	long long num, tmp;
	int three_times;

	int arr_sz;
	vector<pair<int, long long>> arr;

	cin >> arr_sz;
	arr.resize(arr_sz);
	for (int i = 0; i < arr_sz; i++) {
		cin >> num;

		tmp = num;
		three_times = 0;
		while ((tmp % 3) == 0) {
			three_times++;
			tmp /= 3;
		}
		arr[i] = { -three_times, num };
	}
	sort(arr.begin(), arr.end());
	for (int i = 0; i < arr_sz; i++)
		cout << arr[i].second << ' ';
	cout << '\n';

	return 0;
}