#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string Kthsuffix(int k, const string& s) {
	string ans = "";
	vector<string> suffixes;
	for (int i = 0; i < s.size(); ++i) {
		suffixes.push_back(s.substr(i));
	}
	sort(suffixes.begin(), suffixes.end());

	return suffixes[k-1];
}
int main(void) {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		int k;
		string s;
		cin >> k >> s;
		string answer = Kthsuffix(k, s);
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}