#include <iostream>
using namespace std;

#define BOARD_MAX	500
#define DIRECTION	4
int board[BOARD_MAX][BOARD_MAX];
int cache[BOARD_MAX][BOARD_MAX];
int board_sz;
int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int eatingBamboo(int y, int x) {
	int& res = cache[y][x];
	if (res != -1) return res;
	res = 0;

	int max_tmp = 0;
	for (int i = 0; i < DIRECTION; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= board_sz || nx < 0 || nx >= board_sz) continue;
		int tmp;
		if (board[ny][nx] > board[y][x]) {
			tmp = eatingBamboo(ny, nx) + 1;
			if (max_tmp < tmp) {
				max_tmp = tmp;
			}
		}
	}
	return res += max_tmp;
}

int  main(void) {
	cin >> board_sz;
		
	for (int i = 0; i < board_sz; i++) {
		for (int j = 0; j < board_sz; j++) {
			cin >> board[i][j];
			cache[i][j] = -1;
		}
	}
	
	int ans = 0;
	for (int i = 0; i < board_sz; i++) {
		for (int j = 0; j < board_sz; j++) {
			int tmp = eatingBamboo(i, j);
			if (ans < tmp) ans = tmp;
		}
	}
	cout << ans + 1 << '\n';
	return 0;
}