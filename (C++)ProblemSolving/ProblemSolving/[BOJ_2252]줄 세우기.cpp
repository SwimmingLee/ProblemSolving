#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<vector<int>> adj;
vector<bool> chk;

void dfs(int v) {
	chk[v] = true;
	for (int i = 0; i < adj[v].size(); i++) {
		int next = adj[v][i];
		if (!chk[next]) dfs(next);
	}
	cout << v << ' ';
}

void solve() {
	chk.resize(N + 1, false);
	for (int i = 1; i <= N; i++) {
		if (!chk[i]) dfs(i);
	}
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> N >> M;
	adj.resize(N + 1);
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		adj[v].push_back(u);
	}
	solve();
	return 0;
}