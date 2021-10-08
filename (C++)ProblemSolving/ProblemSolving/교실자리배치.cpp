#include <iostream>
using namespace std;

int N;
int friends[21][4];
int board[21][21];
int dy[] = { 0, 0, -1, 1 };
int dx[] = { -1, 1, 0, 0 };
int score[] = { 0, 1, 10, 100, 1000 };

void init() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			board[i][j] = 0;
		}
	}
}

void seatDown(int no) {
	int nearFriend = 0;
	int nearBlank = 0;
	int r = -1, c = 0;

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (board[y][x] != 0) continue;
			int tmpNearFriend = 0;
			int tmpNearBlank = 0;
			for (int i = 0; i < 4; ++i) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

				if (board[ny][nx] == 0) tmpNearBlank++;
				else if (board[ny][nx] == friends[no][0]) tmpNearFriend++;
				else if (board[ny][nx] == friends[no][1]) tmpNearFriend++;
				else if (board[ny][nx] == friends[no][2]) tmpNearFriend++;
				else if (board[ny][nx] == friends[no][3]) tmpNearFriend++;
			}

			if (nearFriend < tmpNearFriend) {
				nearFriend = tmpNearFriend;
				nearBlank = tmpNearBlank;
				r = y;
				c = x;
			}
			else if (nearFriend == tmpNearFriend) {
				if (nearBlank < tmpNearBlank) {
					nearFriend = tmpNearFriend;
					nearBlank = tmpNearBlank;
					r = y;
					c = x;
				}
				else if (nearBlank == tmpNearBlank && r == -1) {
					r = y;
					c = x;
				}
			}
		}
	}

	board[r][c] = no;
}

int sumFriendScore() {
	int ret = 0;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (board[y][x] == 0) continue;

			int no = board[y][x];
			int tmpNearFriend = 0;
			for (int i = 0; i < 4; ++i) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

				if (board[ny][nx] == friends[no][0]) tmpNearFriend++;
				else if (board[ny][nx] == friends[no][1]) tmpNearFriend++;
				else if (board[ny][nx] == friends[no][2]) tmpNearFriend++;
				else if (board[ny][nx] == friends[no][3]) tmpNearFriend++;
			}

			ret += score[tmpNearFriend];
		}
	}
	return ret;
}

int main(void) {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> N;
		init(); // board √ ±‚»≠
		for (int i = 0; i < N; ++i) {
			int no;
			cin >> no;
			cin >> friends[no][0] >> friends[no][1] >> friends[no][2] >> friends[no][3];
			seatDown(no);
			int answer = sumFriendScore();

			cout << '#' << test_case << ' ' << answer << '\n';
		}

	}
	return 0;
}