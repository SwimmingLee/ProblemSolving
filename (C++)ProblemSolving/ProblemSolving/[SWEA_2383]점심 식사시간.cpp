#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define BOARD_MAX	10
#define PERSON_MAX	10
#define STAIR_NUM	2

#define STAIR_A		0
#define STAIR_B		1

int board_sz;
int person_num;
int ans;
int board[BOARD_MAX][BOARD_MAX];
pair<int, int> person[PERSON_MAX];
int stair_depth[STAIR_NUM];
pair<int, int> stair[STAIR_NUM];
int dfs_arr[PERSON_MAX];

int calcTime(vector<int>& stairA_time, vector<int>& stairB_time) {
	int time = 1;
	queue<int> stair_line[STAIR_NUM];
	int stairA_person = stairA_time.size();
	int stairB_person = stairB_time.size();
	int stairA_idx, stairB_idx;

	stairA_idx = stairB_idx = 0;
	//printf("%d %d\n", stair_depth[STAIR_A], stair_depth[STAIR_B]);
	while (stairA_idx < stairA_person || stairB_idx < stairB_person || \
		!stair_line[STAIR_A].empty() || !stair_line[STAIR_B].empty()) {
		int stairA_line_sz = stair_line[STAIR_A].size();
		//printf("TIME: %d, idx: %d, %d \n", time, stairA_idx, stairA_line_sz);
		while (stairA_line_sz--) {
			int tmp = stair_line[STAIR_A].front(); stair_line[STAIR_A].pop();
			tmp -= 1;
			if (tmp > 0) stair_line[STAIR_A].push(tmp);
		}
		while (stairA_idx < stairA_person && time >= stairA_time[stairA_idx] && stair_line[STAIR_A].size() < 3) {
			stair_line[STAIR_A].push(stair_depth[STAIR_A]);
			stairA_idx++;
		}


		int stairB_line_sz = stair_line[STAIR_B].size();
		while (stairB_line_sz--) {
			int tmp = stair_line[STAIR_B].front(); stair_line[STAIR_B].pop();
			tmp -= 1;
			if (tmp > 0) stair_line[STAIR_B].push(tmp);
		}
		while (stairB_idx < stairB_person && time >= stairB_time[stairB_idx] && stair_line[STAIR_B].size() < 3) {
			stair_line[STAIR_B].push(stair_depth[STAIR_B]);
			stairB_idx++;
		}
		time++;
	}

	return time;
}

void dfs(int index) {
	if (index == person_num) {
		vector<int> stair_time[STAIR_NUM];

		for (int i = 0; i < person_num; i++) {
			int choice = dfs_arr[i];
			int arrived_time = abs(stair[choice].first - person[i].first) + abs(stair[choice].second - person[i].second);
			stair_time[choice].push_back(arrived_time);
		}
		sort(stair_time[0].begin(), stair_time[0].end());
		sort(stair_time[1].begin(), stair_time[1].end());

		int time = calcTime(stair_time[0], stair_time[1]);
		if (ans == -1 || ans > time) {
			ans = time;
		}
		return;
	}
	for (int i = 0; i < STAIR_NUM; i++) {
		dfs_arr[index] = i;
		dfs(index + 1);
	}
}//dfs(0)

void solve() {
	dfs(0);
}

int main(void) {
	int TC;
	scanf("%d", &TC);
	for (int test_case = 1; test_case <= TC; test_case++) {
		person_num = 0;
		ans = -1;
		int stair_idx = 0;
		scanf("%d", &board_sz);
		for (int h = 0; h < board_sz; h++) {
			for (int w = 0; w < board_sz; w++) {
				scanf("%d", &board[h][w]);
				if (board[h][w] == 1) {
					person[person_num++] = { h, w };
				}
				else if (board[h][w] != 0) {
					stair_depth[stair_idx] = board[h][w];
					stair[stair_idx++] = { h, w };
				}
			}
		}
		solve();
		printf("#%d %d\n", test_case, ans);
	}
	return 0;
}