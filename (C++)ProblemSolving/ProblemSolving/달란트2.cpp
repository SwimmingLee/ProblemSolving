#include <iostream>
#include <cmath>
using namespace std;

int talent, n;
long long candy(int t, int n) {
	int piece;
	long long answer = 1;
	while (t % n != 0) {
		piece = t / n;
		answer *= (piece + 1);
		t = t - (piece + 1);
		n = n - 1;
	}
	answer *= pow(t / n, n);
	return answer;
}
int main() {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> talent >> n;
		long long answer = candy(talent, n);
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}