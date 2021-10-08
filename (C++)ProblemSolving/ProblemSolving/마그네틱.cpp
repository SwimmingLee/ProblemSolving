#include <iostream>
using namespace std;

// 1: N극, 2: S극
// 위: N극, 아래: S극
int board[100][100];
int n;
void input() {
	cin >> n;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}
}

int deadlock() {
	int total_deadlock = 0;
	for (int c = 0; c < n; ++c) {
		int column_deadlock = 0;
		int magnetic = 0;
		for (int r = 0; r < n; ++r) {
			/*처음엔 그냥 로직 그대로 따라했는데, 다시 생각해보니 굳이 그럴 필요가 없었음
			뭔가 다급하면 이런 생각이 잘 나지 않는 것 같음*/
			if (magnetic == 1 && board[r][c] == 2) {
				magnetic = 2;
				column_deadlock++;
			}
			if (board[r][c] == 1) {
				magnetic = 1;
			}
		}
		total_deadlock += column_deadlock;
	}

	return total_deadlock;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int TC = 10;
	for (int test_case = 1; test_case <= TC; test_case++) {
		int answer = 0;
		input();
		answer = deadlock();
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}