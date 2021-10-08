#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int INF = 987987987;
int N;
string board[100];
int dist[100][100];
bool visited[100][100];
int dy[] = { 0, 0, -1, 1 };
int dx[] = { -1, 1, 0, 0 };

void init() {
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			dist[i][j] = INF;
			visited[i][j] = false;
		}
	}
}

int supplyRoad() {
	priority_queue<pair<int, pair<int, int>>> pq;
	dist[0][0] = 0;
	//visited[0][0] = true;
	pq.push({ 0, {0, 0} });
	while (!pq.empty()) {
		int c = pq.top().first;
		int y = pq.top().second.first;
		int x = pq.top().second.second;
		pq.pop();
		//cout << y << " " << x << " " << c << endl;
		if (visited[y][x]) continue;
		visited[y][x] = true;

		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (!visited[ny][nx] && dist[y][x] + board[ny][nx] - '0' < dist[ny][nx]) {
				dist[ny][nx] = dist[y][x] + board[ny][nx] - '0';
				pq.push({ -(dist[y][x] + board[ny][nx] - '0'), {ny, nx} });
			}
		}
	}

	return dist[N - 1][N - 1];
}
int main(void) {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		init();
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> board[i];
		}

		int answer = supplyRoad();
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}