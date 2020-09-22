#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int cost;
	int u, v;
	bool operator<(const Node& rhs) {
		return cost < rhs.cost;
	}
};
int parent[1001];

int find(int u) {
	if (parent[u] == 0) return u;
	else return find(parent[u]);
}
bool merge(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v) return false;;
	parent[u] = v;
	return true;
}


int main(void) {
	int n, m;
	cin >> n >> m;
	vector<Node> edge;
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		edge.push_back({ c, u, v });
	}
	sort(edge.begin(), edge.end());
	int answer = 0;
	for (int i = 0; i < edge.size(); i++) {
		if (merge(edge[i].u, edge[i].v)) {
			answer += edge[i].cost;
		}
	}
	cout << answer;
	return 0;
}