#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		unordered_set<string> set;
		int n, m;
		string s;
		int answer = 0;
		cin >> n >> m;
		for (int i = 0; i < n; ++i) {
			cin >> s;
			set.insert(s);
		}
		for (int j = 0; j < m; ++j) {
			cin >> s;
			if (set.find(s) != set.end())
				answer++;
		}
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}