#include <iostream>
#include <queue>
using namespace std;

#define MAX_NODE 50001
int N, M;
priority_queue<pair<int, pair<int, int>>> pq;

int parent[MAX_NODE];

int find(int u) {
	if (parent[u] < 0) return u;
	else return parent[u] = find(parent[u]);
}

bool merge(int u, int v) {
	u = find(u);
	v = find(v);

	if (u == v) return false;
	
	// v, u 순으로 만들기
	if (parent[u] < parent[v]) {
		swap(u, v);
	}
	parent[v] += parent[u];
	parent[u] = v;

	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> M;
		while (!pq.empty())
			pq.pop();
		for (int i = 1; i <= N; ++i)
			parent[i] = -1;

		for (int i = 0; i < M; ++i) {
			int u, v, c;
			cin >> u >> v >> c;
			pq.push({ -c, {u, v} });
		}
		

		int answer = 0;
		while (!pq.empty()) {
			int cost = pq.top().first;
			int from = pq.top().second.first;
			int to = pq.top().second.second;
			pq.pop();

			if (merge(from, to)) {
				answer += -cost;
			}
		}
		
		cout << '#' << tc << ' ' << answer << '\n';
	}
}