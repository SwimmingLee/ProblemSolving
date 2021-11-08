#include <iostream>
#include <string>
using namespace std;

int needle_alpha[26];
int haystack_alpha[26];

void init() {
	for (int i = 0; i < 26; ++i) {
		needle_alpha[i] = 0;
		haystack_alpha[i] = 0;
	}
}

bool isAnagram() {
	for (int i = 0; i < 26; ++i) {
		if (needle_alpha[i] != haystack_alpha[i])
			return false;
	}
	return true;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		string haystack, needle;
		cin >> needle >> haystack;

		init();

		int len = needle.size();
		int answer = 0;
		for (int i = 0; i < len; ++i) {
			needle_alpha[needle[i] - 'a']++;
			haystack_alpha[haystack[i] - 'a']++;
		}
		if (isAnagram()) {
			answer++;
		}

		for (int i = len; i < haystack.size(); ++i) {
			haystack_alpha[haystack[i - len] - 'a']--;
			haystack_alpha[haystack[i] - 'a']++;
			if (isAnagram()) {
				answer++;
			}
			
		}
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}
