#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	string s;
	cin >> s;
	
	int len = s.size();
	vector<int> cnt(len+1);
	vector<int> pi(len+1);
	int j = 0;

	for (int i = 1; i < len; i++) {
		while (j > 0 && s[i] != s[j]) j = pi[j - 1];
		if (s[i] == s[j]) {
			pi[i] = j + 1;
			j += 1;
		}
		else {
			pi[i] = 0;
		}
	}
	

	for (int i = 0; i < len; i++) {
		cnt[pi[i]] += 1;
	}
	for (int i = len; i > 0; i--) {
		cnt[pi[i - 1]] += cnt[i];
	}
	vector<pair<int, int>> ans;
	for (int i = len; i > 0; i = pi[i - 1]) {
		ans.push_back({ i, cnt[i]+1 });
	}

	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].first << ' ' << ans[i].second << '\n';
	}
	return 0;
}