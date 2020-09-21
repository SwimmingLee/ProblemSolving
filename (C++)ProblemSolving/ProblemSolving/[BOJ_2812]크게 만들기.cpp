#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	int n, k;
	string s;
	cin >> n >> k >> s;
	
	string answer;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		while (!answer.empty() && answer.back() < s[i] && cnt < k) {
			answer.pop_back();
			cnt++;
		}
		answer.push_back(s[i]);
	}
	while (cnt < k) {
		answer.pop_back();
		cnt++;
	}
	cout << answer << '\n';
	return 0;
}