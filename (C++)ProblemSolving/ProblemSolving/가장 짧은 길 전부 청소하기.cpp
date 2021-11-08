#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
using namespace std;

#define MAX_NODE	200000
typedef pair<int, long long> pii;

int N, M;
vector<pii> adj[MAX_NODE + 1];
bool visited[MAX_NODE + 1];
long long dist[MAX_NODE + 1];

const long long INF = LLONG_MAX;

void init() {
	for (int i = 1; i <= N; ++i) {
		adj[i].clear();
		visited[i] = false;
		dist[i] = INF;
	}
}

long long djk() {
	priority_queue<pair<long long, int>> q;
	q.push({ 0, 1 }); // total dist, current node, 
	dist[1] = 0;

	while (!q.empty()) {
		int cur = q.top().second;
		q.pop();

		if (visited[cur]) {
			continue;
		}
		visited[cur] = true;

		for (pii edge : adj[cur]) {
			int next = edge.first;
			long long cost = edge.second;

			if (dist[next] > dist[cur] + cost) {
				dist[next] = dist[cur] + cost;
				q.push({ -dist[next], next});
			}
		}
	}

	long long ret = 0;
	for (int cur = 2; cur <= N; ++cur) {
		long long minCost = -1;
		for (pii edge : adj[cur]) {
			int near = edge.first;
			long long cost = edge.second;

			long long diff = dist[near] + cost;
			if (diff != dist[cur]) continue;

			if (minCost == -1 || minCost > cost) {
				minCost = cost;
			}
		}
		ret += minCost;
	}
	return ret;

}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//ifstream cin("C:\\Users\\swimm\\Downloads\\input (6).txt");
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> M;
		init();

		for (int i = 0; i < M; ++i) {
			long long u, v, c;
			cin >> u >> v >> c;
			adj[u].push_back({ v, c });
			adj[v].push_back({ u, c });
		}

		long long answer = djk();
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}