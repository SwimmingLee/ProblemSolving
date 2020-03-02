#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> preprocess(string& pattern) {
	int pattern_sz = pattern.length();
	vector<int> fail(pattern_sz, 0);
	int j = 0;
	for (int i = 1; i < pattern_sz; i++) {
		while (j > 0 && pattern[i] != pattern[j]) j = fail[j - 1];
		if (pattern[i] == pattern[j]) {
			fail[i] = j + 1;
			j += 1;
		}
		else {
			fail[i] = 0;
		}
	}
	return fail;
}

void match(string& str, string& pattern) {
	vector<int> matchArr;
	vector<int> fail = preprocess(pattern);

	int str_sz = str.length();
	int pattern_sz = pattern.length();
	
	int j = 0;
	for (int i = 0; i < str_sz ; i++) {
		while (j > 0 && str[i] != pattern[j]) j = fail[j - 1];
		if (str[i] == pattern[j]) {
			j += 1;
			if (j == pattern_sz) {
				matchArr.push_back(i - j + 2);
				j = fail[j - 1];
			}
		}
	}

	cout << matchArr.size() << '\n';
	for (int i = 0; i < matchArr.size(); i++) {
		cout << matchArr[i] << '\n';
	}
}

int main(void) {
	string str, pattern;
	getline(cin, str);
	getline(cin, pattern);

	match(str, pattern);
	return 0;
}