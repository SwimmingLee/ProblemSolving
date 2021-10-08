#include <iostream>
#include <string>
using namespace std;

int n;
string board[8];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int TC = 10;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> n;
		for (int i = 0; i < 8; ++i) {
			cin >> board[i];
		}
		int answer = 0;
		bool vertical, horizon;
		for (int r = 0; r < 8; ++r) {
			for (int c = 0; c < 8; ++c) {
				vertical = horizon = true;
				if (r > 8 - n) vertical = false;
				if (c > 8 - n) horizon = false;
				for (int i = 0; i < n/2; ++i) {
					if (r <= 8 - n && board[r + i][c] != board[r + n - 1 - i][c])
						vertical = false;
					if (c <= 8 - n && board[r][c + i] != board[r][c + n - 1 - i])
						horizon = false;
				}

				
				if (n == 1) {
					answer++;
				}
				else {
					if (vertical) answer++;
					if (horizon) answer++;
				}
			}
		}
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}