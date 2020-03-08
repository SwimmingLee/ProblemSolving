#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> preprocessing(string& p) {
	int len = p.size();
	vector<int> pi(len);
	int j = 0;
	for (int i = 1; i < len; i++) {
		while (j > 0 && p[i] != p[j]) j = pi[j - 1];
		if (p[i] == p[j]) {
			pi[i] = j + 1;
			j += 1;
		}
		else {
			pi[i] = 0;
		}
	}
	return pi;

}
void CalmelonSubString(string& s) {
	int len = s.size();
	vector<int> pi = preprocessing(s);
	vector<int> cnt(len);
	for (int i = 0; i < len -1; i++) {
		cnt[pi[i]] += 1;
	}
	for (int i = pi[len - 1]; i != 0; i = pi[i - 1]) {
		if (cnt[i] >= 1) {
			cout << s.substr(0, i) << '\n';
			return;
		}
	}
	cout << -1 << '\n';
}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string s;
	cin >> s;
	CalmelonSubString(s);
	return 0;
}