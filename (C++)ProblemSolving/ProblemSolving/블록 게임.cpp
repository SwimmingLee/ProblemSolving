#include <string>
#include <vector>
#include <iostream>
using namespace std;

int removable_block[5][3][2] = {
	{{1, 0}, {1, 1}, {1, 2}},
	{{1, 0}, {2, 0}, {2, -1}},
	{{1, 0}, {2, 0}, {2, 1}},
	{{1, 0}, {1, -1}, {1, -2}},
	{{1, 0}, {1, -1}, {1, 1}}
};

bool isRemovalbeBlock(int block_idx, int y, int x, vector<vector<int>>& board) {
	//for (int block_idx = 0; block_idx < 3; block_idx++) {
	for (int i = 0; i < 3; i++) {
		int ny = y + removable_block[block_idx][i][0];
		int nx = x + removable_block[block_idx][i][1];
		if (ny < 0 || nx < 0 || ny >= board.size() || nx >= board[0].size() || \
			board[y][x] != board[ny][nx])
			return false;
	}
	//}
	return true;
}

bool chkSafe(int block_idx, int y, int x, vector<vector<int>>& board) {
	for (int i = 2; i >= 1; i--) {
		int ny = y + removable_block[block_idx][i][0];
		int nx = x + removable_block[block_idx][i][1];
		for (int h = ny; h >= 0; h--) {
			if (board[h][nx] != 0 && board[h][nx] != board[y][x])
				return false;
		}
		if (block_idx == 2 || block_idx == 1) break;
	}
	return true;
}

void removeBlock(int block_idx, int y, int x, vector<vector<int>>& board) {
	board[y][x] = 0;
	for (int i = 0; i < 3; i++) {
		int ny = y + removable_block[block_idx][i][0];
		int nx = x + removable_block[block_idx][i][1];
		board[ny][nx] = 0;
	}
}


int solution(vector<vector<int>> board) {
	int answer = 0;
	for (int y = 0; y < board.size(); y++) {
		for (int x = 0; x < board[0].size(); x++) {
			bool bremove = false;
			if (board[y][x] != 0) {
				for (int block_idx = 0; block_idx < 5; block_idx++) {
					if (isRemovalbeBlock(block_idx, y, x, board)) {
						if (chkSafe(block_idx, y, x, board)) {
							removeBlock(block_idx, y, x, board);
							bremove = true;
							answer++;
						//cout << "[] " << y << " " << x << " \n";
						}
						break;
					}
					
				}
			}
			if (bremove) {
				y--;
				break;
			}
		}
	}
	return answer;
}
