#include <iostream>
#include <algorithm>
using namespace std;

#define BOARD_MAX	50
#define HOUSE_MAX	100
#define CHIKEN_MAX	13

int board[BOARD_MAX][BOARD_MAX];
struct Pos {
	int y, x;
};
Pos house[HOUSE_MAX];
int chiken_distance[HOUSE_MAX];

Pos chiken[CHIKEN_MAX];
int board_sz;
int n_chiken = 0;
int n_house = 0;
int ing_chiken = 0;
int answer = -1;
int dfs_order[CHIKEN_MAX];

void selectChiken(int cnt, int start) {
	if (cnt == ing_chiken) {
		for (int i = 0; i < n_house; i++) {
			chiken_distance[i] = 9999;
		}
		for (int i = 0; i < ing_chiken; i++) {
			for (int j = 0; j < n_house; j++) {
				chiken_distance[j] = min(chiken_distance[j], abs(chiken[dfs_order[i]].y - house[j].y) + abs( chiken[dfs_order[i]].x - house[j].x));
			}
		}
		int total_distance = 0;
		for (int i = 0; i < n_house; i++) {
			total_distance += chiken_distance[i];
		}
		if (answer == -1 || total_distance < answer) {
			answer = total_distance;
		}
		return;
	}
	if (ing_chiken - cnt > n_chiken - start) return;
	for (int i = start; i < n_chiken; i++) {
		dfs_order[cnt] = i;
		selectChiken(cnt + 1, i + 1);
	}
}


int main(void) {
	cin >> board_sz >> ing_chiken;

	for (int i = 0; i < board_sz; i++) {
		for (int j = 0; j < board_sz; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) {
				house[n_house++] = { i, j };
			}
			else if (board[i][j] == 2) {
				chiken[n_chiken++] = { i, j };
			}
		}
	}

	selectChiken(0, 0);
	cout << answer << '\n';
	return 0;
}