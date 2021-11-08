#include <iostream>
#include <string>
using namespace std;

string s1, s2;
int cache[1000][1000];

void init() {
	for (int i = 0; i < 1000; ++i) {
		for (int j = 0; j < 1000; ++j)
			cache[i][j] = -1;
	}
}
int lcs(int s1i, int s2i) {
	if (s1i >= s1.size() || s2i >= s2.size())
		return 0;

	int& ret = cache[s1i][s2i];
	if (ret != -1)
		return ret;

	ret = lcs(s1i + 1, s2i + 1) + (s1[s1i] == s2[s2i] ? 1 : 0);
	ret = max(ret, lcs(s1i + 1, s2i));
	ret = max(ret, lcs(s1i, s2i + 1));

	return ret;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> s1 >> s2;
		init();
		int answer = lcs(0, 0);
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}