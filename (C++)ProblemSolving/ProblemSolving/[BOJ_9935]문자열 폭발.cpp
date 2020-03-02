#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string GetExplosionStr(string& str, string& pattern) {
	string ans;
	int pattern_sz = pattern.length();
	int j = pattern_sz - 1;
	
	while(!str.empty()) {
		char c = str.back();
		str.pop_back();
		ans.push_back(c);
		if (c == pattern[j]) {
			j -= 1;
			if (j < 0) {
				while (++j != pattern_sz) ans.pop_back();
				while (!ans.empty() && j--) {
					int tmp = ans.back();
					ans.pop_back();
					str.push_back(tmp);
				}
				j = pattern_sz - 1;
			}
		}
		else {
			j = pattern_sz - 1;
			if (!ans.empty() && ans.back() == pattern[j])
				j = pattern_sz - 2;
		}
	}
	

	reverse(ans.begin(), ans.end());
	return ans;
}

int main(void) {
	string str, pattern;
	cin >> str >> pattern;

	string ans = GetExplosionStr(str, pattern);
	cout << (ans == "" ? "FRULA" : ans)  << '\n';

	return 0;
}