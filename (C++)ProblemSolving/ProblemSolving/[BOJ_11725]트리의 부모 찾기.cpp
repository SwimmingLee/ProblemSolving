#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int child[2];
};

int n;
queue<int> q;
vector<vector<int>> adj;
vector<int> whoisparent;
vector<Node> node;

void solve() {
	while (!q.empty()) {
		int u = q.front(); q.pop();
		
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (whoisparent[v] != 0) continue;
			if (node[u].child[0] == 0) {
				node[u].child[0] = v;
				whoisparent[v] = u;
			}
			else {
				node[u].child[1] = v;
				whoisparent[v] = u;
			}
			q.push(v);
		}
	}


	for (int i = 2; i <= n; i++) {
		cout << whoisparent[i] << '\n';
	}
}


int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n;
	whoisparent.resize(n+1, 0);
	adj.resize(n + 1);
	node.resize(n + 1);

	for (int i =1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		if (u == 1) {
			adj[u].push_back(v);
			whoisparent[v] = u;
			q.push(v);
		}
		if (v == 1) {
			adj[v].push_back(u);
			whoisparent[u] = v;
			q.push(u);
		}
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	solve();
	return 0;
}