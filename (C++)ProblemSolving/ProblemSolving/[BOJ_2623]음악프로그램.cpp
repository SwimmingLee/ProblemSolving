//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//int N, M;
//vector<vector<int>> adj;
//vector<int> ans;
//vector<bool> chk;
//vector<bool> visited;
//
//bool dfs(int v) {
//	if (visited[v]) return false;
//	if (chk[v]) return true;
//
//	chk[v] = true;
//	visited[v] = true;
//
//	bool res = true;
//	for (int i = 0; i < adj[v].size(); i++) {
//		int next = adj[v][i];
//		res &= dfs(next);
//	}
//
//	ans.push_back(v);
//	return res;
//}
//
//void solve() {
//	chk.resize(N + 1, false);
//	visited.resize(N + 1, false);
//	for (int i = 1; i <= N; i++) {
//		if (!chk[i]) {
//			for (int j = 1; j < N + 1; j++)
//				visited[j] = false;
//			if (!dfs(i)) {
//				cout << 0 << '\n';
//				return;
//			}
//		}
//	}
//	for (int i = (int)ans.size()-1; i >= 0; i--) {
//		cout << ans[i] << '\n';
//	}
//}
//
//
//int main(void) {
//	cin >> N >> M;
//	adj.resize(N + 1);
//	for (int i = 0; i < M; i++) {
//		int n_singer;
//		cin >> n_singer;
//		int prev, singer;
//		prev = -1;
//		for (int j = 0; j < n_singer; j++) {
//			cin >> singer;
//			if (prev != -1) {
//				adj[prev].push_back(singer);
//			}
//			prev = singer;
//		}
//	}	
//	for (int i = 1; i <= N; i++) {
//		sort(adj[i].begin(), adj[i].end());
//		adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
//	}
//	solve();
//	return 0;
//}