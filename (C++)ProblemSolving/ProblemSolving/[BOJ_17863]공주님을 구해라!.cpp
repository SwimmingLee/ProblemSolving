#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int height, width, limit;
int board[100][100];
int seen[100][100];
int dy[] = { 0, 0, -1, 1 };
int dx[] = { -1, 1, 0, 0 };

void solve() {
	queue<pair<int, int>> q;
	q.push({ 0, 0 });
	seen[0][0] = 0;
	int gram_t;
	int gram_y = -1, gram_x;
	int time = -1;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		if (y == height - 1 && x == width - 1) {
			time = seen[y][x];
			//break;
		}
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || nx < 0 || ny >= height || nx >= width \
				|| seen[ny][nx] != -1 || board[ny][nx] == 1) continue;

			if (board[ny][nx] == 2) {
				gram_t = seen[y][x] + 1;
				gram_y = ny;
				gram_x = nx;
			}
			seen[ny][nx] = seen[y][x] + 1;
			q.push({ ny, nx });
		}
	}

	if (gram_y == -1) {
		if (time == -1 || time > limit) cout << "Fail\n";
		else cout << time;
	}
	else {
		int answer;
		if (time == -1) answer =  gram_t + height - 1 - gram_y + width - 1 - gram_x;
		else answer = min(time, gram_t + height - 1 - gram_y + width - 1 - gram_x);


		//cout << time << " " << limit << " ds\n";
		if (answer > limit) cout << "Fail\n";
		else cout << answer;
	}
	
}


int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> height >> width >> limit;

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			cin >> board[h][w];
			seen[h][w] = -1;
		}
	}

	
	solve();
	return 0;
}