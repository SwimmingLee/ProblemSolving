#include <stdio.h>
#include <queue>
using namespace std;

#define BOARD_MAX	350
#define N_MAX		50
#define M_MAX		50

typedef struct {
	int life_power;
	int birth_time;
	int dead_line;
} Cell;

int N, M, K;
Cell board[BOARD_MAX][BOARD_MAX];
queue<pair<int, int>> active_cell;
int dh[] = { 0, 0, -1, 1 };
int dw[] = { -1, 1, 0, 0 };
int ans;

void solve() {
	for (int time = 1; time <= K; time++) {

		int cell_num = active_cell.size();
		//printf("Time: %d, Cell_Num:%d \n", time, cell_num);
		while (cell_num--) {
			int h = active_cell.front().first;
			int w = active_cell.front().second;
			active_cell.pop();

			Cell& pcell = board[h][w];

			pcell.dead_line -= 1;

			// 사춘기 세포는 번식 ㄴㄴ
			if (pcell.dead_line >= pcell.life_power) {
				active_cell.push({ h, w });
				continue;
			}

			// 어른 세포 번식
			for (int i = 0; i < 4; i++) {
				int nh = h + dh[i];
				int nw = w + dw[i];

				Cell& ccell = board[nh][nw];
				if (ccell.dead_line == -1) {
					ccell.birth_time = time;
					ccell.life_power = pcell.life_power;
					ccell.dead_line = pcell.life_power * 2;
					active_cell.push({ nh, nw });
				}
				else if (ccell.birth_time == time && ccell.life_power < pcell.life_power) {
					ccell.life_power = pcell.life_power;
					ccell.dead_line = pcell.life_power * 2;
				}
			}
			
			if (pcell.dead_line != 0) {
				active_cell.push({ h, w });
			}
		}

		//for (int h = (BOARD_MAX - N)/2 -time; h <= (BOARD_MAX - N) / 2 + N + time; h++) {
		//	for (int w = (BOARD_MAX - M) / 2 -time; w <= (BOARD_MAX - M) / 2 + M + time; w++) {
		//		if (board[h][w].dead_line == -1)
		//			printf("%c ", 'x');
		//		else
		//			printf("%d ", board[h][w].dead_line);
		//	}
		//	printf("\n");
		//}
		//printf("\n");
	}
}


int main(void) {
	int TC;
	scanf("%d", &TC);
	for (int test_case = 1; test_case <= TC; test_case++) {
		scanf("%d %d %d", &N, &M, &K);
		while (!active_cell.empty()) {
			active_cell.pop();
		}
		for (int h = 0; h < BOARD_MAX; h++) {
			for (int w = 0; w < BOARD_MAX; w++) {
				board[h][w].dead_line = -1;
			}
		}
		for (int h = 0; h < N; h++) {
			for (int w = 0; w < M; w++) {
				int nh = (BOARD_MAX - N) / 2 + h;
				int nw = (BOARD_MAX - M) / 2 + w;
				int life_power;
				scanf("%d", &life_power);
				if (life_power != 0) {
					board[nh][nw] = { life_power, 0, life_power * 2 };
					active_cell.push({ nh, nw });
				}
				
			}
		}
		solve();
		printf("#%d %d\n", test_case, active_cell.size());
	}
	return 0;
}