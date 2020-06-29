#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int board[2][6][4];

int block_sz[3] = { 1, 2, 2 };
int block_xpos[3][2] = { {0, 0}, {0, 1}, {0, 0} };
int block_ypos[3][2] = { {0, 0}, {0, 0}, {0, 1} };
bool chk[10001];

int isHazard(int bi) {
	for (int h = 0; h < 2; h++) {
		for (int w = 0; w < 4; w++) {
			if (board[bi][h][w] != 0) return 2-h;
		}
	}
	return 0;
}

int getScore(int bi, queue<int>& q) {
	for (int h = 2; h < 6; h++) {
		bool isHole = true;
		for (int w = 0; w < 4; w++) {
			if (board[bi][h][w] == 0) isHole = false;
		}
		if (isHole) {
			q.push(h);
			for (int w = 0; w < 4; w++) {
				board[bi][h][w] = 0;
			}
		}
	}
	
	return q.size();
}

void fallBlock(int t, int y, int x, int bi, int ci) {

	for (int h = 0; h < 6; h++) {
		bool isOk = false;
		for (int sz = 0; sz < block_sz[t]; sz++) {
			int ny = (y + 1) + block_ypos[t][sz];
			int nx = x + block_xpos[t][sz];

			if (ny >= 6 || board[bi][ny][nx] != 0) isOk = true;
		}
		if (isOk) break;
		y += 1;
	}
	
	for (int sz = 0; sz < block_sz[t]; sz++) {
		int ny = y + block_ypos[t][sz];
		int nx = x + block_xpos[t][sz];
		board[bi][ny][nx] = ci;
	}
}
int placeBlock(int t, int x, int bi, int ci) {
	int score = 0;

	fallBlock(t, 0, x, bi, ci);

	// 점수 얻기 
	queue<int> q;
	int tmp;
	while (tmp = getScore(bi, q)) {
		score += tmp;
		while (!q.empty()) {
			int y = q.front();
			q.pop();
	
			vector<int> st;
			for (int h = y - 1; h >= 0; h--) {
				for (int w = 0; w < 4; w++) {
					int cii = board[bi][h][w];
					int nt, ny;
					if (cii == 0 || chk[cii]) continue;
					board[bi][h][w] = 0;

					if (w + 1 < 4 && board[bi][h][w + 1] == cii) {
						board[bi][h][w + 1] = 0;
						nt = 1;
						ny = h;
					}
					else if (h - 1 >= 0 && board[bi][h - 1][w] == cii) {
						board[bi][h - 1][w] = 0;
						nt = 2;
						ny = h - 1;
					}
					else {
						nt = 0;
						ny = h;
					}
					
					chk[cii] = true;
					st.push_back(cii);
					fallBlock(nt, ny, w, bi, cii);
				}
			}

			while (!st.empty()) {
				chk[st.back()] = false;
				st.pop_back();
			}
		}
	}


	// 연한 칸 밑으로 내리기
	int step = isHazard(bi);
	if (step != 0) {
		for (int h = 5; h >= 0; h--) {
			for (int w = 0; w < 4; w++) {
				if (h - step >= 0) board[bi][h][w] = board[bi][h - step][w];
				else board[bi][h][w] = 0;
			}
		}
	}

	return score;
}

int main(void) {
	int cmd_num;
	int answer = 0;
	scanf("%d", &cmd_num);
	for (int i = 1; i <= cmd_num; i++) {
		int t, y, x;
		scanf("%d %d %d", &t, &y, &x);
		answer += placeBlock(t - 1, x, 0, i);
		if (t == 1) {
			answer += placeBlock(0, 3 - y, 1, i);
		}
		else if (t == 2) {
			answer += placeBlock(2, 3 - y, 1, i);
		}
		else if (t == 3) {
			answer += placeBlock(1, 2 - y, 1, i);
		}
	}
	int rest_block = 0;
	for (int bi = 0; bi < 2; bi++) {
		for (int h = 0; h < 6; h++) {
			for (int w = 0; w < 4; w++) {
				if (board[bi][h][w] != 0) rest_block++;
			}
		}
	}
	printf("%d\n%d\n", answer, rest_block);
	return 0;
}