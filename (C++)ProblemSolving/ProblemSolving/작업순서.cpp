#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int inbound[1001];
vector<int> adj[1001];
bool visited[1001];
int vertax, edge;
//
//void topologicalSort(int n) {
//	
//	for (int i = 0; i < adj[n].size(); ++i) {
//		int next = adj[n][i];
//		//inbound[next] -= 1;
//		if (!visited[next]) {
//			topologicalSort(next);
//		}
//	}
//	visited[n] = true;
//	cout << ' ' << n;
//}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int TC = 10;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> vertax >> edge;
		for (int i = 1; i <= vertax; ++i) {
			adj[i].resize(0);
			inbound[i] = 0;
			visited[i] = false;
		}
		for (int i = 0; i < edge; ++i) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			inbound[v]++;
			/*adj[v].push_back(u);
			inbound[u]++;*/
		}

		// BFS를 이용한 topological sort
		queue<int> q;
		for (int i = 1; i <= vertax; ++i) {
			if (inbound[i] == 0) q.push(i);
		}

		cout << '#' << test_case;
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			cout << ' ' << cur;

			for (int i = 0; i < adj[cur].size(); ++i) {
				int next = adj[cur][i];
				inbound[next]--;
				if (inbound[next] == 0)
					q.push(next);
			}
		}
		cout << '\n';

		// DFS를 이용한 topological sort
		//cout << '#' << test_case;
		//for (int i = 1; i <= vertax; ++i) {
		//	if (!visited[i] && inbound[i] == 0)
		//		topologicalSort(i);
		//}
		//cout << '\n';
	}
}