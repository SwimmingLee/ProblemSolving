#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
	int to;
	int cost;
	bool operator<(const Edge& rhs) const{
		return cost > rhs.cost;
	}
};

vector<Edge> adj[10001];
bool chk[10001];
int main(void) {
	int n_vertex, n_edge;
	cin >> n_vertex >> n_edge;
	for (int i = 0; i < n_edge; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		adj[u].push_back({ v, c });
		adj[v].push_back({ u, c });
	}
	priority_queue<Edge> q;
	for (Edge& e : adj[1]) {
		q.push(e);
	}
	chk[1] = true;
	long long answer = 0;
	while (!q.empty()) {
		Edge cur = q.top();
		q.pop();
		if (chk[cur.to]) continue;
		chk[cur.to] = true;

		answer += cur.cost;
		for (Edge& e : adj[cur.to]) {
			q.push(e);
		}

	}
	cout << answer;
	return 0;
}