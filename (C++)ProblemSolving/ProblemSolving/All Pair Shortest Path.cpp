#include <iostream>
using namespace std;

int N, M;
int adj[501][501];
const int INF = 987987987;
void init() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (i == j)
				adj[i][j] = 0;
			else
				adj[i][j] = INF;
		}
	}
}
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> M;
		init();
		for (int i = 0; i < M; ++i) {
			int u, v, c;
			cin >> u >> v >> c;
			adj[u][v] = min(adj[u][v], c);
		}

		for (int k = 1; k <= N; ++k) {
			for (int i = 1; i <= N; ++i) {
				for (int j = 1; j <= N; ++j) {
					if (adj[i][j] > adj[i][k] + adj[k][j]) {
						adj[i][j] = adj[i][k] + adj[k][j];
					}
				}
			}
		}
		
		cout << '#' << tc << ' ';
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (adj[i][j] == INF)
					cout << -1 << ' ';
				else
					cout << adj[i][j] << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}