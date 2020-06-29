#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

#define H_MAX	15
#define W_MAX	12
#define N_MAX	4

int N, W, H;
int board[H_MAX][W_MAX];
int ans;
int dfs_arr[N_MAX];

int dh[] = { 0, 0, -1, 1 };
int dw[] = { -1, 1, 0, 0 };

void breakBrick() {
	
}

void dfs(int index) {
	if (index == N) {
		breakBrick();
		return;
	}
	for (int i = 0; i < W; i++) {
		int copy_board[H_MAX][W_MAX];

		for (int h = 0; h < H; h++) {
			for (int w = 0; w < W; w++) {
				copy_board[h][w] = board[h][w];
			}
		}

		dfs_arr[index] = i;
		queue<pair<int, int>> chain;
		vector<vector<bool>> chk(N, vector<bool>(H, false));

		int col = dfs_arr[i];
		for (int h = 0; h < H; h++) {
			if (board[h][col] != 0) {
				chain.push({ h, col });
				chk[h][col] = true;
				break;
			}
		}

		while (!chain.empty()) {
			int h = chain.front().first;
			int w = chain.front().second;
			chain.pop();

			int power = board[h][w];
			for (int i = 0; i < 4; i++) {
			}
		}
		
		dfs(index + 1);
		for (int h = 0; h < H; h++) {
			for (int w = 0; w < W; w++) {
				board[h][w] = copy_board[h][w];
			}
		}
	}
}

void solve() {
	dfs(0);
}

int main(void) {
	int TC;
	scanf("%d", &TC);
	for (int test_case = 1; test_case <= TC; test_case) {
		scanf("%d %d %d", &N, &W, &H);
		for (int h = 0; h < H; h++) {
			for (int w = 0; w < W; w++) {
				scanf("%d", &board[h][w]);
			}
		}
		solve();
		printf("#%d %d\n", test_case, ans);
	}

	return 0;
}