#include <iostream>
#include <string>
using namespace std;

int main(void) {
	int tc;
	cin >> tc;
	long long sim;
	long long res;
	while (tc--) {
		int n;
		string s;
		cin >> n >> s;
		sim = 0;
		for (int i = 0; i < n; i++) {
			sim = (sim << 1) + s[i] - '0';
		}
		res = sim;
		for (int i = n; i < 2 * n - 1; i++) {
			res &= ~(1 << n);
			res <<= 1;
			res += s[i] - '0';

			sim &= res;
		}
		string answer;
		for (int i = n-1; i>= 0; i--) {
			answer.push_back(((sim >> i) & 1) + '0');
		}
		cout << answer << '\n';
	}
	return 0;
}