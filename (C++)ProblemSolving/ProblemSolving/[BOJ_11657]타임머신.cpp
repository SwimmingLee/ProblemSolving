#include <iostream>
using namespace std;

struct Edge {
	int from, to;
	int cost;
};
int dist[501];
Edge edge[6000];
const int inf = 987987987;

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int n_city, n_route;
	cin >> n_city >> n_route;
	for (int i = 0; i < n_route; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		edge[i] = { u, v, c };
	}
	for (int i = 0; i <= n_city; i++) {
		dist[i] = inf;
	}
	dist[1] = 0;
	bool negative_cycle = false;
	for (int i = 1; i <= n_city; i++) {
		for (int j = 0; j < n_route; j++) {
			int from = edge[j].from;
			int to = edge[j].to;
			int cost = edge[j].cost;

			if (dist[from] != inf && dist[to] > dist[from] + cost) {
				dist[to] = dist[from] + cost;
				if (i == n_city || dist[to] < -inf) {
					negative_cycle = true;
					break;
				}
			}
		}
	}
	if (negative_cycle) {
		cout << -1;
	}
	else {
		for (int i = 2; i <= n_city; i++) {
			cout << (dist[i] == inf ? -1 : dist[i]) << '\n';
		}
	}
	return 0;
}