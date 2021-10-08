#include <iostream>
#include <string>
using namespace std;

string pattern, haystack;
int findPattern() {
	const long long MOD = 69521241234;
	const int base = 256;
	long long patternHash = 0;
	long long hayHash = 0;
	int first = 1;
	int answer = 0;
	for (int i = 0; i <= haystack.size() - pattern.size(); ++i) {
		if (i == 0) {
			for (int j = 0; j < pattern.size(); ++j) {
				patternHash = (patternHash * base + pattern[j]) % MOD;
				hayHash = (hayHash * base + haystack[j]) % MOD;
				if (j < pattern.size() - 1)
					first *= base;
			}
		}
		else {
			hayHash = ((hayHash - haystack[i-1] * first) * base + haystack[i + pattern.size() -1]) % MOD;
		}

		if (patternHash == hayHash) {
			bool isPattern = true;
			for (int j = 0; j < pattern.size(); ++j) {
				if (pattern[j] != haystack[i + j]) {
					isPattern = false;
					break;
				}
			}
			if (isPattern)
				answer++;
		}
	}
	return answer;
}

int findPattern2() {
	int fail[11] = { 0, 0};
	int answer = 0;
	// preprocess - fail array
	int j = 0;
	for (int i = 1; i < pattern.size(); ++i) {
		while (j > 0 && pattern[i] != pattern[j]) j = fail[j-1];
		if (pattern[i] == pattern[j]) {
			fail[i] = j + 1;
			++j;
		}
		else {
			fail[i] = 0;
		}
	}

	// find pattern in haystack string
	j = 0;
	for (int i = 0; i < haystack.size(); ++i) {
		while (j > 0 && haystack[i] != pattern[j]) j = fail[j-1];
		if (pattern[j] == haystack[i]) {
			++j;
			if (j == pattern.size()) {
				j = fail[j - 1];
				answer += 1;
			}
		}
	}
	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int TC = 10;
	//cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		int n;
		cin >> n;
		cin >> pattern >> haystack;
		int answer = findPattern();
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}