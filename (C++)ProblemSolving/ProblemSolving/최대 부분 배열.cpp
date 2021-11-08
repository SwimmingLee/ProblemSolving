#include <iostream>
using namespace std;

int N;
int A[200000];

int greatestSubArray() {
	int ret = 0;
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		if (sum < 0)
			sum = 0;

		sum += A[i];
		if (ret < sum)
			ret = sum;
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
		for (int i = 0; i < N; ++i) {
			cin >> A[i];
		}

		int answer = greatestSubArray();
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}