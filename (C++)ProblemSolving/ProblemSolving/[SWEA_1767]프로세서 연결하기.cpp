#include <iostream>
using namespace std;

#define BOARD_MAX	12
#define CORE_MAX	12
#define DIR			4
#define UP			2
#define DOWN		3
#define LEFT		1	
#define RIGHT		0


int max_connected_cnt;
int min_connected_len;
int processor_cnt;
int board_sz;
int board[BOARD_MAX][BOARD_MAX];
int copy_board[BOARD_MAX][BOARD_MAX];
pair<int, int> processor[CORE_MAX];
int dfs_arr[CORE_MAX];
int connected_len = 0;
int connected_cnt = 0;

void dfs(int index, int start) {
	if (index == processor_cnt) {
		if (connected_cnt > max_connected_cnt) {
			//cout << "AA" << endl;
			max_connected_cnt = connected_cnt;
			min_connected_len = connected_len;
		}
		else if (connected_cnt == max_connected_cnt) {
			//cout << "BB" << endl;
			min_connected_len = min_connected_len < connected_len ? min_connected_len : connected_len;
		}
		return;
	}

	for (int i = 0; i < DIR; i++) {
		dfs_arr[index] = i;
		bool isok = true;
		int gain_len = 0;
		int ch = processor[index].first;
		int cw = processor[index].second;

		if (dfs_arr[index] == UP) {
			for (int h = ch - 1; h >= 0; h--) {
				if (copy_board[h][cw] != 0) {
					isok = false;
					break;
				}
			}

			if (isok) {
				for (int h = ch - 1; h >= 0; h--) {
					copy_board[h][cw] = 2;
				}
				gain_len = ch;
				connected_len += gain_len;
				connected_cnt++;
			}
		}
		else if (dfs_arr[index] == DOWN) {
			for (int h = ch + 1; h < board_sz; h++) {
				if (copy_board[h][cw] != 0) {
					isok = false;
					break;
				}
			}

			if (isok) {
				for (int h = ch + 1; h < board_sz; h++) {
					copy_board[h][cw] = 2;
				}
				gain_len = board_sz - 1 - ch;
				connected_len += gain_len;
				connected_cnt++;
			}
		}
		else if (dfs_arr[index] == LEFT) {
			for (int w = cw - 1; w >= 0; w--) {
				if (copy_board[ch][w] != 0) {
					isok = false;
					break;
				}
			}

			if (isok) {
				for (int w = cw - 1; w >= 0; w--) {
					copy_board[ch][w] = 2;
				}
				gain_len = cw;
				connected_len += gain_len;
				connected_cnt++;
			}
		}
		else {
			for (int w = cw + 1; w < board_sz; w++) {
				if (copy_board[ch][w] != 0) {
					isok = false;
					break;
				}
			}

			if (isok) {
				for (int w = cw + 1; w < board_sz; w++) {
					copy_board[ch][w] = 2;
				}
				gain_len = board_sz - 1 - cw;
				connected_len += gain_len;
				connected_cnt++;
			}
		}

		dfs(index + 1, i + 1);
		if (isok) {
			if (dfs_arr[index] == UP) {
				for (int h = ch - 1; h >= 0; h--) {
					copy_board[h][cw] = 0;
				}
			}
			else if (dfs_arr[index] == DOWN) {
				for (int h = ch + 1; h < board_sz; h++) {
					copy_board[h][cw] = 0;
				}
			}
			else if (dfs_arr[index] == LEFT) {
				for (int w = cw - 1; w >= 0; w--) {
					copy_board[ch][w] = 0;
				}
			}
			else {
				for (int w = cw + 1; w < board_sz; w++) {
					copy_board[ch][w] = 0;
				}
			}
			connected_len -= gain_len;
			connected_cnt--;
		}
	}
}

void connectProcessor() {
	dfs(0, 0);
}


int main(void) {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		processor_cnt = 0;
		max_connected_cnt = 0;
		min_connected_len = 0;
		cin >> board_sz;
		for (int h = 0; h < board_sz; h++) {
			for (int w = 0; w < board_sz; w++) {
				cin >> board[h][w];
				if (board[h][w] == 1  && h != 0 && h != board_sz-1 && w != 0 && w != board_sz-1) {
						processor[processor_cnt++] = { h, w };
					}
				}
			}
			for (int h = 0; h < board_sz; h++) {
				for (int w = 0; w < board_sz; w++) {
					copy_board[h][w] = board[h][w];
				}
			}
			connectProcessor();
			cout << '#' << test_case << ' '  << min_connected_len << '\n';
		}
		return 0;
	}