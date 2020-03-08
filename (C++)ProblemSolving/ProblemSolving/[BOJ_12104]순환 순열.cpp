#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> preprocessing(string& p) {
	int len = p.size();
	vector<int> pi(len);

	int j = 0;
	for (int i = 1; i < len; i++) {
		while (j > 0 && p[j] != p[i]) j = pi[j - 1];
		if (p[j] == p[i]) {
			pi[i] = j + 1;
			j += 1;
		}
		else {
			pi[i] = 0;
		}
	}
	return pi;
}

int KMP(string& s, string& p) {
	int ans = 0;
	vector<int> pi = preprocessing(p);
	int j = 0;
	for (int i = 0; i < s.size(); i++) {
		while (j > 0 && p[j] != s[i]) j = pi[j - 1];
		if (p[j] == s[i]) {
			j += 1;
			if (j == p.size()) {
				j = pi[j - 1];
				ans += 1;
			}
		}
		
	}
	return ans;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s, p;
	cin >> s >> p;
	s += s;
	s.pop_back();
	cout << KMP(s, p) << '\n';

	return 0;
}