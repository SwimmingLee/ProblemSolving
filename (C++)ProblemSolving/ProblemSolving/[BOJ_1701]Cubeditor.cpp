#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int preprocessing(const string& pattern) {
	int long_fail = 0;
	vector<int> fail(pattern.size(), 0);
	int j = 0; 
	for (int i = 1; i < pattern.size(); i++) {
		while (j > 0 && pattern[i] != pattern[j]) j = fail[j - 1];
		if (pattern[i] == pattern[j]) {
			fail[i] = ++j;
			if (long_fail < fail[i]) 
				long_fail = fail[i];
		}
		else fail[i] = 0;
	}
	return long_fail;
}
int GetLongPartialStr(string &str) {
	int ans = 0;
	int str_sz = str.length();
	string pattern;
	
	for (int i = 0; i < str_sz; i++) {
		char c = str.back(); str.pop_back();
		pattern.insert(0, 1, c);
		int tmp = preprocessing(pattern);
		if (tmp > ans)
			ans = tmp;
	}
	return ans;
}

int main(void) {
	string str;
	cin >> str;

	cout << GetLongPartialStr(str) << '\n';
	return 0;
}