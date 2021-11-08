#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAX_NODE 50001
const int INF = 987987987;
int N, M, X;
vector<pair<int, int>> edge[MAX_NODE];
vector<pair<int, int>> rev_edge[MAX_NODE];
bool visited[MAX_NODE]; 
bool rev_visited[MAX_NODE];
int dist[MAX_NODE];
int rev_dist[MAX_NODE];

void init() {
	for (int i = 1; i <= N; ++i) {
		edge[i].clear();
		rev_edge[i].clear();

		dist[i] = INF;
		rev_dist[i] = INF;

		visited[i] = false;
		rev_visited[i] = false;
	}
}

void djk(int x, vector<pair<int, int>> edge[], bool visited[], int dist[]) {
	
	priority_queue<pair<int, int>> pq;
	pq.push({ 0, x });
	dist[x] = 0;
	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		if (visited[cur]) {
			continue;
		}
		visited[cur] = true;

		for (auto e : edge[cur]) {
			int next = e.first;
			int cost = e.second;
			if (dist[next] > dist[cur] + cost) {
				dist[next] = dist[cur] + cost;
				pq.push({ -dist[next], next });
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> M >> X;
		init();
		for (int i = 0; i < M; ++i) {
			int u, v, c;
			cin >> u >> v >> c;
			edge[u].push_back({ v, c });
			rev_edge[v].push_back({ u, c });
		}

		djk(X, edge, visited, dist);
		djk(X, rev_edge, rev_visited, rev_dist);

		int answer = 0;
		for (int i = 1; i <= N; ++i) {
			int tmp = dist[i] + rev_dist[i];
			if (tmp >= INF) continue;
			answer = max(answer, tmp);
			
		}

		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}