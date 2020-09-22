#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int n_problem, n_info;
int input_line[32001];
vector<vector<int>> adj;

void solve() {
	priority_queue<int> PQ;
	for (int i = 1; i <= n_problem; i++) {
		if (input_line[i] == 0) {
			PQ.push(-i);
		}
	}

	while (!PQ.empty()) {
		int cur = -PQ.top();
		PQ.pop();
		cout << cur << ' ';
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];

			input_line[next]--;
			if (input_line[next] == 0) {
				PQ.push(-next);
			}

		}
	}
}


int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n_problem >> n_info;
	adj.resize(n_problem + 1);
	for (int i = 0; i < n_info; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		input_line[v]++;
	}

	solve();
}

