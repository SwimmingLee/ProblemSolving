#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n_paper;
vector<string> a;
bool compare(const string& a, const string& b) {
	if (a.size() < b.size()) {
		return true;
	}
	else if (a.size() > b.size()) {
		return false;
	}
	else {
		return a < b;
	}
}
int main(void) {
	cin >> n_paper;
	while (n_paper--) {
		string s;
		cin >> s;
		
		// 끝처리 하지 않기 위한 방법
		s.push_back('a');
		int left = 0, right = 0;
		bool bnum = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= 'a' && s[i] <= 'z') {
				if (bnum) {
					right = i;
					string ss = s.substr(left, right - left);
					reverse(ss.begin(), ss.end());
					while (ss.size() > 1 && ss.back() == '0') {
						ss.pop_back();
					}
					reverse(ss.begin(), ss.end());
					a.push_back(ss);
				}
				bnum = false;
				
			}
			else {
				if (!bnum) {
					left = i;
					bnum = true;
				}
			}
		}
	}

	sort(a.begin(), a.end(), compare);
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << '\n';
	}
	return 0;
}