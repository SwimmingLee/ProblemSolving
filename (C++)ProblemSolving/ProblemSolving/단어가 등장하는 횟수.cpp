#include <iostream>
#include <string>
using namespace std;

#define MAX_NEEDLE_STRING	100000

string haystack;
string needle;
int fail[MAX_NEEDLE_STRING];

int getNeedleCount() {
	int ret = 0;

	int j = 0;
	for (int i = 1; i < needle.size(); ++i) {
		while (j > 0 && needle[i] != needle[j]) {
			j = needle[j - 1];
		}
		if (needle[i] == needle[j]) {
			fail[i] = ++j;
		}
		else {
			fail[i] = 0;
		}
	}


	j = 0;
	for (int i = 0; i < haystack.size(); ++i) {
		while (j > 0 && haystack[i] != needle[j]) {
			j = fail[j - 1];
		}
		if (haystack[i] == needle[j]) {
			++j;
			if (j == needle.size()) {
				ret+=1;
				j = fail[j - 1];
			}
		}
	}

	return ret;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> haystack >> needle;
		int answer = getNeedleCount();
		cout << '#' << tc << ' ' << answer << '\n';
	}

	return 0;
}