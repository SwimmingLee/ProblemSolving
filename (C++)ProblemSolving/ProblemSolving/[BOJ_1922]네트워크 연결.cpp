#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node{
	int cost;
	int u, v;

	bool operator< (const Node rhs) const {
		return this->cost < rhs.cost;
	}
};
int n_node, n_edge;
vector<Node> adj;
int parent[1001];
void init() {
	for (int i = 1; i <= n_node; i++) {
		parent[i] = -1;
	}
}
int find(int u) {
	if (parent[u] < 0) return u;
	else return parent[u] = find(parent[u]);
}
void merge(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v) return;
	parent[u] += parent[v];
	parent[v] = u;
}

void mst() {
	int res = 0;
	init();
	sort(adj.begin(), adj.end());
	for (int i = 0; i < adj.size(); i++) {
		int cost = adj[i].cost;
		//cout << cost << endl;
		int u = adj[i].u;
		int v = adj[i].v;
		
		u = find(u);
		v = find(v);
		//cout << u << " " << v << " \n";
		if (u != v) {
			res += cost;
			merge(u, v);
			if (parent[u] == -n_node) {
				break;
			}
		}
		
	}
	cout << res << '\n';
}
int main(void) {
	cin >> n_node >> n_edge;
	while (n_edge--) {
		int u, v, cost;
		cin >> u >> v >> cost;
		adj.push_back({ cost, u, v });
	}
	mst();
	return 0;
}