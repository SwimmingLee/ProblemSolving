#include <iostream>
#include <string>
#include <vector>
using namespace std;

int L;
string bracket;
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> L >> bracket;

		vector<pair<char, int>> st;
		for (int i = 0; i < bracket.size(); ++i) {
			if (!st.empty() && (st.back().first == '(' && bracket[i] == ')')) {
				st.pop_back();
				continue;
			}
			st.push_back({ bracket[i], i });
		}

		int answer = 0;
		bool hasOpen = false;
		bool hasClose = false;
		int len = st.size();
		// 남은 갯수가 홀수이면 짝이 맞지 않으므로 -1
		if (len % 2 == 1) {
			answer = -1;
		}
		else {
			for (int i = 0; i < len; ++i) {
				if (st[i].first == '(') hasOpen = true;
				else hasClose = true;

				if (hasOpen && hasClose) break;
			}
			if (hasOpen)
				answer++;
			if (hasClose)
				answer++;
		}

		cout << '#' << tc << ' ' << answer << '\n';
		
		// (((((( 꼴 or )))))) 꼴
		if (answer == 1) {
			if (hasOpen) {
				cout << st[len / 2].second << ' ' << st[len -1].second << '\n';
			}
			else {
				cout << st[0].second << ' ' << st[(len / 2) -1].second << '\n';
			}
		}
		// )))))((( 꼴
		else if (answer == 2) {
			if (st[len / 2].first == ')') {
				cout << st[0].second << ' ' << st[(len / 2) - 1].second << '\n';
				for (int i = len / 2; i < len; ++i) {
					if (st[i].first == '(') {
						cout << st[i].second << ' ' << st[len - 1].second << '\n';
						break;
					}
				}
			}
			else {
				cout << st[len / 2].second << ' ' << st[len - 1].second << '\n';
				for (int i = len / 2; i >= 0; --i) {
					if (st[i].first == ')') {
						cout << st[0].second << ' ' << st[i].second << '\n';
						break;
					}
				}
			}
		}

		
	}
	return 0;
}