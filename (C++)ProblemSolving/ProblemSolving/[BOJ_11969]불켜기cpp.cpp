#include <iostream>
#include <queue>
using namespace std;

#define MAX_N		101

#define NOT_VISITED	0
#define VISITABLE	1
#define VISITED		2

int N, M;
vector<pair<int, int>> room[MAX_N][MAX_N];
int light_room[MAX_N][MAX_N];
int visited_room[MAX_N][MAX_N];

int dy[] = {0, 0, -1, 1};
int dx[] = { -1, 1, 0, 0 };

int solve() {
	int answer = 1;
	queue<pair<int, int>> q;
	q.push({ 1, 1 });
	visited_room[1][1] = VISITED;
	light_room[1][1] = true;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		
		q.pop();
		for (auto& room_pos : room[y][x]) {
			if (!light_room[room_pos.first][room_pos.second]) {
				answer += 1;
				light_room[room_pos.first][room_pos.second] = true;
				if (visited_room[room_pos.first][room_pos.second] == VISITABLE) {
					q.push({ room_pos.first, room_pos.second });
					visited_room[room_pos.first][room_pos.second] = VISITED;
				}
			}
		}

		

		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny < 1 || nx < 1 || ny > N || nx > N || visited_room[ny][nx] == VISITED) continue;
			
			if (light_room[ny][nx]) {
				q.push({ ny, nx });
				visited_room[ny][nx] = VISITED;
			}
			else {
				visited_room[ny][nx] = VISITABLE;
			}
		}

	}
	return answer;
	
}

int main(void) {
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int in_y, in_x, out_y, out_x;
		cin >> in_y >> in_x >> out_y >> out_x;
		room[in_y][in_x].push_back({ out_y, out_x });
	}

	int answer = solve();
	cout << answer;

	return 0;
}