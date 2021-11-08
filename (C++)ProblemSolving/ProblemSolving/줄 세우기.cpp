#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_NODE	50000
int N, M;
int inbound[MAX_NODE];
vector<int> adj[MAX_NODE];

void init() {
	for (int i = 0; i <= N; ++i) {
		inbound[i] = 0;
		adj[i].clear();
	}
}

int main(void) {

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> M;
		init();
		for (int i = 0; i < M; ++i) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			inbound[v]++;
		}

		queue<int> q;
		for (int i = 1; i <= N; ++i) {
			if (inbound[i] == 0) {
				q.push(i);
			}
		}

		cout << '#' << tc << ' ';
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			cout << cur << ' ';

			for (int next : adj[cur]) {
				inbound[next]--;

				if (inbound[next] == 0) {
					q.push(next);
				}
			}
		}
		cout << '\n';
	}
	return 0;
}